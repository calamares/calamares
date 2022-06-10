/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2017 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2017 Gabriel Craciunescu <crazy@frugalware.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "GeneralRequirements.h"

#include "CheckerContainer.h"
#include "partman_devices.h"

#include "CalamaresVersion.h"  // For development-or-not
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"
#include "modulesystem/Requirement.h"
#include "network/Manager.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/Units.h"
#include "utils/Variant.h"
#include "widgets/WaitingWidget.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QGuiApplication>
#include <QScreen>

#include <unistd.h>  //geteuid

GeneralRequirements::GeneralRequirements( QObject* parent )
    : QObject( parent )
    , m_requiredStorageGiB( -1 )
    , m_requiredRamGiB( -1 )
{
}

static QSize
biggestSingleScreen()
{
    QSize s;
    for ( const auto* screen : QGuiApplication::screens() )
    {
        QSize thisScreen = screen->availableSize();
        if ( !s.isValid() || ( s.width() * s.height() < thisScreen.width() * thisScreen.height() ) )
        {
            s = thisScreen;
        }
    }
    return s;
}

/** @brief Distinguish has-not-been-checked-at-all from false.
 *
 */
struct MaybeChecked
{
    bool hasBeenChecked = false;
    bool value = false;

    MaybeChecked& operator=( bool b )
    {
        hasBeenChecked = true;
        value = b;
        return *this;
    }

    operator bool() const { return value; }
};

QDebug&
operator<<( QDebug& s, const MaybeChecked& c )
{
    if ( c.hasBeenChecked )
    {
        s << c.value;
    }
    else
    {
        s << "unchecked";
    }
    return s;
}

