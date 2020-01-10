/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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
#include "BlankViewStep.h"

#include "utils/CalamaresUtilsGui.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

namespace Calamares
{

BlankViewStep::BlankViewStep( const QString& title,
                              const QString& description,
                              const QString& details,
                              QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new QWidget() )
{
    QBoxLayout* layout = new QVBoxLayout();

    constexpr int const marginWidth = 10;
    constexpr int const spacingHeight = 10;

    auto* label = new QLabel( title );
    label->setAlignment( Qt::AlignHCenter );
    label->setFont( CalamaresUtils::largeFont() );
    layout->addWidget( label );

    label = new QLabel( description );
    label->setWordWrap( true );
    label->setMargin( marginWidth );
    layout->addSpacing( spacingHeight );
    layout->addWidget( label );

    if ( !details.isEmpty() )
    {
        label = new QLabel( details );
        label->setMargin( marginWidth );
        layout->addSpacing( spacingHeight );
        layout->addWidget( label );
    }

    layout->addStretch( 1 );  // Push the rest to the top

    m_widget->setLayout( layout );
}

BlankViewStep::~BlankViewStep() {}

QString
BlankViewStep::prettyName() const
{
    return tr( "Blank Page" );
}

void
BlankViewStep::back()
{
}

void
BlankViewStep::next()
{
}

bool
BlankViewStep::isBackEnabled() const
{
    return false;
}

bool
BlankViewStep::isNextEnabled() const
{
    return false;
}

bool
BlankViewStep::isAtBeginning() const
{
    return true;
}

bool
BlankViewStep::isAtEnd() const
{
    return false;
}

QWidget*
BlankViewStep::widget()
{
    return m_widget;
}

Calamares::JobList
BlankViewStep::jobs() const
{
    return JobList();
}

}  // namespace Calamares
