/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "core/PartUtils.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "partition/PartitionSize.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

Config::Config( QObject* parent )
    : QObject( parent )
{
}

const NamedEnumTable< Config::InstallChoice >&
Config::installChoiceNames()
{
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< InstallChoice > names {
        { QStringLiteral( "none" ), InstallChoice::NoChoice },
        { QStringLiteral( "nochoice" ), InstallChoice::NoChoice },
        { QStringLiteral( "alongside" ), InstallChoice::Alongside },
        { QStringLiteral( "erase" ), InstallChoice::Erase },
        { QStringLiteral( "replace" ), InstallChoice::Replace },
        { QStringLiteral( "manual" ), InstallChoice::Manual },
    };
    // clang-format on
    // *INDENT-ON*

    return names;
}

const NamedEnumTable< Config::SwapChoice >&
Config::swapChoiceNames()
{
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< SwapChoice > names {
        { QStringLiteral( "none" ), SwapChoice::NoSwap },
        { QStringLiteral( "small" ), SwapChoice::SmallSwap },
        { QStringLiteral( "suspend" ), SwapChoice::FullSwap },
        { QStringLiteral( "reuse" ), SwapChoice::ReuseSwap },
        { QStringLiteral( "file" ), SwapChoice::SwapFile },
    };
    // clang-format on
    // *INDENT-ON*

    return names;
}

const NamedEnumTable< Config::LuksGeneration >&
Config::luksGenerationNames()
{
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< LuksGeneration > names {
        { QStringLiteral( "luks1" ), LuksGeneration::Luks1 },
        { QStringLiteral( "luks" ), LuksGeneration::Luks1 },
        { QStringLiteral( "luks2" ), LuksGeneration::Luks2 },
    };
    // clang-format on
    // *INDENT-ON*

    return names;
}

Config::SwapChoice
pickOne( const Config::SwapChoiceSet& s )
{
    if ( s.count() == 0 )
    {
        return Config::SwapChoice::NoSwap;
    }
    if ( s.count() == 1 )
    {
        return *( s.begin() );
    }
    if ( s.contains( Config::SwapChoice::NoSwap ) )
    {
        return Config::SwapChoice::NoSwap;
    }
    // Here, count > 1 but NoSwap is not a member.
    return *( s.begin() );
}

static Config::SwapChoiceSet
getSwapChoices( const QVariantMap& configurationMap )
{
    // SWAP SETTINGS
    //
    // This is a bit convoluted because there's legacy settings to handle as well
    // as the new-style list of choices, with mapping back-and-forth.
    if ( configurationMap.contains( "userSwapChoices" )
         && ( configurationMap.contains( "ensureSuspendToDisk" ) || configurationMap.contains( "neverCreateSwap" ) ) )
    {
        cError() << "Partition-module configuration mixes old- and new-style swap settings.";
    }

    if ( configurationMap.contains( "ensureSuspendToDisk" ) )
    {
        cWarning() << "Partition-module setting *ensureSuspendToDisk* is deprecated.";
    }
    bool ensureSuspendToDisk = Calamares::getBool( configurationMap, "ensureSuspendToDisk", true );

    if ( configurationMap.contains( "neverCreateSwap" ) )
    {
        cWarning() << "Partition-module setting *neverCreateSwap* is deprecated.";
    }
    bool neverCreateSwap = Calamares::getBool( configurationMap, "neverCreateSwap", false );

    Config::SwapChoiceSet choices;  // Available swap choices
    if ( configurationMap.contains( "userSwapChoices" ) )
    {
        // We've already warned about overlapping settings with the
        // legacy *ensureSuspendToDisk* and *neverCreateSwap*.
        QStringList l = configurationMap[ "userSwapChoices" ].toStringList();

        for ( const auto& item : l )
        {
            bool ok = false;
            auto v = Config::swapChoiceNames().find( item, ok );
            if ( ok )
            {
                choices.insert( v );
            }
        }

        if ( choices.isEmpty() )
        {
            cWarning() << "Partition-module configuration for *userSwapChoices* is empty:" << l;
            choices.insert( Config::SwapChoice::FullSwap );
        }

        // suspend if it's one of the possible choices; suppress swap only if it's
        // the **only** choice available.
        ensureSuspendToDisk = choices.contains( Config::SwapChoice::FullSwap );
        neverCreateSwap = ( choices.count() == 1 ) && choices.contains( Config::SwapChoice::NoSwap );
    }
    else
    {
        // Convert the legacy settings into a single setting for now.
        if ( neverCreateSwap )
        {
            choices.insert( Config::SwapChoice::NoSwap );
        }
        else if ( ensureSuspendToDisk )
        {
            choices.insert( Config::SwapChoice::FullSwap );
        }
        else
        {
            choices.insert( Config::SwapChoice::SmallSwap );
        }
    }

    // Not all are supported right now // FIXME
    static const char unsupportedSetting[] = "Partition-module does not support *userSwapChoices* setting";

#define COMPLAIN_UNSUPPORTED( x ) \
    if ( choices.contains( x ) ) \
    { \
        bool bogus = false; \
        cWarning() << unsupportedSetting << Config::swapChoiceNames().find( x, bogus ); \
        choices.remove( x ); \
    }

    COMPLAIN_UNSUPPORTED( Config::SwapChoice::ReuseSwap )
#undef COMPLAIN_UNSUPPORTED

    return choices;
}