Calamares::RequirementsList
GeneralRequirements::checkRequirements()
{
    QSize availableSize = biggestSingleScreen();

    MaybeChecked enoughStorage;
    MaybeChecked enoughRam;
    MaybeChecked hasPower;
    MaybeChecked hasInternet;
    MaybeChecked isRoot;
    bool enoughScreen = availableSize.isValid() && ( availableSize.width() >= CalamaresUtils::windowMinimumWidth )
        && ( availableSize.height() >= CalamaresUtils::windowMinimumHeight );

    qint64 requiredStorageB = CalamaresUtils::GiBtoBytes( m_requiredStorageGiB );
    if ( m_entriesToCheck.contains( "storage" ) )
    {
        enoughStorage = checkEnoughStorage( requiredStorageB );
    }

    qint64 requiredRamB = CalamaresUtils::GiBtoBytes( m_requiredRamGiB );
    if ( m_entriesToCheck.contains( "ram" ) )
    {
        enoughRam = checkEnoughRam( requiredRamB );
    }

    if ( m_entriesToCheck.contains( "power" ) )
    {
        hasPower = checkHasPower();
    }

    if ( m_entriesToCheck.contains( "internet" ) )
    {
        hasInternet = checkHasInternet();
    }

    if ( m_entriesToCheck.contains( "root" ) )
    {
        isRoot = checkIsRoot();
    }

    using TNum = Logger::DebugRow< const char*, qint64 >;
    using TR = Logger::DebugRow< const char*, MaybeChecked >;
    // clang-format off
    cDebug() << "GeneralRequirements output:"
             << TNum( "storage", requiredStorageB )
             << TR( "enoughStorage", enoughStorage )
             << TNum( "RAM", requiredRamB )
             << TR( "enoughRam", enoughRam )
             << TR( "hasPower", hasPower )
             << TR( "hasInternet", hasInternet )
             << TR( "isRoot", isRoot );
    // clang-format on

    Calamares::RequirementsList checkEntries;
    foreach ( const QString& entry, m_entriesToCheck )
    {
        const bool required = m_entriesToRequire.contains( entry );
        if ( entry == "storage" )
        {
            checkEntries.append(
                { entry,
                  [ req = m_requiredStorageGiB ]
                  {
                      return tr( "Please ensure the system has at least %1 GiB available drive space." ).arg( req )
                          + QStringLiteral( "<br/><br/>" )
                          + tr( "Available drive space is all of the hard disks and SSDs connected to the system." );
                  },
                  [ req = m_requiredStorageGiB ]
                  { return tr( "There is not enough drive space. At least %1 GiB is required." ).arg( req ); },
                  enoughStorage,
                  required } );
        }
        else if ( entry == "ram" )
        {
            checkEntries.append(
                { entry,
                  [ req = m_requiredRamGiB ] { return tr( "has at least %1 GiB working memory" ).arg( req ); },
                  [ req = m_requiredRamGiB ] {
                      return tr( "The system does not have enough working memory. At least %1 GiB is required." )
                          .arg( req );
                  },
                  enoughRam,
                  required } );
        }
        else if ( entry == "power" )
        {
            checkEntries.append( { entry,
                                   [] { return tr( "is plugged in to a power source" ); },
                                   [] { return tr( "The system is not plugged in to a power source." ); },
                                   hasPower,
                                   required } );
        }
        else if ( entry == "internet" )
        {
            checkEntries.append( { entry,
                                   [] { return tr( "is connected to the Internet" ); },
                                   [] { return tr( "The system is not connected to the Internet." ); },
                                   hasInternet,
                                   required } );
        }
        else if ( entry == "root" )
        {
            checkEntries.append( { entry,
                                   [] { return tr( "is running the installer as an administrator (root)" ); },
                                   []
                                   {
                                       return Calamares::Settings::instance()->isSetupMode()
                                           ? tr( "The setup program is not running with administrator rights." )
                                           : tr( "The installer is not running with administrator rights." );
                                   },
                                   isRoot,
                                   required } );
        }
        else if ( entry == "screen" )
        {
            checkEntries.append( { entry,
                                   [] { return tr( "has a screen large enough to show the whole installer" ); },
                                   []
                                   {
                                       return Calamares::Settings::instance()->isSetupMode()
                                           ? tr( "The screen is too small to display the setup program." )
                                           : tr( "The screen is too small to display the installer." );
                                   },
                                   enoughScreen,
                                   required } );
        }
#ifdef CALAMARES_VERSION_RC
        if ( entry == "false" )
        {
            checkEntries.append( { entry,
                                   [] { return tr( "is always false" ); },
                                   [] { return tr( "The computer says no." ); },
                                   false,
                                   required } );
        }
        if ( entry == "slow-false" )
        {
            sleep(3);
            checkEntries.append( { entry,
                                   [] { return tr( "is always false (slowly)" ); },
                                   [] { return tr( "The computer says no (slowly)." ); },
                                   false,
                                   required } );
        }
        if ( entry == "true" )
        {
            checkEntries.append( { entry,
                                   [] { return tr( "is always true" ); },
                                   [] { return tr( "The computer says yes." ); },
                                   true,
                                   required } );
        }
        if ( entry == "slow-true" )
        {
            sleep(3);
            checkEntries.append( { entry,
                                   [] { return tr( "is always true (slowly)" ); },
                                   [] { return tr( "The computer says yes (slowly)." ); },
                                   true,
                                   required } );
        }
        if ( entry == "snark" )
        {
            static unsigned int snark_count = 0;
            checkEntries.append( { entry,
                                   [] { return tr( "is checked three times." ); },
                                   []
                                   {
                                       return tr( "The snark has not been checked three times.",
                                                  "The (some mythological beast) has not been checked three times." );
                                   },
                                   ++snark_count > 3,
                                   required } );
        }
#endif
    }
    return checkEntries;
}

/** @brief Loads the check-internet URLs
 *
 * There may be zero or one or more URLs specified; returns
 * @c true if the configuration is incomplete or damaged in some way.
 */
