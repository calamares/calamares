/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "LuksBootKeyFileJob.h"

#include "utils/System.h"
#include "utils/Entropy.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/UMask.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QDir>
#include <QRegularExpression>

LuksBootKeyFileJob::LuksBootKeyFileJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

LuksBootKeyFileJob::~LuksBootKeyFileJob() {}

QString
LuksBootKeyFileJob::prettyName() const
{
    return tr( "Configuring LUKS key file." );
}

struct LuksDevice
{
    LuksDevice( const QMap< QString, QVariant >& pinfo )
        : isValid( false )
        , isRoot( false )
    {
        if ( pinfo.contains( "luksMapperName" ) )
        {
            QString fs = pinfo[ "fs" ].toString();
            QString mountPoint = pinfo[ "mountPoint" ].toString();

            if ( !mountPoint.isEmpty() || fs == QStringLiteral( "linuxswap" ) )
            {
                isValid = true;
                isRoot = mountPoint == '/';
                device = pinfo[ "device" ].toString();
                passphrase = pinfo[ "luksPassphrase" ].toString();
            }
        }
    }

    bool isValid;
    bool isRoot;
    QString device;
    QString passphrase;
};

/** @brief Extract the luks passphrases setup.
 *
 * Given a list of partitions (as set up by the partitioning module,
 * so there's maps with keys inside), returns just the list of
 * luks passphrases for each device.
 */
static QList< LuksDevice >
getLuksDevices( const QVariantList& list )
{
    QList< LuksDevice > luksItems;

    for ( const auto& p : list )
    {
        if ( p.canConvert< QVariantMap >() )
        {
            LuksDevice d( p.toMap() );
            if ( d.isValid )
            {
                luksItems.append( d );
            }
        }
    }
    return luksItems;
}

struct LuksDeviceList
{
    LuksDeviceList( const QVariant& partitions )
        : valid( false )
    {
        if ( partitions.canConvert< QVariantList >() )
        {
            devices = getLuksDevices( partitions.toList() );
            valid = true;
        }
    }

    QList< LuksDevice > devices;
    bool valid;
};

static const char keyfile[] = "/crypto_keyfile.bin";

static bool
generateTargetKeyfile()
{
    Calamares::UMask m( Calamares::UMask::Safe );

    // Get the data
    QByteArray entropy;
    auto entropySource = Calamares::getEntropy( 2048, entropy );
    if ( entropySource != Calamares::EntropySource::URandom )
    {
        cWarning() << "Could not get entropy from /dev/urandom for LUKS.";
        return false;
    }

    auto fileResult
        = Calamares::System::instance()->createTargetFile( keyfile, entropy, Calamares::System::WriteMode::Overwrite );
    entropy.fill( 'A' );
    if ( !fileResult )
    {
        cWarning() << "Could not create LUKS keyfile:" << smash( fileResult.code() );
        return false;
    }

    // Give ample time to check that the file was created correctly;
    // we actually expect ls to return pretty-much-instantly.
    auto r = Calamares::System::instance()->targetEnvCommand(
        { "ls", "-la", "/" }, QString(), QString(), std::chrono::seconds( 5 ) );
    cDebug() << "In target system after creating LUKS file" << r.getOutput();
    return true;
}

static bool
setupLuks( const LuksDevice& d, const QString& luks2Hash )
{
    // Get luksDump for this device
    auto luks_dump = Calamares::System::instance()->targetEnvCommand(
        { QStringLiteral( "cryptsetup" ), QStringLiteral( "luksDump" ), d.device },
        QString(),
        QString(),
        std::chrono::seconds( 5 ) );
    if ( luks_dump.getExitCode() != 0 )
    {
        cWarning() << "Could not get LUKS information on " << d.device << ':' << luks_dump.getOutput() << "(exit code"
                   << luks_dump.getExitCode() << ')';
        return false;
    }

    // Check LUKS version
    int luks_version = 0;
    QRegularExpression version_re( QStringLiteral( R"(version:\s*([0-9]))" ),
                                   QRegularExpression::CaseInsensitiveOption );
    QRegularExpressionMatch match = version_re.match( luks_dump.getOutput() );
    if ( !match.hasMatch() )
    {
        cWarning() << "Could not get LUKS version on device: " << d.device;
        return false;
    }
    bool ok;
    luks_version = match.captured( 1 ).toInt( &ok );
    if ( !ok )
    {
        cWarning() << "Could not get LUKS version on device: " << d.device;
        return false;
    }
    cDebug() << "LUKS" << luks_version << " found on device: " << d.device;

    // Check the number of slots used for LUKS1 devices
    if ( luks_version == 1 )
    {
        QRegularExpression slots_re( QStringLiteral( R"(\d+:\s*enabled)" ), QRegularExpression::CaseInsensitiveOption );
        if ( luks_dump.getOutput().count( slots_re ) == 8 )
        {
            cWarning() << "No key slots left on LUKS1 device: " << d.device;
            return false;
        }
    }

    // Add the key to the keyfile
    QStringList args = { QStringLiteral( "cryptsetup" ), QStringLiteral( "luksAddKey" ), d.device, keyfile };
    if ( luks_version == 2 && luks2Hash != QString() )
    {
        args.insert( 2, "--pbkdf" );
        args.insert( 3, luks2Hash );
    }
    auto r
        = Calamares::System::instance()->targetEnvCommand( args, QString(), d.passphrase, std::chrono::seconds( 60 ) );
    if ( r.getExitCode() != 0 )
    {
        cWarning() << "Could not configure LUKS keyfile on" << d.device << ':' << r.getOutput() << "(exit code"
                   << r.getExitCode() << ')';
        return false;
    }
    return true;
}

