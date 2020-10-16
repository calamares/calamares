/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "PrettyRadioButton.h"

#include "utils/CalamaresUtilsGui.h"
#include "widgets/ClickableLabel.h"

#include <QButtonGroup>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>

namespace Calamares
{

PrettyRadioButton::PrettyRadioButton( QWidget* parent )
    : QWidget( parent )
    , m_label( new ClickableLabel )
    , m_radio( new QRadioButton )
    , m_mainLayout( new QGridLayout )
    , m_optionsLayout( nullptr )
{
    setLayout( m_mainLayout );

    m_label->setBuddy( m_radio );

    m_label->setWordWrap( true );
    m_label->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

    m_mainLayout->addWidget( m_radio, 0, 0 );
    m_mainLayout->addWidget( m_label, 0, 1 );
    m_mainLayout->setContentsMargins( 0, 0, 0, 0 );

    connect( m_label, &ClickableLabel::clicked, m_radio, &QRadioButton::click );
    connect( m_radio, &QRadioButton::toggled, this, &PrettyRadioButton::toggleOptions );
}


void
PrettyRadioButton::setText( const QString& text )
{
    m_label->setText( text );
}


void
PrettyRadioButton::setIconSize( const QSize& size )
{
    m_radio->setIconSize( size );
}


void
PrettyRadioButton::setIcon( const QIcon& icon )
{
    m_radio->setIcon( icon );
}


QSize
PrettyRadioButton::iconSize() const
{
    return m_radio->iconSize();
}


void
PrettyRadioButton::setChecked( bool checked )
{
    m_radio->setChecked( checked );
}


bool
PrettyRadioButton::isChecked() const
{
    return m_radio->isChecked();
}

void
PrettyRadioButton::addToGroup( QButtonGroup* group, int id )
{
    group->addButton( m_radio, id );
}


void
PrettyRadioButton::addOptionsComboBox( QComboBox* box )
{
    if ( !box )
    {
        return;
    }

    if ( !m_optionsLayout )
    {
        QWidget* w = new QWidget;
        m_optionsLayout = new QHBoxLayout;
        m_optionsLayout->setAlignment( Qt::AlignmentFlag::AlignLeft );
        m_optionsLayout->addStretch( 1 );

        w->setLayout( m_optionsLayout );
        m_mainLayout->addWidget( w, 1, 1 );

        toggleOptions( m_radio->isChecked() );
    }

    m_optionsLayout->insertWidget( m_optionsLayout->count() - 1, box );
}

void
PrettyRadioButton::toggleOptions( bool toggle )
{
    if ( m_optionsLayout )
    {
        m_optionsLayout->parentWidget()->setVisible( toggle );
    }
}

}  // namespace Calamares
