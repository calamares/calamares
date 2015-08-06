/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "RequirementsChecker.h"

#include "CheckerWidget.h"
#include "partman_devices.h"

#include "widgets/WaitingWidget.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/CalamaresUtilsSystem.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include <QBoxLayout>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QProcess>
#include <QTimer>

#include <unistd.h> //geteuid

RequirementsChecker::RequirementsChecker( QObject* parent )
    : QObject( parent )
    , m_widget( new QWidget() )
    , m_actualWidget( new CheckerWidget() )
    , m_verdict( false )
    , m_requiredStorageGB( -1 )
{
    QBoxLayout* mainLayout = new QHBoxLayout;
    m_widget->setLayout( mainLayout );
    CalamaresUtils::unmarginLayout( mainLayout );

    WaitingWidget* waitingWidget = new WaitingWidget( QString() );
    mainLayout->addWidget( waitingWidget );
    CALAMARES_RETRANSLATE( waitingWidget->setText( tr( "Gathering system information..." ) ); )

    QTimer* timer = new QTimer;
    timer->setSingleShot( true );
    connect( timer, &QTimer::timeout,
             [=]()
    {
        bool enoughStorage = false;
        bool enoughRam = false;
        bool hasPower = false;
        bool hasInternet = false;
        bool isRoot = false;

        qint64 requiredStorageB = m_requiredStorageGB * 1073741824L; /*powers of 2*/
        cDebug() << "Need at least storage bytes:" << requiredStorageB;
        if ( m_entriesToCheck.contains( "storage" ) )
            enoughStorage = checkEnoughStorage( requiredStorageB );

        qint64 requiredRamB = m_requiredRamGB * 1073741824L; /*powers of 2*/
        cDebug() << "Need at least ram bytes:" << requiredRamB;
        if ( m_entriesToCheck.contains( "ram" ) )
            enoughRam = checkEnoughRam( requiredRamB );

        if ( m_entriesToCheck.contains( "power" ) )
            hasPower = checkHasPower();

        if ( m_entriesToCheck.contains( "internet" ) )
            hasInternet = checkHasInternet();

        if ( m_entriesToCheck.contains( "root" ) )
            isRoot = checkIsRoot();

        cDebug() << "enoughStorage, enoughRam, hasPower, hasInternet, isRoot: "
                 << enoughStorage << enoughRam << hasPower << hasInternet << isRoot;

        QList< PrepareEntry > checkEntries;
        foreach ( const QString& entry, m_entriesToCheck )
        {
            if ( entry == "storage" )
                checkEntries.append( {
                    entry,
                    [this]{ return tr( "has at least %1 GB available drive space" )
                        .arg( m_requiredStorageGB ); },
                    [this]{ return tr( "There is not enough drive space. At least %1 GB is required." )
                        .arg( m_requiredStorageGB ); },
                    enoughStorage,
                    m_entriesToRequire.contains( entry )
                } );
            else if ( entry == "ram" )
                checkEntries.append( {
                    entry,
                    [this]{ return tr( "has at least %1 GB working memory" )
                        .arg( m_requiredRamGB ); },
                    [this]{ return tr( "The system does not have enough working memory. At least %1 GB is required." )
                        .arg( m_requiredRamGB ); },
                    enoughRam,
                    m_entriesToRequire.contains( entry )
                } );
            else if ( entry == "power" )
                checkEntries.append( {
                    entry,
                    [this]{ return tr( "is plugged in to a power source" ); },
                    [this]{ return tr( "The system is not plugged in to a power source." ); },
                    hasPower,
                    m_entriesToRequire.contains( entry )
                } );
            else if ( entry == "internet" )
                checkEntries.append( {
                    entry,
                    [this]{ return tr( "is connected to the Internet" ); },
                    [this]{ return tr( "The system is not connected to the Internet." ); },
                    hasInternet,
                    m_entriesToRequire.contains( entry )
                } );
            else if ( entry == "root" )
                checkEntries.append( {
                    entry,
                    [this]{ return QString(); }, //we hide it
                    [this]{ return tr( "The installer is not running with administrator rights." ); },
                    isRoot,
                    m_entriesToRequire.contains( entry )
                } );

        }

        m_actualWidget->init( checkEntries );
        m_widget->layout()->removeWidget( waitingWidget );
        waitingWidget->deleteLater();
        m_actualWidget->setParent( m_widget );
        m_widget->layout()->addWidget( m_actualWidget );

        bool canGoNext = true;
        foreach ( const PrepareEntry& entry, checkEntries )
        {
            if ( !entry.checked && entry.required )
            {
                canGoNext = false;
                break;
            }
        }
        m_verdict = canGoNext;
        emit verdictChanged( m_verdict );

        if ( canGoNext )
            detectFirmwareType();

        timer->deleteLater();
    } );
    timer->start( 0 );

    emit verdictChanged( true );
}


RequirementsChecker::~RequirementsChecker()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}


