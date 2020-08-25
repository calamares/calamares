/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ResultWidget.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"

#include <QBoxLayout>

static inline void
setCondition( QLabel* label, CalamaresUtils::ImageType t )
{
    label->setPixmap(
        CalamaresUtils::defaultPixmap( t, CalamaresUtils::Original, QSize( label->height(), label->height() ) ) );
}

ResultWidget::ResultWidget( bool satisfied, bool required, QWidget* parent )
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

    if ( satisfied )
    {
        setCondition( m_iconLabel, CalamaresUtils::StatusOk );
    }
    else if ( required )
    {
        setCondition( m_iconLabel, CalamaresUtils::StatusError );
    }
    else
    {
        setCondition( m_iconLabel, CalamaresUtils::StatusWarning );
    }
}


void
ResultWidget::setText( const QString& text )
{
    m_textLabel->setText( text );
}
