/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, 2020, Adriaan de Groot <groot@kde.org>
 *   Copyright 2017, Gabriel Craciunescu <crazy@frugalware.org>
 *   Copyright 2019, Collabora Ltd <arnaud.ferraris@collabora.com>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "GeneralRequirements.h"

#include "CheckerContainer.h"
#include "partman_devices.h"

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

#include "GlobalStorage.h"
#include "JobQueue.h"

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
    cDebug() << "Need at least storage bytes:" << requiredStorageB;
    if ( m_entriesToCheck.contains( "storage" ) )
    {
        enoughStorage = checkEnoughStorage( requiredStorageB );
    }

    qint64 requiredRamB = CalamaresUtils::GiBtoBytes( m_requiredRamGiB );
    cDebug() << "Need at least ram bytes:" << requiredRamB;
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

    using TR = Logger::DebugRow< const char*, MaybeChecked >;
    cDebug() << "GeneralRequirements output:" << TR( "enoughStorage", enoughStorage ) << TR( "enoughRam", enoughRam )
             << TR( "hasPower", hasPower ) << TR( "hasInternet", hasInternet ) << TR( "isRoot", isRoot );

    Calamares::RequirementsList checkEntries;
    foreach ( const QString& entry, m_entriesToCheck )
    {
        if ( entry == "storage" )
        {
            checkEntries.append(
                { entry,
                  [ req = m_requiredStorageGiB ] {
                      return tr( "has at least %1 GiB available drive space" ).arg( req );
                  },
                  [ req = m_requiredStorageGiB ] {
                      return tr( "There is not enough drive space. At least %1 GiB is required." ).arg( req );
                  },
                  enoughStorage,
                  m_entriesToRequire.contains( entry ) } );
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
                  m_entriesToRequire.contains( entry ) } );
        }
        else if ( entry == "power" )
        {
            checkEntries.append( { entry,
                                   [] { return tr( "is plugged in to a power source" ); },
                                   [] { return tr( "The system is not plugged in to a power source." ); },
                                   hasPower,
                                   m_entriesToRequire.contains( entry ) } );
        }
        else if ( entry == "internet" )
        {
            checkEntries.append( { entry,
                                   [] { return tr( "is connected to the Internet" ); },
                                   [] { return tr( "The system is not connected to the Internet." ); },
                                   hasInternet,
                                   m_entriesToRequire.contains( entry ) } );
        }
        else if ( entry == "root" )
        {
            checkEntries.append( { entry,
                                   [] { return tr( "is running the installer as an administrator (root)" ); },
                                   [] {
                                       return Calamares::Settings::instance()->isSetupMode()
                                           ? tr( "The setup program is not running with administrator rights." )
                                           : tr( "The installer is not running with administrator rights." );
                                   },
                                   isRoot,
                                   m_entriesToRequire.contains( entry ) } );
        }
        else if ( entry == "screen" )
        {
            checkEntries.append( { entry,
                                   [] { return tr( "has a screen large enough to show the whole installer" ); },
                                   [] {
                                       return Calamares::Settings::instance()->isSetupMode()
                                           ? tr( "The screen is too small to display the setup program." )
                                           : tr( "The screen is too small to display the installer." );
                                   },
                                   enoughScreen,
                                   false } );
        }
    }
    return checkEntries;
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

    QUrl checkInternetUrl;
    QString checkInternetSetting = CalamaresUtils::getString( configurationMap, "internetCheckUrl" );
    if ( !checkInternetSetting.isEmpty() )
    {
        checkInternetUrl = QUrl( checkInternetSetting.trimmed() );
        if ( !checkInternetUrl.isValid() )
        {
            cWarning() << "GeneralRequirements entry 'internetCheckUrl' is invalid in welcome.conf"
                       << checkInternetSetting << "reverting to default (http://example.com).";
            checkInternetUrl = QUrl( "http://example.com" );
            incompleteConfiguration = true;
        }
    }
    else
    {
        cWarning() << "GeneralRequirements entry 'internetCheckUrl' is undefined in welcome.conf,"
                      "reverting to default (http://example.com).";
        checkInternetUrl = "http://example.com";
        incompleteConfiguration = true;
    }
    if ( checkInternetUrl.isValid() )
    {
        CalamaresUtils::Network::Manager::instance().setCheckHasInternetUrl( checkInternetUrl );
    }

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
    return availableRam >= requiredRam * 0.95;  // because MemTotal is variable
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