void
updateGlobalStorage( Config::InstallChoice installChoice, Config::SwapChoice swapChoice )
{
    auto* gs = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    if ( gs )
    {
        QVariantMap m;
        m.insert( "install", Config::installChoiceNames().find( installChoice ) );
        m.insert( "swap", Config::swapChoiceNames().find( swapChoice ) );
        gs->insert( "partitionChoices", m );
    }
}

void
Config::setInstallChoice( int c )
{
    if ( ( c < InstallChoice::NoChoice ) || ( c > InstallChoice::Manual ) )
    {
        cWarning() << "Invalid install choice (int)" << c;
        c = InstallChoice::NoChoice;
    }
    setInstallChoice( static_cast< InstallChoice >( c ) );
}

void
Config::setInstallChoice( InstallChoice c )
{
    if ( c != m_installChoice )
    {
        m_installChoice = c;
        Q_EMIT installChoiceChanged( c );
        ::updateGlobalStorage( c, m_swapChoice );
    }
}

void
Config::setSwapChoice( int c )
{
    if ( ( c < SwapChoice::NoSwap ) || ( c > SwapChoice::SwapFile ) )
    {
        cWarning() << "Invalid swap choice (int)" << c;
        c = SwapChoice::NoSwap;
    }
    setSwapChoice( static_cast< SwapChoice >( c ) );
}

void
Config::setSwapChoice( Config::SwapChoice c )
{
    if ( c != m_swapChoice )
    {
        m_swapChoice = c;
        Q_EMIT swapChoiceChanged( c );
        ::updateGlobalStorage( m_installChoice, c );
    }
}

void
Config::setEraseFsTypeChoice( const QString& choice )
{
    const QString canonicalChoice = PartUtils::canonicalFilesystemName( choice, nullptr );
    if ( canonicalChoice != m_eraseFsTypeChoice )
    {
        m_eraseFsTypeChoice = canonicalChoice;
        Q_EMIT eraseModeFilesystemChanged( canonicalChoice );
    }
}

void
Config::setReplaceFilesystemChoice( const QString& filesystemName )
{
    const QString canonicalChoice = PartUtils::canonicalFilesystemName( filesystemName, nullptr );
    if ( canonicalChoice != m_replaceFileSystemChoice )
    {
        m_replaceFileSystemChoice = canonicalChoice;
        Q_EMIT replaceModeFilesystemChanged( canonicalChoice );
    }
}

bool
Config::acceptPartitionTableType( PartitionTable::TableType tableType ) const
{
    return m_requiredPartitionTableType.empty()
        || m_requiredPartitionTableType.contains( PartitionTable::tableTypeToName( tableType ) );
}

