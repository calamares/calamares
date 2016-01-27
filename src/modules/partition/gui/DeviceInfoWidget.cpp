/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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


#include "DeviceInfoWidget.h"

#include <utils/CalamaresUtilsGui.h>
#include <JobQueue.h>
#include <GlobalStorage.h>

#include <QDir>
#include <QLabel>
#include <QHBoxLayout>

DeviceInfoWidget::DeviceInfoWidget( QWidget* parent )
    : QWidget( parent )
    , m_bootIcon( new QLabel )
    , m_bootLabel( new QLabel )
    , m_ptIcon( new QLabel )
    , m_ptLabel( new QLabel )
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    setLayout( mainLayout );

    CalamaresUtils::unmarginLayout( mainLayout );

    mainLayout->addWidget( m_bootIcon );
    mainLayout->addWidget( m_bootLabel );
    mainLayout->addSpacing( CalamaresUtils::defaultFontHeight() / 4 );
    mainLayout->addWidget( m_ptIcon );
    mainLayout->addWidget( m_ptLabel );

    QSize iconSize = CalamaresUtils::defaultIconSize();

    m_bootIcon->setMargin( 0 );
    m_bootIcon->setFixedSize( iconSize );
    m_bootIcon->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::BootEnvironment,
                                                          CalamaresUtils::Original,
                                                          iconSize ) );
    m_ptIcon->setMargin( 0 );
    m_ptIcon->setFixedSize( iconSize );
    m_ptIcon->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionTable,
                                                        CalamaresUtils::Original,
                                                        iconSize ) );

    QFontMetrics fm = QFontMetrics( QFont() );
    m_ptLabel->setMinimumWidth( fm.boundingRect( "Amiga" ).width() + CalamaresUtils::defaultFontHeight() / 2 );
    m_bootLabel->setMinimumWidth( fm.boundingRect( "BIOS" ).width() + CalamaresUtils::defaultFontHeight() / 2 );
    m_ptLabel->setAlignment( Qt::AlignCenter );
    m_bootLabel->setAlignment( Qt::AlignCenter );

    QPalette palette;
    palette.setBrush( QPalette::Foreground, QColor( "#4D4D4D" ) ); //dark grey

    m_ptIcon->setAutoFillBackground( true );
    m_bootIcon->setAutoFillBackground( true );
    m_ptLabel->setAutoFillBackground( true );
    m_bootLabel->setAutoFillBackground( true );
    m_ptIcon->setPalette( palette );
    m_bootIcon->setPalette( palette );
    m_ptLabel->setPalette( palette );
    m_bootLabel->setPalette( palette );

    m_bootIcon->setToolTip( tr( "The <strong>boot environment</strong> of this system.<br><br>"
                                "Older x86 systems only support <strong>BIOS</strong>.<br>"
                                "Modern systems usually use <strong>EFI</strong>, but "
                                "may also show up as BIOS if started in compatibility "
                                "mode." ) );
    m_ptIcon->setToolTip( tr( "The type of <strong>partition table</strong> on the "
                              "selected storage device.<br><br>"
                              "The only way to change the partition table type is to "
                              "erase and recreate the partition table from scratch, "
                              "which destroys all data on the storage device.<br>"
                              "This installer will keep the current partition table "
                              "unless you explicitly choose otherwise.<br>"
                              "If unsure, on modern systems GPT is preferred." ) );

    bool isEfi = false;
    if ( QDir( "/sys/firmware/efi/efivars" ).exists() )
        isEfi = true;

    QString bootToolTip;
    if ( isEfi )
    {
        m_bootLabel->setText( "EFI " );
        bootToolTip = tr( "This system was started with an <strong>EFI</strong> "
                          "boot environment.<br><br>"
                          "To configure startup from an EFI environment, this installer "
                          "must deploy a boot loader application, like <strong>GRUB"
                          "</strong> or <strong>systemd-boot</strong> on an <strong>"
                          "EFI System Partition</strong>. This is automatic, unless "
                          "you choose manual partitioning, in which case you must "
                          "choose it or create it on your own." );
    }
    else
    {
        m_bootLabel->setText( "BIOS" );
        bootToolTip = tr( "This system was started with a <strong>BIOS</strong> "
                          "boot environment.<br><br>"
                          "To configure startup from a BIOS environment, this installer "
                          "must install a boot loader, like <strong>GRUB"
                          "</strong>, either at the beginning of a partition or "
                          "on the <strong>Master Boot Record</strong> near the "
                          "beginning of the partition table (preferred). "
                          "This is automatic, unless "
                          "you choose manual partitioning, in which case you must "
                          "set it up on your own." );

    }
    m_bootLabel->setToolTip( bootToolTip );

}


void
DeviceInfoWidget::setPartitionTableType( PartitionTable::TableType type )
{
    QString typeString = PartitionTable::tableTypeToName( type ).toUpper();

    // fix up if the name shouldn't be uppercase:
    switch ( type )
    {
    case PartitionTable::msdos:
    case PartitionTable::msdos_sectorbased:
        typeString = "MBR";
        break;
    case PartitionTable::loop:
        typeString = "loop";
        break;
    case PartitionTable::mac:
        typeString = "Mac";
        break;
    case PartitionTable::amiga:
        typeString = "Amiga";
        break;
    case PartitionTable::sun:
        typeString = "Sun";
        break;
    case PartitionTable::unknownTableType:
        typeString = " ? ";
    }


    QString toolTipString = tr( "The selected storage device has a partition table of "
                                "type <strong>%1</strong>." )
                            .arg( typeString );

    switch ( type )
    {
    case PartitionTable::loop:
        toolTipString = tr( "The selected storage device is a <strong>loop</strong> "
                            "device.<br><br>"
                            "This is not an actual partition table, it is "
                            "a pseudo-device that makes a file accessible as a block device. "
                            "This kind of setup usually only contains a single filesystem." );
        break;
    case PartitionTable::unknownTableType:
        toolTipString = tr( "This installer <strong>cannot detect a partition table</strong> on the "
                            "selected storage device.<br><br>"
                            "The device either has no partition "
                            "table, or the partition table is corrupted or of an unknown "
                            "type.<br>"
                            "This installer can create a new partition table for you, "
                            "either automatically, or through the manual partitioning "
                            "page." );
        break;
    case PartitionTable::gpt:
        toolTipString += tr( "<br><br>This is the recommended partition table type for modern "
                             "systems which start from an <strong>EFI</strong> boot "
                             "environment." );
        break;
    case PartitionTable::msdos:
    case PartitionTable::msdos_sectorbased:
        toolTipString += tr( "<br><br>This partition table type is only advisable on older "
                             "systems which start from a <strong>BIOS</strong> boot "
                             "environment. GPT is recommended in most other cases.<br><br>"
                             "<strong>Warning:</strong> the MBR partition table "
                             "is an obsolete standard.<br>"
                             "Only 4 <em>primary</em> partitions may be created, and of "
                             "those 4, one can be an <em>extended</em> partition, which "
                             "may in turn contain many <em>logical</em> partitions." );
    }

    m_ptLabel->setText( typeString );
    m_ptLabel->setToolTip( toolTipString );
}

