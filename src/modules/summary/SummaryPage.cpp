/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#include "SummaryPage.h"

#include "ViewManager.h"
#include "viewpages/ViewStep.h"

#include <QBoxLayout>
#include <QLabel>

static const int SECTION_SPACING = 12;

SummaryPage::SummaryPage( QWidget* parent )
    : QWidget()
{
    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->setContentsMargins( 0, 0, 0, 0 );
}


void
SummaryPage::onActivate()
{
    createContentWidget();

    QString text;
    bool first = true;
    foreach ( Calamares::ViewStep* step,
              Calamares::ViewManager::instance()->prepareSteps() )
    {
        QString text = step->prettyStatus();
        QWidget* widget = step->createSummaryWidget();

        if ( text.isEmpty() && !widget )
            continue;

        if ( first )
            first = false;
        else
            m_layout->addSpacing( SECTION_SPACING );

        m_layout->addWidget( createTitleLabel( step->prettyName() ) );
        if ( !text.isEmpty() )
            m_layout->addWidget( createBodyLabel( text ) );
        if ( widget )
            m_layout->addWidget( widget );
    }
    m_layout->addStretch();
}

void
SummaryPage::createContentWidget()
{
    delete m_contentWidget;
    m_contentWidget = new QWidget;
    m_layout = new QVBoxLayout( m_contentWidget );
    layout()->addWidget( m_contentWidget );
}

QLabel*
SummaryPage::createTitleLabel( const QString& text ) const
{
    QLabel* label = new QLabel( text );
    QFont fnt = font();
    fnt.setBold( true );
    label->setFont( fnt );
    return label;
}

QLabel*
SummaryPage::createBodyLabel( const QString& text ) const
{
    return new QLabel( text );
}