static void
fillGSConfigurationEFI( Calamares::GlobalStorage* gs, const QVariantMap& configurationMap )
{
    // Set up firmwareType global storage entry. This is used, e.g. by the bootloader module.
    QString firmwareType( PartUtils::isEfiSystem() ? QStringLiteral( "efi" ) : QStringLiteral( "bios" ) );
    gs->insert( "firmwareType", firmwareType );

    bool ok = false;
    auto efiConfiguration = Calamares::getSubMap( configurationMap, "efi", ok );

    // Mount Point
    {
        const auto efiSystemPartition = Calamares::getString(
            efiConfiguration,
            "mountPoint",
            Calamares::getString( configurationMap, "efiSystemPartition", QStringLiteral( "/boot/efi" ) ) );
        // This specific GS key is also used by bootloader and grubcfg modules,
        // as well as partition module internalls.
        gs->insert( "efiSystemPartition", efiSystemPartition );
    }

    // Sizes
    {
        const auto efiRecommendedSize = Calamares::getString(
            efiConfiguration, "recommendedSize", Calamares::getString( configurationMap, "efiSystemPartitionSize" ) );
        if ( !efiRecommendedSize.isEmpty() )
        {
            Calamares::Partition::PartitionSize part_size = Calamares::Partition::PartitionSize( efiRecommendedSize );
            if ( part_size.isValid() )
            {
                gs->insert( PartUtils::efiFilesystemRecommendedSizeGSKey(), part_size.toBytes() );

                // Assign long long int to long unsigned int to prevent compilation warning,
                // checks for loss-of-precision in the conversion.
                auto byte_part_size = part_size.toBytes();
                if ( byte_part_size != PartUtils::efiFilesystemRecommendedSize() )
                {
                    cWarning() << "EFI partition size" << efiRecommendedSize << "has been adjusted to"
                               << PartUtils::efiFilesystemRecommendedSize() << "bytes";
                }
            }
            else
            {
                cWarning() << "EFI partition size" << efiRecommendedSize << "is invalid, ignored";
            }
        }

        const auto efiMinimumSize = Calamares::getString( efiConfiguration, "minimumSize" );
        if ( !efiMinimumSize.isEmpty() )
        {
            Calamares::Partition::PartitionSize part_size = Calamares::Partition::PartitionSize( efiMinimumSize );
            if ( part_size.isValid() )
            {
                if ( part_size.toBytes() > PartUtils::efiFilesystemRecommendedSize() )
                {
                    cWarning() << "EFI minimum size" << efiMinimumSize << "is larger than the recommended size"
                               << efiRecommendedSize << ", ignored.";
                }
                else
                {
                    gs->insert( PartUtils::efiFilesystemMinimumSizeGSKey(), part_size.toBytes() );
                }
            }
        }
    }

    // Name (label) of partition
    {
        const auto efiLabel = Calamares::getString(
            efiConfiguration, "label", Calamares::getString( configurationMap, "efiSystemPartitionName" ) );

        if ( !efiLabel.isEmpty() )
        {
            gs->insert( "efiSystemPartitionName", efiLabel );
        }
    }
}

