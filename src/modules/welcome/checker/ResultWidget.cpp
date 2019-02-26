/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

static inline void setCondition( QLabel* label, CalamaresUtils::ImageType t )
{
    label->setPixmap( CalamaresUtils::defaultPixmap( t,
                                                    CalamaresUtils::Original,
                                                    QSize( label->height(), label->height() ) ) );
}

CheckItemWidget::CheckItemWidget( bool checked,
                                  bool required,
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
        // Condition is satisfied
        setCondition( m_iconLabel, CalamaresUtils::StatusOk );
    else
        if ( required )
            setCondition( m_iconLabel, CalamaresUtils::StatusError );
        else
            setCondition( m_iconLabel, CalamaresUtils::StatusWarning );
}


void
CheckItemWidget::setText( const QString& text )
{
    m_textLabel->setText( text );
}
