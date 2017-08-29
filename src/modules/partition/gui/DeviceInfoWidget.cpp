/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
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

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include <QDir>
#include <QLabel>
#include <QHBoxLayout>

DeviceInfoWidget::DeviceInfoWidget( QWidget* parent )
    : QWidget( parent )
    , m_ptIcon( new QLabel )
    , m_ptLabel( new QLabel )
    , m_tableType( PartitionTable::unknownTableType )
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    setLayout( mainLayout );

    CalamaresUtils::unmarginLayout( mainLayout );

    mainLayout->addWidget( m_ptIcon );
    mainLayout->addWidget( m_ptLabel );

    QSize iconSize = CalamaresUtils::defaultIconSize();

    m_ptIcon->setMargin( 0 );
    m_ptIcon->setFixedSize( iconSize );
    m_ptIcon->setPixmap(
        CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionTable,
                                       CalamaresUtils::Original,
                                       iconSize ) );

    QFontMetrics fm = QFontMetrics( QFont() );
    m_ptLabel->setMinimumWidth( fm.boundingRect( "Amiga" ).width() + CalamaresUtils::defaultFontHeight() / 2 );
    m_ptLabel->setAlignment( Qt::AlignCenter );

    QPalette palette;
    palette.setBrush( QPalette::Foreground, QColor( "#4D4D4D" ) ); //dark grey

    m_ptIcon->setAutoFillBackground( true );
    m_ptLabel->setAutoFillBackground( true );
    m_ptIcon->setPalette( palette );
    m_ptLabel->setPalette( palette );

    CALAMARES_RETRANSLATE( retranslateUi(); )
}


void
DeviceInfoWidget::setPartitionTableType( PartitionTable::TableType type )
{
    m_tableType = type;
    retranslateUi();
}

void
DeviceInfoWidget::retranslateUi()
{
    QString typeString = PartitionTable::tableTypeToName( m_tableType ).toUpper();

    // fix up if the name shouldn't be uppercase:
    switch ( m_tableType )
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


    QString toolTipString = tr( "This device has a <strong>%1</strong> partition "
                                "table." )
                            .arg( typeString );

    switch ( m_tableType )
    {
    case PartitionTable::loop:
        toolTipString = tr( "This is a <strong>loop</strong> "
                            "device.<br><br>"
                            "It is a pseudo-device with no partition table "
                            "that makes a file accessible as a block device. "
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
                             "is an obsolete MS-DOS era standard.<br>"
                             "Only 4 <em>primary</em> partitions may be created, and of "
                             "those 4, one can be an <em>extended</em> partition, which "
                             "may in turn contain many <em>logical</em> partitions." );
    }

    m_ptLabel->setText( typeString );
    m_ptLabel->setToolTip( toolTipString );

    m_ptIcon->setToolTip( tr( "The type of <strong>partition table</strong> on the "
                            "selected storage device.<br><br>"
                            "The only way to change the partition table type is to "
                            "erase and recreate the partition table from scratch, "
                            "which destroys all data on the storage device.<br>"
                            "This installer will keep the current partition table "
                            "unless you explicitly choose otherwise.<br>"
                            "If unsure, on modern systems GPT is preferred." ) );
}
