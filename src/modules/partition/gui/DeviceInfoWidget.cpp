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
    mainLayout->addWidget( m_ptIcon );
    mainLayout->addWidget( m_ptLabel );

    bool isEfi = false;
    if ( QDir( "/sys/firmware/efi/efivars" ).exists() )
        isEfi = true;

    if ( isEfi )
        m_bootLabel->setText( "EFI " );
    else
        m_bootLabel->setText( "BIOS" );

    QSize iconSize = QSize( CalamaresUtils::defaultFontHeight(),
                            CalamaresUtils::defaultFontHeight() );

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
    m_ptLabel->setMinimumWidth( fm.boundingRect( "MSDOS" ).width() +2 );
    m_bootLabel->setMinimumWidth( fm.boundingRect( "BIOS" ).width() +2 );
    m_ptLabel->setAlignment( Qt::AlignCenter );
    m_bootLabel->setAlignment( Qt::AlignCenter );

    QPalette palette;
    palette.setBrush( QPalette::Foreground, QColor( "#4D4D4D" ) ); //dark grey

    m_ptLabel->setPalette( palette );
    m_bootLabel->setPalette( palette );

    m_bootIcon->setToolTip( tr( "The <strong>boot environment</strong> of this system.<br><br>"
                                "Older x86 systems only support <strong>BIOS</strong>.<br>"
                                "Modern systems usually use <strong>EFI</strong>, but "
                                "may also show up as BIOS if the boot "
                                "environment runs in compatibility mode.<br>"
                                "Relevant entries in the system setup utility "
                                "include: CSM, compatibility support module, "
                                "Legacy boot, BIOS boot, etc." ) );
    m_ptIcon->setToolTip( tr( "The type of <strong>partition table</strong> currently "
                              "present on the selected storage device.<br><br>"
                              "Common values on x86-compatible systems include "
                              "<strong>GPT</strong> and <strong>MSDOS</strong>.<br>"
                              "Some systems may use other, less common partition table "
                              "types, like BSD or Sun."
                              "The only way to change the partition table type is to "
                              "erase and recreate the partition table from scratch, "
                              "which destroys all data on the storage device.<br>"
                              "This installer will keep the current partition table "
                              "unless you explicitly choose otherwise.<br>"
                              "If unsure, on modern systems GPT is preferred." ) );
}


void
DeviceInfoWidget::setPartitionTableType( PartitionTable::TableType type )
{
    QString typeString = PartitionTable::tableTypeToName( type ).toUpper();
    // fix up if the name shouldn't be uppercase:
    switch ( type )
    {
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

    m_ptLabel->setText( typeString );
}

