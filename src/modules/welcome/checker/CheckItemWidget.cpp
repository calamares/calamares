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

#include "CheckItemWidget.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"

#include <QBoxLayout>

CheckItemWidget::CheckItemWidget( bool checked,
                                  QWidget* parent )
    : QWidget( parent )
{
    QBoxLayout* mainLayout = new QHBoxLayout;
    setLayout( mainLayout );

    m_iconLabel = new QLabel( this );
    mainLayout->addWidget( m_iconLabel );
    m_iconLabel->setFixedSize( CalamaresUtils::defaultIconSize() );
    m_textLabel = new QLabel( this );
    mainLayout->addWidget( m_textLabel );
    m_textLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

    if ( checked )
        m_iconLabel->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
                                                               CalamaresUtils::Original,
                                                               QSize( m_iconLabel->height(),
                                                                      m_iconLabel->height() ) ) );
    else
        m_iconLabel->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                               CalamaresUtils::Original,
                                                               QSize( m_iconLabel->height(),
                                                                      m_iconLabel->height() ) ) );
}


void
CheckItemWidget::setText( const QString& text )
{
    m_textLabel->setText( text );
}
