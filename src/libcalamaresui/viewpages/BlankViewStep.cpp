/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
