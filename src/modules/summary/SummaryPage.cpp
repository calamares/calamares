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

#include "SummaryPage.h"

#include "ViewManager.h"
#include "viewpages/ViewStep.h"
#include "utils/Retranslator.h"
#include "utils/CalamaresUtilsGui.h"

#include <QBoxLayout>
#include <QLabel>
#include <QScrollArea>

static const int SECTION_SPACING = 12;

SummaryPage::SummaryPage( QWidget* parent )
    : QWidget()
    , m_scrollArea( new QScrollArea( this ) )
    , m_contentWidget( nullptr )
{
    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->setContentsMargins( 0, 0, 0, 0 );

    QLabel* headerLabel = new QLabel( this );
    CALAMARES_RETRANSLATE(
        headerLabel->setText( tr( "This is an overview of what will happen once you start "
                                  "the install procedure." ) );
    )
    layout->addWidget( headerLabel );
    layout->addWidget( m_scrollArea );
    m_scrollArea->setWidgetResizable( true );
    m_scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    m_scrollArea->setFrameStyle( QFrame::NoFrame );
    m_scrollArea->setContentsMargins( 0, 0, 0, 0 );
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
        QHBoxLayout* itemBodyLayout = new QHBoxLayout;
        m_layout->addSpacing( CalamaresUtils::defaultFontHeight() / 2 );
        m_layout->addLayout( itemBodyLayout );
        itemBodyLayout->addSpacing( CalamaresUtils::defaultFontHeight() * 2 );
        QVBoxLayout* itemBodyCoreLayout = new QVBoxLayout;
        itemBodyLayout->addLayout( itemBodyCoreLayout );
        CalamaresUtils::unmarginLayout( itemBodyLayout );
        if ( !text.isEmpty() )
            itemBodyCoreLayout->addWidget( createBodyLabel( text ) );
        if ( widget )
            itemBodyCoreLayout->addWidget( widget );
        itemBodyLayout->addSpacing( CalamaresUtils::defaultFontHeight() * 2 );
    }
    m_layout->addStretch();
}

void
SummaryPage::createContentWidget()
{
    delete m_contentWidget;
    m_contentWidget = new QWidget;
    m_layout = new QVBoxLayout( m_contentWidget );
    CalamaresUtils::unmarginLayout( m_layout );
    m_scrollArea->setWidget( m_contentWidget );
}

QLabel*
SummaryPage::createTitleLabel( const QString& text ) const
{
    QLabel* label = new QLabel( text );
    QFont fnt = font();
    fnt.setWeight( QFont::Light );
    fnt.setPointSize( CalamaresUtils::defaultFontSize() * 2 );
    label->setFont( fnt );
    label->setContentsMargins( 0, 0, 0, 0 );

    return label;
}

QLabel*
SummaryPage::createBodyLabel( const QString& text ) const
{
    QLabel* label = new QLabel;
    label->setMargin( CalamaresUtils::defaultFontHeight() / 2 );
    QPalette pal( palette() );
    pal.setColor( QPalette::Background, palette().background().color().lighter( 108 ) );
    label->setAutoFillBackground( true );
    label->setPalette( pal );
    label->setText( text );
    return label;
}
