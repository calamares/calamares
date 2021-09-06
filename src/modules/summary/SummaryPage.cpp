/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 2019, Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "SummaryPage.h"

#include "SummaryViewStep.h"

#include "Branding.h"
#include "Settings.h"
#include "ViewManager.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/QtCompat.h"
#include "utils/Retranslator.h"
#include "viewpages/ExecutionViewStep.h"

#include <QBoxLayout>
#include <QLabel>
#include <QScrollArea>

static const int SECTION_SPACING = 12;

SummaryPage::SummaryPage( Config* config, const SummaryViewStep* thisViewStep, QWidget* parent )
    : QWidget()
    , m_thisViewStep( thisViewStep )
    , m_contentWidget( nullptr )
    , m_scrollArea( new QScrollArea( this ) )
{
    Q_UNUSED( parent )


    this->setObjectName( "summaryStep" );

    Q_ASSERT( m_thisViewStep );
    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->setContentsMargins( 0, 0, 0, 0 );

    QLabel* headerLabel = new QLabel( this );
    headerLabel->setObjectName( "summaryTitle" );
    headerLabel->setText( config->message() );
    connect( config, &Config::messageChanged, headerLabel, &QLabel::setText );
    layout->addWidget( headerLabel );
    layout->addWidget( m_scrollArea );
    m_scrollArea->setWidgetResizable( true );
    m_scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    // If Calamares will grow, then only show scrollbar when it's needed
    // (e.g. when the screen is full).
    m_scrollArea->setVerticalScrollBarPolicy(
        Calamares::Branding::instance()->windowExpands() ? Qt::ScrollBarAsNeeded : Qt::ScrollBarAlwaysOn );
    m_scrollArea->setFrameStyle( QFrame::NoFrame );
    m_scrollArea->setContentsMargins( 0, 0, 0, 0 );
}


static QLabel*
createTitleLabel( const QString& text, const QFont& titleFont )
{
    QLabel* label = new QLabel( text );
    label->setObjectName( "summaryItemTitle" );
    label->setFont( titleFont );
    label->setContentsMargins( 0, 0, 0, 0 );

    return label;
}

static QLabel*
createBodyLabel( const QString& text, const QPalette& bodyPalette )
{
    QLabel* label = new QLabel;
    label->setObjectName( "summaryItemBody" );
    label->setMargin( CalamaresUtils::defaultFontHeight() / 2 );
    label->setAutoFillBackground( true );
    label->setPalette( bodyPalette );
    label->setText( text );
    return label;
}

// Adds a widget for those ViewSteps that want a summary;
// see SummaryPage documentation and also ViewStep docs.
void
SummaryPage::onActivate()
{
    delete m_contentWidget;  // It might have been created previously
    m_contentWidget = new QWidget;
    m_layout = new QVBoxLayout( m_contentWidget );
    CalamaresUtils::unmarginLayout( m_layout );

    QFont titleFont = font();
    titleFont.setWeight( QFont::Light );
    titleFont.setPointSize( CalamaresUtils::defaultFontSize() * 2 );

    QPalette bodyPalette( palette() );
    bodyPalette.setColor( WindowBackground, palette().window().color().lighter( 108 ) );

    bool first = true;
    const Calamares::ViewStepList steps = stepsForSummary( Calamares::ViewManager::instance()->viewSteps() );

    for ( Calamares::ViewStep* step : steps )
    {
        QString text = step->prettyStatus();
        QWidget* widget = step->createSummaryWidget();

        if ( text.isEmpty() && !widget )
        {
            continue;
        }

        if ( first )
        {
            first = false;
        }
        else
        {
            m_layout->addSpacing( SECTION_SPACING );
        }

        m_layout->addWidget( createTitleLabel( step->prettyName(), titleFont ) );
        QHBoxLayout* itemBodyLayout = new QHBoxLayout;
        m_layout->addSpacing( CalamaresUtils::defaultFontHeight() / 2 );
        m_layout->addLayout( itemBodyLayout );
        itemBodyLayout->addSpacing( CalamaresUtils::defaultFontHeight() * 2 );
        QVBoxLayout* itemBodyCoreLayout = new QVBoxLayout;
        itemBodyLayout->addLayout( itemBodyCoreLayout );
        CalamaresUtils::unmarginLayout( itemBodyLayout );
        if ( !text.isEmpty() )
        {
            itemBodyCoreLayout->addWidget( createBodyLabel( text, bodyPalette ) );
        }
        if ( widget )
        {
            itemBodyCoreLayout->addWidget( widget );
        }
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

        emit m_thisViewStep->ensureSize( widgetSize );  // Only expand height
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
        {
            break;
        }

        steps.append( step );
    }

    return steps;
}

void
SummaryPage::onLeave()
{
    delete m_contentWidget;
    m_contentWidget = nullptr;
}
