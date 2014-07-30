/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include <PartitionViewStep.h>

#include <DeviceModel.h>
#include <PartitionCoreModule.h>
#include <PartitionModel.h>
#include <PartitionPage.h>
#include <PartitionPreview.h>

// Qt
#include <QFormLayout>
#include <QLabel>

PartitionViewStep::PartitionViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_core( new PartitionCoreModule( this ) )
    , m_widget( new PartitionPage( m_core ) )
{
    connect( m_core, SIGNAL( hasRootMountPointChanged( bool ) ),
             SIGNAL( nextStatusChanged( bool ) ) );
}


QString
PartitionViewStep::prettyName() const
{
    return tr( "Partitions" );
}


QWidget*
PartitionViewStep::widget()
{
    return m_widget;
}


QWidget*
PartitionViewStep::createSummaryWidget() const
{
    QWidget* widget = new QWidget;
    QFormLayout* layout = new QFormLayout( widget );
    layout->setMargin( 0 );

    QList< PartitionCoreModule::SummaryInfo > list = m_core->createSummaryInfo();
    for ( const auto& info : list )
    {
        PartitionPreview* preview;

        layout->addRow( new QLabel( info.deviceName ) );

        preview = new PartitionPreview;
        preview->setModel( info.partitionModelBefore );
        info.partitionModelBefore->setParent( widget );
        layout->addRow( tr( "Before:" ), preview );

        preview = new PartitionPreview;
        preview->setModel( info.partitionModelAfter );
        info.partitionModelAfter->setParent( widget );
        layout->addRow( tr( "After:" ), preview );
    }
    return widget;
}

void
PartitionViewStep::next()
{
    emit done();
}


void
PartitionViewStep::back()
{}


bool
PartitionViewStep::isNextEnabled() const
{
    return m_core->hasRootMountPoint();
}


bool
PartitionViewStep::isAtBeginning() const
{
    return true;
}


bool
PartitionViewStep::isAtEnd() const
{
    return true;
}


QList< Calamares::job_ptr >
PartitionViewStep::jobs() const
{
    return m_core->jobs();
}