static QVariantList
partitionsFromGlobalStorage()
{
    Calamares::GlobalStorage* globalStorage = Calamares::JobQueue::instance()->globalStorage();
    return globalStorage->value( QStringLiteral( "partitions" ) ).toList();
}

/// Checks if the partition (represented by @p map) mounts to the given @p path
STATICTEST bool
hasMountPoint( const QVariantMap& map, const QString& path )
{
    const auto v = map.value( QStringLiteral( "mountPoint" ) );
    return v.isValid() && QDir::cleanPath( v.toString() ) == path;
}

STATICTEST bool
isEncrypted( const QVariantMap& map )
{
    return map.contains( QStringLiteral( "luksMapperName" ) );
}

/// Checks for any partition satisfying @p pred
STATICTEST bool
anyPartition( bool ( *pred )( const QVariantMap& ) )
{
    const auto partitions = partitionsFromGlobalStorage();
    return std::find_if( partitions.cbegin(),
                         partitions.cend(),
                         [ &pred ]( const QVariant& partitionVariant ) { return pred( partitionVariant.toMap() ); } )
        != partitions.cend();
}

STATICTEST bool
hasUnencryptedSeparateBoot()
{
    return anyPartition(
        []( const QVariantMap& partition )
        { return hasMountPoint( partition, QStringLiteral( "/boot" ) ) && !isEncrypted( partition ); } );
}

Calamares::JobResult
LuksBootKeyFileJob::exec()
{
    const auto* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( !gs )
    {
        return Calamares::JobResult::internalError(
            "LuksBootKeyFile", "No GlobalStorage defined.", Calamares::JobResult::InvalidConfiguration );
    }
    if ( !gs->contains( "partitions" ) )
    {
        cError() << "No GS[partitions] key.";
        return Calamares::JobResult::internalError(
            "LuksBootKeyFile", tr( "No partitions are defined." ), Calamares::JobResult::InvalidConfiguration );
    }

    LuksDeviceList s( gs->value( "partitions" ) );
    if ( !s.valid )
    {
        cError() << "GS[partitions] is invalid";
        return Calamares::JobResult::internalError(
            "LuksBootKeyFile", tr( "No partitions are defined." ), Calamares::JobResult::InvalidConfiguration );
    }

    cDebug() << "There are" << s.devices.count() << "LUKS partitions";
    if ( s.devices.count() < 1 )
    {
        cDebug() << Logger::SubEntry << "Nothing to do for LUKS.";
        return Calamares::JobResult::ok();
    }

    auto it = std::partition( s.devices.begin(), s.devices.end(), []( const LuksDevice& d ) { return d.isRoot; } );
    for ( const auto& d : s.devices )
    {
        cDebug() << Logger::SubEntry << ( d.isRoot ? "root" : "dev." ) << d.device << "passphrase?"
                 << !d.passphrase.isEmpty();
    }

    if ( it == s.devices.begin() )
    {
        // User has configured non-root partition for encryption
        cDebug() << Logger::SubEntry << "No root partition, skipping keyfile creation.";
        return Calamares::JobResult::ok();
    }

    if ( hasUnencryptedSeparateBoot() )
    {
        // /boot partition is not encrypted, keyfile must not be used.
        cDebug() << Logger::SubEntry << "/boot partition is not encrypted, skipping keyfile creation.";
        return Calamares::JobResult::ok();
    }

    if ( s.devices.first().passphrase.isEmpty() )
    {
        cDebug() << Logger::SubEntry << "No root passphrase.";
        return Calamares::JobResult::error(
            tr( "Encrypted rootfs setup error" ),
            tr( "Root partition %1 is LUKS but no passphrase has been set." ).arg( s.devices.first().device ) );
    }

    if ( !generateTargetKeyfile() )
    {
        return Calamares::JobResult::error(
            tr( "Encrypted rootfs setup error" ),
            tr( "Could not create LUKS key file for root partition %1." ).arg( s.devices.first().device ) );
    }

    for ( const auto& d : s.devices )
    {
        // Skip setupLuks for root partition if system has an unencrypted /boot
        if ( d.isRoot && hasUnencryptedSeparateBoot() )
        {
            continue;
        }

        if ( !setupLuks( d, m_luks2Hash ) )
        {
            // Could not configure the LUKS partition
            // This should not stop the installation: do not return Calamares::JobResult::error.
            cError() << "Encrypted rootfs setup error: could not configure LUKS key file on partition " << d.device;
        }
    }

    return Calamares::JobResult::ok();
}

void
LuksBootKeyFileJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    // Map the value from the config file to accepted values;
    // this is an immediately-invoked lambda which is passed the
    // return value of getString().
    m_luks2Hash = []( const QString& value )
    {
        if ( value == QStringLiteral( "default" ) )
        {
            return QString();  // Empty is used internally for "default from cryptsetup"
        }
        return value.toLower();
    }( Calamares::getString( configurationMap, QStringLiteral( "luks2Hash" ), QString() ) );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( LuksBootKeyFileJobFactory, registerPlugin< LuksBootKeyFileJob >(); )
