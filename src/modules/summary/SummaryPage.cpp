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

#include "SummaryPage.h"

#include "SummaryViewStep.h"

#include "ExecutionViewStep.h"
#include "utils/Retranslator.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "ViewManager.h"

#include <QBoxLayout>
#include <QLabel>
#include <QScrollArea>

static const int SECTION_SPACING = 12;

SummaryPage::SummaryPage( const SummaryViewStep* thisViewStep, QWidget* parent )
    : QWidget()
    , m_thisViewStep( thisViewStep )
    , m_contentWidget( nullptr )
    , m_scrollArea( new QScrollArea( this ) )
{
    Q_UNUSED( parent );
    Q_ASSERT( m_thisViewStep );
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


// Adds a widget for those ViewSteps that want a summary;
// see SummaryPage documentation and also ViewStep docs.
void
SummaryPage::onActivate()
{
    createContentWidget();

    bool first = true;
    const Calamares::ViewStepList steps =
        stepsForSummary( Calamares::ViewManager::instance()->viewSteps() );

    for ( Calamares::ViewStep* step : steps )
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

    m_scrollArea->setWidget( m_contentWidget );

    auto summarySize = m_contentWidget->sizeHint();
    if ( summarySize.height() > m_scrollArea->size().height() )
    {
        auto enlarge = 2 + summarySize.height() - m_scrollArea->size().height();
        auto widgetSize = this->size();
        widgetSize.setHeight( widgetSize.height() + enlarge );

        cDebug() << "Summary widget is larger than viewport, enlarge by" << enlarge << "to" << widgetSize;

        emit m_thisViewStep->enlarge( QSize( 0, enlarge ) );  // Only expand height
    }
}

Calamares::ViewStepList
SummaryPage::stepsForSummary( const Calamares::ViewStepList& allSteps ) const
{
    Calamares::ViewStepList steps;
    for ( Calamares::ViewStep* step : allSteps )
    {
        // We start from the beginning of the complete steps list. If we encounter any
        // ExecutionViewStep, it means there was an execution phase in the past, and any
        // jobs from before that phase were already executed, so we can safely clear the
        // list of steps to summarize and start collecting from scratch.
        if ( qobject_cast< Calamares::ExecutionViewStep* >( step ) )
        {
            steps.clear();
            continue;
        }

        // If we reach the parent step of this page, we're done collecting the list of
        // steps to summarize.
        if ( m_thisViewStep == step )
            break;

        steps.append( step );
    }

    return steps;
}


void
SummaryPage::createContentWidget()
{
    delete m_contentWidget;
    m_contentWidget = new QWidget;
    m_layout = new QVBoxLayout( m_contentWidget );
    CalamaresUtils::unmarginLayout( m_layout );
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
