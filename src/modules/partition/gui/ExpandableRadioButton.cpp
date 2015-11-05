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


#include "ExpandableRadioButton.h"

#include <utils/CalamaresUtilsGui.h>
#include <widgets/ClickableLabel.h>

#include <QBoxLayout>


ExpandableRadioButton::ExpandableRadioButton( QWidget* parent )
    : PrettyRadioButton( parent )
    , m_expandableWidget( nullptr )
{
    QBoxLayout* mainLayout = qobject_cast< QBoxLayout* >( layout() );
    mainLayout->setDirection( QBoxLayout::TopToBottom );
    mainLayout->setContentsMargins( 0, 0, 0, 0 );
    QBoxLayout* prettyRadioButtonLayout = new QHBoxLayout;
    prettyRadioButtonLayout->addWidget( m_radio );
    prettyRadioButtonLayout->addWidget( m_label );
    mainLayout->addLayout( prettyRadioButtonLayout );
}


QSize
ExpandableRadioButton::sizeHint() const
{
    return PrettyRadioButton::sizeHint();
}


void
ExpandableRadioButton::setExpandableWidget( QWidget* widget )
{
    if ( m_expandableWidget )
    {
        layout()->removeWidget( m_expandableWidget );
        m_expandableWidget->deleteLater();
    }

    m_expandableWidget = widget;
    m_expandableWidget->setVisible( m_radio->isChecked() );
    layout()->addWidget( m_expandableWidget );
    updateGeometry();

    connect( m_radio, &QRadioButton::toggled,
             m_expandableWidget, &QWidget::setVisible );
}


QWidget*
ExpandableRadioButton::expandableWidget() const
{
    return m_expandableWidget;
}

