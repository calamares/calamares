/* === This file is part of Calamares - <https://github.com/calamares> ===
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


#include "BootInfoWidget.h"
#include "core/PartUtils.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"

#include <QDir>
#include <QLabel>
#include <QHBoxLayout>

BootInfoWidget::BootInfoWidget( QWidget* parent )
    : QWidget( parent )
    , m_bootIcon( new QLabel )
    , m_bootLabel( new QLabel )
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    setLayout( mainLayout );

    CalamaresUtils::unmarginLayout( mainLayout );

    mainLayout->addWidget( m_bootIcon );
    mainLayout->addWidget( m_bootLabel );

    QSize iconSize = CalamaresUtils::defaultIconSize();

    m_bootIcon->setMargin( 0 );
    m_bootIcon->setFixedSize( iconSize );
    m_bootIcon->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::BootEnvironment,
                                                          CalamaresUtils::Original,
                                                          iconSize ) );

    QFontMetrics fm = QFontMetrics( QFont() );
    m_bootLabel->setMinimumWidth( fm.boundingRect( "BIOS" ).width() + CalamaresUtils::defaultFontHeight() / 2 );
    m_bootLabel->setAlignment( Qt::AlignCenter );

    QPalette palette;
    palette.setBrush( QPalette::Foreground, QColor( "#4D4D4D" ) ); //dark grey

    m_bootIcon->setAutoFillBackground( true );
    m_bootLabel->setAutoFillBackground( true );
    m_bootIcon->setPalette( palette );
    m_bootLabel->setPalette( palette );

    CALAMARES_RETRANSLATE( retranslateUi(); )
}

void
BootInfoWidget::retranslateUi()
{
    m_bootIcon->setToolTip( tr( "The <strong>boot environment</strong> of this system.<br><br>"
                                "Older x86 systems only support <strong>BIOS</strong>.<br>"
                                "Modern systems usually use <strong>EFI</strong>, but "
                                "may also show up as BIOS if started in compatibility "
                                "mode." ) );

    QString bootToolTip;
    if ( PartUtils::isEfiSystem() )
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
