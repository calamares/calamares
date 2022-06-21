/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ResultsListWidget.h"

#include "ResultDelegate.h"

#include "Branding.h"
#include "Settings.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "widgets/FixedAspectRatioLabel.h"
#include "widgets/WaitingWidget.h"

#include <QAbstractButton>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QListView>
#include <QVBoxLayout>

ResultsListWidget::ResultsListWidget( Config* config, QWidget* parent )
    : QWidget( parent )
    , m_config( config )
{
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    auto mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    QHBoxLayout* explanationLayout = new QHBoxLayout;
    m_explanation = new QLabel( m_config->warningMessage() );
    m_explanation->setWordWrap( true );
    m_explanation->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    m_explanation->setOpenExternalLinks( false );
    m_explanation->setObjectName( "resultsExplanation" );
    explanationLayout->addWidget( m_explanation );
    m_countdown = new CountdownWaitingWidget;
    m_countdown->setToolTip( tr( "Checking requirements again in a few seconds ..." ) );
    m_countdown->start();
    explanationLayout->addWidget( m_countdown );

    mainLayout->addLayout( explanationLayout );
    mainLayout->addSpacing( CalamaresUtils::defaultFontHeight() / 2 );

    auto* listview = new QListView( this );
    listview->setSelectionMode( QAbstractItemView::NoSelection );
    listview->setDragDropMode( QAbstractItemView::NoDragDrop );
    listview->setAcceptDrops( false );
    listview->setItemDelegate( new ResultDelegate( this, Calamares::RequirementsModel::NegatedText ) );
    listview->setModel( config->unsatisfiedRequirements() );
    m_centralWidget = listview;
    m_centralLayout = mainLayout;

    mainLayout->addWidget( listview );
    mainLayout->addStretch();

    connect( config, &Config::warningMessageChanged, m_explanation, &QLabel::setText );
}

void
ResultsListWidget::requirementsComplete()
{
    // Check that the satisfaction of the requirements:
    // - if everything is satisfied, show the welcome image
    // - otherwise, if all the mandatory ones are satisfied,
    //   we won't be re-checking (see ModuleManager::checkRequirements)
    //   so hide the countdown,
    // - otherwise we have unsatisfied mandatory requirements,
    //   so keep the countdown and the list of problems.
    const bool requirementsSatisfied = m_config->requirementsModel()->satisfiedRequirements();
    const bool mandatoryRequirementsSatisfied = m_config->requirementsModel()->satisfiedMandatory();

    if ( mandatoryRequirementsSatisfied )
    {
        m_countdown->stop();
        m_countdown->hide();
    }
    if ( requirementsSatisfied )
    {
        delete m_centralWidget;
        m_centralWidget = nullptr;

        if ( !Calamares::Branding::instance()->imagePath( Calamares::Branding::ProductWelcome ).isEmpty() )
        {
            QPixmap theImage
                = QPixmap( Calamares::Branding::instance()->imagePath( Calamares::Branding::ProductWelcome ) );
            if ( !theImage.isNull() )
            {
                QLabel* imageLabel;
                if ( Calamares::Branding::instance()->welcomeExpandingLogo() )
                {
                    FixedAspectRatioLabel* p = new FixedAspectRatioLabel;
                    p->setPixmap( theImage );
                    imageLabel = p;
                }
                else
                {
                    imageLabel = new QLabel;
                    imageLabel->setPixmap( theImage );
                }

                imageLabel->setContentsMargins( 4, CalamaresUtils::defaultFontHeight() * 3 / 4, 4, 4 );
                imageLabel->setAlignment( Qt::AlignCenter );
                imageLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
                imageLabel->setObjectName( "welcomeLogo" );
                // This specifically isn't assigned to m_centralWidget
                m_centralLayout->addWidget( imageLabel );
            }
        }
        m_explanation->setAlignment( Qt::AlignCenter );
    }
}
