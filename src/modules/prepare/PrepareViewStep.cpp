/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "PrepareViewStep.h"

#include "PreparePage.h"
#include "partman_devices.h"

#include "widgets/QtWaitingSpinner.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"

#include <QBoxLayout>
#include <QLabel>
#include <QProcess>

PrepareViewStep::PrepareViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new QWidget() )
    , m_actualWidget( new PreparePage() )
    , m_nextEnabled( false )
    , m_requiredStorageGB( -1 )
{
    QBoxLayout* mainLayout = new QHBoxLayout;
    m_widget->setLayout( mainLayout );
    CalamaresUtils::unmarginLayout( mainLayout );

    QWidget* waitingWidget = new QWidget;
    {
        QBoxLayout* waitingLayout = new QVBoxLayout;
        waitingWidget->setLayout( waitingLayout );
        waitingLayout->addStretch();
        QBoxLayout* pbLayout = new QHBoxLayout;
        waitingLayout->addLayout( pbLayout );
        pbLayout->addStretch();

        QtWaitingSpinner* spnr = new QtWaitingSpinner();
        pbLayout->addWidget( spnr );

        pbLayout->addStretch();

        QLabel* waitingLabel = new QLabel( "Gathering system information..." );

        int spnrSize = waitingLabel->fontMetrics().height() * 4;
        spnr->setFixedSize( spnrSize, spnrSize );
        spnr->setRadius( spnrSize / 2 );
        spnr->setLength( spnrSize / 2 );
        spnr->setWidth( spnrSize / 8 );
        spnr->start();

        waitingLabel->setAlignment( Qt::AlignCenter);
        waitingLayout->addSpacing( spnrSize / 2 );
        waitingLayout->addWidget( waitingLabel );
        waitingLayout->addStretch();

        mainLayout->addWidget( waitingWidget );

        CalamaresUtils::unmarginLayout( waitingLayout );
    }

    QTimer* timer = new QTimer;
    timer->setSingleShot( true );
    connect( timer, &QTimer::timeout,
             [=]()
    {
        bool enoughStorage, enoughRam, hasPower, hasInternet;

        qint64 requiredStorageB = m_requiredStorageGB * 1073741824L; /*powers of 2*/
        cDebug() << "Need at least storage bytes:" << requiredStorageB;
        enoughStorage = checkEnoughStorage( requiredStorageB );

        qint64 requiredRamB = m_requiredRamGB * 1073741824L; /*powers of 2*/
        cDebug() << "Need at least ram bytes:" << requiredRamB;
        enoughRam = checkEnoughRam( requiredRamB );

        hasPower = checkHasPower();
        hasInternet = checkHasInternet();
        cDebug() << "enoughStorage, enoughRam, hasPower, hasInternet: "
                 << enoughStorage << enoughRam << hasPower << hasInternet;

        m_actualWidget->init();
        m_widget->layout()->removeWidget( waitingWidget );
        waitingWidget->deleteLater();
        m_widget->layout()->addWidget( m_actualWidget );
        m_nextEnabled = true;
        emit nextStatusChanged( m_nextEnabled );
        timer->deleteLater();
    } );
    timer->start( 0 );

    emit nextStatusChanged( true );
}


PrepareViewStep::~PrepareViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}


QString
PrepareViewStep::prettyName() const
{
    return tr( "Prepare" );
}


QWidget*
PrepareViewStep::widget()
{
    return m_widget;
}


void
PrepareViewStep::next()
{
    emit done();
}


void
PrepareViewStep::back()
{}


bool
PrepareViewStep::isNextEnabled() const
{
    return m_nextEnabled;
}


bool
PrepareViewStep::isAtBeginning() const
{
    return true;
}


bool
PrepareViewStep::isAtEnd() const
{
    return true;
}


QList< Calamares::job_ptr >
PrepareViewStep::jobs() const
{
    return QList< Calamares::job_ptr >();
}


void
PrepareViewStep::onLeave()
{
}


void
PrepareViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    if ( configurationMap.contains( "requiredStorage" ) &&
         configurationMap.value( "requiredStorage" ).type() == QVariant::Double )
    {
        bool ok = false;
        m_requiredStorageGB = configurationMap.value( "requiredStorage" ).toDouble( &ok );
        if ( !ok )
            m_requiredStorageGB = 3.;
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
}


bool
PrepareViewStep::checkEnoughStorage( qint64 requiredSpace )
{
    return check_big_enough( requiredSpace );
}


bool
PrepareViewStep::checkEnoughRam( qint64 requiredRam )
{
    // A line in meminfo looks like this, with {print $2} we grab the second column.
    // MemTotal:        8133432 kB

    QProcess p;
    p.start( "awk", { "/MemTotal/ {print $2}", "/proc/meminfo" } );
    p.waitForFinished();
    QString memoryLine = p.readAllStandardOutput().simplified();
    qint64 availableRam = memoryLine.toLongLong() * 1024;

    return availableRam >= requiredRam;
}


bool
PrepareViewStep::checkHasPower()
{
    return false;
}


bool
PrepareViewStep::checkHasInternet()
{
    return false;
}