void
Config::fillConfigurationFSTypes( const QVariantMap& configurationMap )
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    // The defaultFileSystemType setting needs a bit more processing,
    // as we want to cover various cases (such as different cases)
    QString fsName = Calamares::getString( configurationMap, "defaultFileSystemType" );
    QString fsRealName;
    FileSystem::Type fsType = FileSystem::Type::Unknown;
    if ( fsName.isEmpty() )
    {
        cWarning() << "Partition-module setting *defaultFileSystemType* is missing, will use ext4";
        fsRealName = PartUtils::canonicalFilesystemName( QStringLiteral( "ext4" ), &fsType );
    }
    else
    {
        fsRealName = PartUtils::canonicalFilesystemName( fsName, &fsType );
        if ( fsType == FileSystem::Type::Unknown )
        {
            cWarning() << "Partition-module setting *defaultFileSystemType* is bad (" << fsName
                       << ") using ext4 instead";
            fsRealName = PartUtils::canonicalFilesystemName( QStringLiteral( "ext4" ), &fsType );
        }
        else if ( fsRealName != fsName )
        {
            cWarning() << "Partition-module setting *defaultFileSystemType* changed to" << fsRealName;
        }
    }
    Q_ASSERT( fsType != FileSystem::Type::Unknown );
    m_defaultFsType = fsType;
    gs->insert( "defaultFileSystemType", fsRealName );

    // TODO: canonicalize the names? How is translation supposed to work?
    m_eraseFsTypes = Calamares::getStringList( configurationMap, "availableFileSystemTypes" );
    if ( !m_eraseFsTypes.contains( fsRealName ) )
    {
        if ( !m_eraseFsTypes.isEmpty() )
        {
            // Explicitly set, and doesn't include the default
            cWarning() << "Partition-module *availableFileSystemTypes* does not contain the default" << fsRealName;
            m_eraseFsTypes.prepend( fsRealName );
        }
        else
        {
            // Not explicitly set, so it's empty; don't complain
            m_eraseFsTypes = QStringList { fsRealName };
        }
    }

    // Set LUKS file system based on luksGeneration provided, defaults to 'luks'.
    bool nameFound = false;
    Config::LuksGeneration luksGeneration
        = luksGenerationNames().find( Calamares::getString( configurationMap, "luksGeneration" ), nameFound );
    if ( !nameFound )
    {
        cWarning() << "Partition-module setting *luksGeneration* not found or invalid. Defaulting to luks1.";
        luksGeneration = Config::LuksGeneration::Luks1;
    }
    m_luksFileSystemType = luksGeneration;
    gs->insert( "luksFileSystemType", luksGenerationNames().find( luksGeneration ) );

    Q_ASSERT( !m_eraseFsTypes.isEmpty() );
    Q_ASSERT( m_eraseFsTypes.contains( fsRealName ) );
    m_eraseFsTypeChoice = fsRealName;
    m_replaceFileSystemChoice = fsRealName;
    Q_EMIT eraseModeFilesystemChanged( m_eraseFsTypeChoice );
    Q_EMIT replaceModeFilesystemChanged( m_replaceFileSystemChoice );
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    // Settings that overlap with the Welcome module
    m_requiredStorageGiB = Calamares::getDouble( configurationMap, "requiredStorage", -1.0 );
    m_swapChoices = getSwapChoices( configurationMap );

    bool nameFound = false;  // In the name table (ignored, falls back to first entry in table)
    m_initialInstallChoice
        = installChoiceNames().find( Calamares::getString( configurationMap, "initialPartitioningChoice" ), nameFound );
    setInstallChoice( m_initialInstallChoice );

    m_initialSwapChoice
        = swapChoiceNames().find( Calamares::getString( configurationMap, "initialSwapChoice" ), nameFound );
    if ( !m_swapChoices.contains( m_initialSwapChoice ) )
    {
        cWarning() << "Configuration for *initialSwapChoice* is not one of the *userSwapChoices*";
        if ( nameFound )
        {
            cWarning() << Logger::SubEntry << "Choice" << swapChoiceNames().find( m_initialSwapChoice ) << "added.";
            m_swapChoices.insert( m_initialSwapChoice );
        }
        m_initialSwapChoice = pickOne( m_swapChoices );
    }
    setSwapChoice( m_initialSwapChoice );

    m_allowZfsEncryption = Calamares::getBool( configurationMap, "allowZfsEncryption", true );

    m_allowManualPartitioning = Calamares::getBool( configurationMap, "allowManualPartitioning", true );
    m_preCheckEncryption = Calamares::getBool( configurationMap, "preCheckEncryption", false );
    m_showNotEncryptedBootMessage = Calamares::getBool( configurationMap, "showNotEncryptedBootMessage", true );
    m_requiredPartitionTableType = Calamares::getStringList( configurationMap, "requiredPartitionTableType" );

    {
        bool bogus = true;
        const auto lvmConfiguration = Calamares::getSubMap( configurationMap, "lvm", bogus );
        m_isLVMEnabled = Calamares::getBool( lvmConfiguration, "enable", true );
    }

    m_essentialMounts= Calamares::getStringList( configurationMap, "essentialMounts" );

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    gs->insert( "armInstall", Calamares::getBool( configurationMap, "armInstall", false ) );
    fillGSConfigurationEFI( gs, configurationMap );
    fillConfigurationFSTypes( configurationMap );
}

void
Config::fillGSSecondaryConfiguration() const
{
    // If there's no setting (e.g. from the welcome page) for required storage
    // then use ours, if it was set.
    auto* gs = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    if ( m_requiredStorageGiB >= 0.0 && gs && !gs->contains( "requiredStorageGiB" ) )
    {
        gs->insert( "requiredStorageGiB", m_requiredStorageGiB );
    }
}
