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

SummaryPage::SummaryPage( Config* config, QWidget* parent )
    : QWidget()
    , m_contentWidget( nullptr )
    , m_scrollArea( new QScrollArea( this ) )
{
    Q_UNUSED( parent )

    this->setObjectName( "summaryStep" );

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

static QWidget*
createStepWidget( const QString& description, QWidget* innerWidget, const QPalette& palette )
{
    QWidget* w = new QWidget();
    QHBoxLayout* itemBodyLayout = new QHBoxLayout;
    w->setLayout( itemBodyLayout );

    // Indent the inner box by a bit
    itemBodyLayout->addSpacing( CalamaresUtils::defaultFontHeight() * 2 );
    QVBoxLayout* itemBodyCoreLayout = new QVBoxLayout;
    itemBodyLayout->addLayout( itemBodyCoreLayout );
    CalamaresUtils::unmarginLayout( itemBodyLayout );

    itemBodyCoreLayout->addSpacing( CalamaresUtils::defaultFontHeight() / 2 );
    if ( innerWidget )
    {
        itemBodyCoreLayout->addWidget( innerWidget );
    }
    else
    {
        itemBodyCoreLayout->addWidget( createBodyLabel( description, palette ) );
    }

    return w;
}

static void
ensureSize( QWidget* parent, QScrollArea* container, Calamares::ViewStep* viewstep )
{
    auto summarySize = container->widget()->sizeHint();
    if ( summarySize.height() > container->size().height() )
    {
        auto enlarge = 2 + summarySize.height() - container->size().height();
        auto widgetSize = parent->size();
        widgetSize.setHeight( widgetSize.height() + enlarge );

        cDebug() << "Summary widget is larger than viewport, enlarge by" << enlarge << "to" << widgetSize;

        emit viewstep->ensureSize( widgetSize );  // Only expand height
    }
}

// Adds a widget for those ViewSteps that want a summary;
// see SummaryPage documentation and also ViewStep docs.
void
SummaryPage::buildWidgets( Config* config, SummaryViewStep* viewstep )
{
    const int SECTION_SPACING = 12;

    delete m_contentWidget;  // It might have been created previously
    m_contentWidget = new QWidget;
    m_layout = new QVBoxLayout( m_contentWidget );
    CalamaresUtils::unmarginLayout( m_layout );

    QFont titleFont = font();
    titleFont.setWeight( QFont::Light );
    titleFont.setPointSize( CalamaresUtils::defaultFontSize() * 2 );

    QPalette bodyPalette( palette() );
    bodyPalette.setColor( WindowBackground, palette().window().color().lighter( 108 ) );

    const auto* model = config->summaryModel();
    const auto rowCount = model->rowCount();

    for ( int row = 0; row < rowCount; row++ )
    {
        const auto rowIndex = model->index( row );
        QString title = model->data( rowIndex, SummaryModel::TitleRole ).toString();
        QString text = model->data( rowIndex, SummaryModel::MessageRole ).toString();
        QWidget* widget = model->data( rowIndex, SummaryModel::WidgetRole ).value< QWidget* >();

        if ( text.isEmpty() && !widget )
        {
            continue;
        }

        if ( row > 0 )
        {
            m_layout->addSpacing( SECTION_SPACING );
        }

        m_layout->addWidget( createTitleLabel( title, titleFont ) );
        m_layout->addWidget( createStepWidget( text, widget, bodyPalette ) );
    }
    m_layout->addStretch();

    m_scrollArea->setWidget( m_contentWidget );
    ensureSize( this, m_scrollArea, viewstep );
}

void
SummaryPage::cleanup()
{
    delete m_contentWidget;
    m_contentWidget = nullptr;
}