static bool
getCheckInternetUrls( const QVariantMap& configurationMap )
{
    const QString exampleUrl = QStringLiteral( "http://example.com" );

    bool incomplete = false;
    QStringList checkInternetSetting = CalamaresUtils::getStringList( configurationMap, "internetCheckUrl" );
    if ( !checkInternetSetting.isEmpty() )
    {
        QVector< QUrl > urls;
        for ( const auto& urlString : qAsConst( checkInternetSetting ) )
        {
            QUrl url( urlString.trimmed() );
            if ( url.isValid() )
            {
                urls.append( url );
            }
            else
            {
                cWarning() << "GeneralRequirements entry 'internetCheckUrl' in welcome.conf contains invalid"
                           << urlString;
            }
        }

        if ( urls.empty() )
        {
            cWarning() << "GeneralRequirements entry 'internetCheckUrl' contains no valid URLs, "
                       << "reverting to default (" << exampleUrl << ").";
            CalamaresUtils::Network::Manager::instance().setCheckHasInternetUrl( QUrl( exampleUrl ) );
            incomplete = true;
        }
        else
        {
            CalamaresUtils::Network::Manager::instance().setCheckHasInternetUrl( urls );
        }
    }
    else
    {
        cWarning() << "GeneralRequirements entry 'internetCheckUrl' is undefined in welcome.conf, "
                      "reverting to default ("
                   << exampleUrl << ").";
        CalamaresUtils::Network::Manager::instance().setCheckHasInternetUrl( QUrl( exampleUrl ) );
        incomplete = true;
    }
    return incomplete;
}


void
GeneralRequirements::setConfigurationMap( const QVariantMap& configurationMap )
{
    bool incompleteConfiguration = false;

    if ( configurationMap.contains( "check" ) && configurationMap.value( "check" ).type() == QVariant::List )
    {
        m_entriesToCheck.clear();
        m_entriesToCheck.append( configurationMap.value( "check" ).toStringList() );
    }
    else
    {
        cWarning() << "GeneralRequirements entry 'check' is incomplete.";
        incompleteConfiguration = true;
    }

    if ( configurationMap.contains( "required" ) && configurationMap.value( "required" ).type() == QVariant::List )
    {
        m_entriesToRequire.clear();
        m_entriesToRequire.append( configurationMap.value( "required" ).toStringList() );
    }
    else
    {
        cWarning() << "GeneralRequirements entry 'required' is incomplete.";
        incompleteConfiguration = true;
    }

#ifdef WITHOUT_LIBPARTED
    if ( m_entriesToCheck.contains( "storage" ) || m_entriesToRequire.contains( "storage" ) )
    {
        // Warn, but also drop the required bit because otherwise installation
        // will be impossible (because the check always returns false).
        cWarning() << "GeneralRequirements checks 'storage' but libparted is disabled.";
        m_entriesToCheck.removeAll( "storage" );
        m_entriesToRequire.removeAll( "storage" );
    }
#endif

    // Help out with consistency, but don't fix
    for ( const auto& r : m_entriesToRequire )
        if ( !m_entriesToCheck.contains( r ) )
        {
            cWarning() << "GeneralRequirements requires" << r << "but does not check it.";
        }

    if ( configurationMap.contains( "requiredStorage" )
         && ( configurationMap.value( "requiredStorage" ).type() == QVariant::Double
              || configurationMap.value( "requiredStorage" ).type() == QVariant::LongLong ) )
    {
        bool ok = false;
        m_requiredStorageGiB = configurationMap.value( "requiredStorage" ).toDouble( &ok );
        if ( !ok )
        {
            cWarning() << "GeneralRequirements entry 'requiredStorage' is invalid.";
            m_requiredStorageGiB = 3.;
        }

        Calamares::JobQueue::instance()->globalStorage()->insert( "requiredStorageGiB", m_requiredStorageGiB );
    }
    else
    {
        cWarning() << "GeneralRequirements entry 'requiredStorage' is missing.";
        m_requiredStorageGiB = 3.;
        incompleteConfiguration = true;
    }

    if ( configurationMap.contains( "requiredRam" )
         && ( configurationMap.value( "requiredRam" ).type() == QVariant::Double
              || configurationMap.value( "requiredRam" ).type() == QVariant::LongLong ) )
    {
        bool ok = false;
        m_requiredRamGiB = configurationMap.value( "requiredRam" ).toDouble( &ok );
        if ( !ok )
        {
            cWarning() << "GeneralRequirements entry 'requiredRam' is invalid.";
            m_requiredRamGiB = 1.;
            incompleteConfiguration = true;
        }
    }
    else
    {
        cWarning() << "GeneralRequirements entry 'requiredRam' is missing.";
        m_requiredRamGiB = 1.;
        incompleteConfiguration = true;
    }

    incompleteConfiguration |= getCheckInternetUrls( configurationMap );

    if ( incompleteConfiguration )
    {
        cWarning() << "GeneralRequirements configuration map:" << Logger::DebugMap( configurationMap );
    }
}


