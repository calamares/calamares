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

/** @brief A "details" dialog for the results-list
 *
 * This displays the same RequirementsList as ResultsListWidget,
 * but the *details* part rather than the show description.
 *
 * This is an internal-to-the-widget class.
 */
class ResultsListDialog : public QDialog
{
    Q_OBJECT
public:
    /** @brief Create a dialog for the given @p checkEntries list of requirements.
     *
     * The list must continue to exist for the lifetime of the dialog,
     * or UB happens.
     */
    ResultsListDialog( const Calamares::RequirementsModel& model, QWidget* parent );
    ~ResultsListDialog() override;

private:
    QLabel* m_title;
    const Calamares::RequirementsModel& m_model;

    void retranslate();
};

ResultsListDialog::ResultsListDialog( const Calamares::RequirementsModel& model, QWidget* parent )
    : QDialog( parent )
    , m_model( model )
{
    auto* mainLayout = new QVBoxLayout;
    auto* entriesLayout = new QVBoxLayout;

    m_title = new QLabel( this );
    m_title->setObjectName( "resultDialogTitle" );

    QDialogButtonBox* buttonBox = new QDialogButtonBox( QDialogButtonBox::Close, Qt::Horizontal, this );
    buttonBox->setObjectName( "resultDialogButtons" );

    mainLayout->addWidget( m_title );
    mainLayout->addLayout( entriesLayout );
    mainLayout->addWidget( buttonBox );

    setLayout( mainLayout );

    connect( buttonBox, &QDialogButtonBox::clicked, this, &QDialog::close );

    CALAMARES_RETRANSLATE_SLOT( &ResultsListDialog::retranslate );
}

ResultsListDialog::~ResultsListDialog() {}

void
ResultsListDialog::retranslate()
{
    m_title->setText( tr( "For best results, please ensure that this computer:" ) );
    setWindowTitle( tr( "System requirements" ) );
}


ResultsListWidget::ResultsListWidget( Config* config, QWidget* parent )
    : QWidget( parent )
    , m_config( config )
{
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    auto mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    int paddingSize = qBound( 32, CalamaresUtils::defaultFontHeight() * 4, 128 );

    QHBoxLayout* explanationLayout = new QHBoxLayout;
    m_explanation = new QLabel( m_config->warningMessage() );
    m_explanation->setWordWrap( true );
    m_explanation->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    m_explanation->setOpenExternalLinks( false );
    m_explanation->setObjectName( "resultsExplanation" );
    explanationLayout->addWidget( m_explanation );
    m_countdown = new CountdownWaitingWidget;
    explanationLayout->addWidget( m_countdown );
    m_countdown->start();

    mainLayout->addLayout( explanationLayout );
    mainLayout->addSpacing( CalamaresUtils::defaultFontHeight() / 2 );

    auto* listview = new QListView( this );
    listview->setSelectionMode( QAbstractItemView::NoSelection );
    listview->setDragDropMode( QAbstractItemView::NoDragDrop );
    listview->setAcceptDrops( false );
    listview->setItemDelegate( new ResultDelegate( this ) );
    listview->setModel( config->unsatisfiedRequirements() );
    m_centralWidget = listview;
    m_centralLayout = mainLayout;

    mainLayout->addWidget( listview );
    mainLayout->addStretch();

    connect( config,
             &Config::warningMessageChanged,
             [ = ]( QString s )
             {
                 if ( isModelFilled() )
                 {
                     m_explanation->setText( s );
                 }
             } );
    connect( m_explanation, &QLabel::linkActivated, this, &ResultsListWidget::linkClicked );
}


void
ResultsListWidget::linkClicked( const QString& link )
{
    if ( link == "#details" )
    {
        auto* dialog = new ResultsListDialog( *( m_config->requirementsModel() ), this );
        dialog->exec();
        dialog->deleteLater();
    }
}

void
ResultsListWidget::requirementsChanged()
{
    if ( !isModelFilled() )
    {
        return;
    }

    // Check that all are satisfied (gives warnings if not) and
    // all *mandatory* entries are satisfied (gives errors if not).

    const bool requirementsSatisfied = m_config->requirementsModel()->satisfiedRequirements();
    auto isUnSatisfied = []( const Calamares::RequirementsModel& m, QModelIndex i )
    { return !m.data( i, Calamares::RequirementsModel::Satisfied ).toBool(); };

    if ( requirementsSatisfied )
    {
        m_countdown->stop();
        m_countdown->hide();

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

bool
ResultsListWidget::isModelFilled()
{
    if ( m_config->requirementsModel()->count() < m_requirementsSeen )
    {
        return false;
    }
    m_requirementsSeen = m_config->requirementsModel()->count();
    return true;
}


#include "utils/moc-warnings.h"

#include "ResultsListWidget.moc"
