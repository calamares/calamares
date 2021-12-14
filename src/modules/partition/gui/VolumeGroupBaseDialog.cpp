/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "VolumeGroupBaseDialog.h"
#include "ui_VolumeGroupBaseDialog.h"

#include "core/SizeUtils.h"
#include "gui/ListPhysicalVolumeWidgetItem.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

VolumeGroupBaseDialog::VolumeGroupBaseDialog( QWidget* parent, const QString& vgName, PartitionVector pvList )
    : QDialog( parent )
    , ui( new Ui::VolumeGroupBaseDialog )
    , m_volumeGroupName( vgName )
    , m_totalSizeValue( 0 )
    , m_usedSizeValue( 0 )
{
    ui->setupUi( this );

    for ( const Partition* p : pvList )
    {
        ui->pvList->addItem( new ListPhysicalVolumeWidgetItem( p, false ) );
    }

    ui->vgType->addItems( { "LVM", "RAID" } );
    ui->vgType->setCurrentIndex( 0 );

    QRegularExpression re( R"(^(?!_|\.)[\w\-.+]+)" );
    ui->vgName->setValidator( new QRegularExpressionValidator( re, this ) );
    ui->vgName->setText( vgName );

    updateOkButton();
    updateTotalSize();

    connect( ui->pvList, &QListWidget::itemChanged, this, [&]( QListWidgetItem* ) {
        updateTotalSize();
        updateOkButton();
    } );

    connect( ui->peSize, qOverload< int >( &QSpinBox::valueChanged ), this, [&]( int ) {
        updateTotalSectors();
        updateOkButton();
    } );

    connect( ui->vgName, &QLineEdit::textChanged, this, [&]( const QString& s ) {
        m_volumeGroupName = s;
        updateOkButton();
    } );
}

VolumeGroupBaseDialog::~VolumeGroupBaseDialog()
{
    delete ui;
}

VolumeGroupBaseDialog::PartitionVector
VolumeGroupBaseDialog::selectedPVs() const
{
    PartitionVector items;

    for ( int i = 0; i < ui->pvList->count(); i++ )
    {
        ListPhysicalVolumeWidgetItem* item = dynamic_cast< ListPhysicalVolumeWidgetItem* >( ui->pvList->item( i ) );

        if ( item && item->checkState() == Qt::Checked )
        {
            items << item->partition();
        }
    }

    return items;
}

bool
VolumeGroupBaseDialog::isSizeValid() const
{
    return m_totalSizeValue >= m_usedSizeValue;
}

void
VolumeGroupBaseDialog::updateOkButton()
{
    okButtonWidget()->setEnabled( isSizeValid() && !selectedPVs().empty() && !ui->vgName->text().isEmpty()
                                  && ui->peSize->value() > 0 );
}

void
VolumeGroupBaseDialog::setUsedSizeValue( qint64 usedSize )
{
    m_usedSizeValue = usedSize;

    ui->usedSize->setText( formatByteSize( m_usedSizeValue ) );
}

void
VolumeGroupBaseDialog::setLVQuantity( qint32 lvQuantity )
{
    ui->lvQuantity->setText( QString::number( lvQuantity ) );
}

void
VolumeGroupBaseDialog::updateTotalSize()
{
    m_physicalExtentSize = peSizeWidget()->value();
    m_totalSizeValue = 0;

    for ( const Partition* p : selectedPVs() )
    {
        m_totalSizeValue += p->capacity()
            - p->capacity()
                % ( m_physicalExtentSize * Capacity::unitFactor( Capacity::Unit::Byte, Capacity::Unit::MiB ) );
    }

    ui->totalSize->setText( formatByteSize( m_totalSizeValue ) );

    updateTotalSectors();
}

void
VolumeGroupBaseDialog::updateTotalSectors()
{
    m_physicalExtentSize = peSizeWidget()->value();

    qint64 totalSectors = 0;
    qint64 extentSize = m_physicalExtentSize * Capacity::unitFactor( Capacity::Unit::Byte, Capacity::Unit::MiB );

    if ( extentSize > 0 )
    {
        totalSectors = m_totalSizeValue / extentSize;
    }

    ui->totalSectors->setText( QString::number( totalSectors ) );
}

QLineEdit*
VolumeGroupBaseDialog::vgNameWidget() const
{
    return ui->vgName;
}

QComboBox*
VolumeGroupBaseDialog::vgTypeWidget() const
{
    return ui->vgType;
}

QSpinBox*
VolumeGroupBaseDialog::peSizeWidget() const
{
    return ui->peSize;
}

QListWidget*
VolumeGroupBaseDialog::pvListWidget() const
{
    return ui->pvList;
}

QPushButton*
VolumeGroupBaseDialog::okButtonWidget() const
{
    return ui->buttonBox->button( QDialogButtonBox::StandardButton::Ok );
}