bool
GeneralRequirements::checkEnoughStorage( qint64 requiredSpace )
{
#ifdef WITHOUT_LIBPARTED
    Q_UNUSED( requiredSpace )
    cWarning() << "GeneralRequirements is configured without libparted.";
    return false;
#else
    return check_big_enough( requiredSpace );
#endif
}


bool
GeneralRequirements::checkEnoughRam( qint64 requiredRam )
{
    // Ignore the guesstimate-factor; we get an under-estimate
    // which is probably the usable RAM for programs.
    quint64 availableRam = CalamaresUtils::System::instance()->getTotalMemoryB().first;
    return double( availableRam ) >= double( requiredRam ) * 0.95;  // cast to silence 64-bit-int conversion to double
}


bool
GeneralRequirements::checkBatteryExists()
{
    const QFileInfo basePath( "/sys/class/power_supply" );

    if ( !( basePath.exists() && basePath.isDir() ) )
    {
        return false;
    }

    QDir baseDir( basePath.absoluteFilePath() );
    const auto entries = baseDir.entryList( QDir::AllDirs | QDir::Readable | QDir::NoDotAndDotDot );
    for ( const auto& item : entries )
    {
        QFileInfo typePath( baseDir.absoluteFilePath( QString( "%1/type" ).arg( item ) ) );
        QFile typeFile( typePath.absoluteFilePath() );
        if ( typeFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            if ( typeFile.readAll().startsWith( "Battery" ) )
            {
                return true;
            }
        }
    }

    return false;
}


bool
GeneralRequirements::checkHasPower()
{
    const QString UPOWER_SVC_NAME( "org.freedesktop.UPower" );
    const QString UPOWER_INTF_NAME( "org.freedesktop.UPower" );
    const QString UPOWER_PATH( "/org/freedesktop/UPower" );

    if ( !checkBatteryExists() )
    {
        return true;
    }

    cDebug() << "A battery exists, checking for mains power.";
    QDBusInterface upowerIntf( UPOWER_SVC_NAME, UPOWER_PATH, UPOWER_INTF_NAME, QDBusConnection::systemBus() );

    bool onBattery = upowerIntf.property( "OnBattery" ).toBool();

    if ( !upowerIntf.isValid() )
    {
        // We can't talk to upower but we're obviously up and running
        // so I guess we got that going for us, which is nice...
        return true;
    }

    // If a battery exists but we're not using it, means we got mains
    // power.
    return !onBattery;
}


bool
GeneralRequirements::checkHasInternet()
{
    auto& nam = CalamaresUtils::Network::Manager::instance();
    bool hasInternet = nam.checkHasInternet();
    Calamares::JobQueue::instance()->globalStorage()->insert( "hasInternet", hasInternet );
    return hasInternet;
}


bool
GeneralRequirements::checkIsRoot()
{
    return !geteuid();
}