QWidget*
RequirementsChecker::widget() const
{
    return m_widget;
}


void
RequirementsChecker::setConfigurationMap( const QVariantMap& configurationMap )
{
    if ( configurationMap.contains( "requiredStorage" ) &&
         configurationMap.value( "requiredStorage" ).type() == QVariant::Double )
    {
        bool ok = false;
        m_requiredStorageGB = configurationMap.value( "requiredStorage" ).toDouble( &ok );
        if ( !ok )
            m_requiredStorageGB = 3.;

        Calamares::JobQueue::instance()->globalStorage()->insert( "requiredStorageGB", m_requiredStorageGB );
    }
    else
    {
        m_requiredStorageGB = 3.;
    }

    if ( configurationMap.contains( "requiredRam" ) &&
         configurationMap.value( "requiredRam" ).type() == QVariant::Double )
    {
        bool ok = false;
        m_requiredRamGB = configurationMap.value( "requiredRam" ).toDouble( &ok );
        if ( !ok )
            m_requiredRamGB = 1.;
    }
    else
    {
        m_requiredRamGB = 1.;
    }

    if ( configurationMap.contains( "check" ) &&
         configurationMap.value( "check" ).type() == QVariant::List )
    {
        m_entriesToCheck.clear();
        m_entriesToCheck.append( configurationMap.value( "check" ).toStringList() );
    }

    if ( configurationMap.contains( "required" ) &&
         configurationMap.value( "required" ).type() == QVariant::List )
    {
        m_entriesToRequire.clear();
        m_entriesToRequire.append( configurationMap.value( "required" ).toStringList() );
    }
}


bool
RequirementsChecker::verdict() const
{
    return m_verdict;
}


bool
RequirementsChecker::checkEnoughStorage( qint64 requiredSpace )
{
    return check_big_enough( requiredSpace );
}


bool
RequirementsChecker::checkEnoughRam( qint64 requiredRam )
{
    qint64 availableRam = CalamaresUtils::System::instance()->getPhysicalMemoryB();
    if ( !availableRam )
        availableRam = CalamaresUtils::System::instance()->getTotalMemoryB();
    return availableRam >= requiredRam * 0.95; // because MemTotal is variable
}


bool
RequirementsChecker::checkBatteryExists()
{
    const QFileInfo basePath( "/sys/class/power_supply" );

    if ( !( basePath.exists() && basePath.isDir() ) )
        return false;

    QDir baseDir( basePath.absoluteFilePath() );
    foreach ( auto item, baseDir.entryList( QDir::AllDirs |
                                            QDir::Readable |
                                            QDir::NoDotAndDotDot ) )
    {
        QFileInfo typePath( baseDir.absoluteFilePath( QString( "%1/type" )
                                                      .arg( item ) ) );
        QFile typeFile( typePath.absoluteFilePath() );
        if ( typeFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            if ( typeFile.readAll().startsWith( "Battery" ) )
                return true;
        }
    }

    return false;
}


bool
RequirementsChecker::checkHasPower()
{
    const QString UPOWER_SVC_NAME( "org.freedesktop.UPower" );
    const QString UPOWER_INTF_NAME( "org.freedesktop.UPower" );
    const QString UPOWER_PATH( "/org/freedesktop/UPower" );

    if ( !checkBatteryExists() )
        return true;

    cDebug() << "A battery exists, checking for mains power.";
    QDBusInterface upowerIntf( UPOWER_SVC_NAME,
                               UPOWER_PATH,
                               UPOWER_INTF_NAME,
                               QDBusConnection::systemBus(), 0 );

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
RequirementsChecker::checkHasInternet()
{
    const QString NM_SVC_NAME( "org.freedesktop.NetworkManager" );
    const QString NM_INTF_NAME( "org.freedesktop.NetworkManager" );
    const QString NM_PATH( "/org/freedesktop/NetworkManager" );
    const int NM_STATE_CONNECTED_GLOBAL = 70;

    QDBusInterface nmIntf( NM_SVC_NAME,
                           NM_PATH,
                           NM_INTF_NAME,
                           QDBusConnection::systemBus(), 0 );

    bool ok = false;
    int nmState = nmIntf.property( "state" ).toInt( &ok );

    if ( !ok || !nmIntf.isValid() )
    {
        // We can't talk to NM, so no idea.  Wild guess: we're connected
        // using ssh with X forwarding, and are therefore connected.  This
        // allows us to proceed with a minimum of complaint.
        return true;
    }

    return nmState == NM_STATE_CONNECTED_GLOBAL;
}


bool
RequirementsChecker::checkIsRoot()
{
    return !geteuid();
}


void
RequirementsChecker::detectFirmwareType()
{
    QString fwType = QFile::exists( "/sys/firmware/efi/efivars" ) ? "efi" : "bios";
    Calamares::JobQueue::instance()->globalStorage()->insert( "firmwareType", fwType );
}
