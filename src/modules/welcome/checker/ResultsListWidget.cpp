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

#include "ResultWidget.h"

#include "Branding.h"
#include "Settings.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "widgets/FixedAspectRatioLabel.h"

#include <QAbstractButton>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>

/** @brief Add widgets to @p layout for the list @p checkEntries
 *
 * The @p resultWidgets is filled with pointers to the widgets;
 * for each entry in @p checkEntries that satisfies @p predicate,
 * a widget is created, otherwise a nullptr is added instead.
 *
 * Adds all the widgets to the given @p layout.
 *
 * Afterwards, @p resultWidgets has a length equal to @p checkEntries.
 */
static void
createResultWidgets( QLayout* layout,
                     QList< ResultWidget* >& resultWidgets,
                     const Calamares::RequirementsModel& model,
                     std::function< bool( const Calamares::RequirementsModel&, QModelIndex ) > predicate )
{
    resultWidgets.clear();
    resultWidgets.reserve( model.count() );
    for ( auto i = 0; i < model.count(); i++ )
    {
        const auto& index = model.index( i );
        if ( !predicate( model, index ) )
        {
            resultWidgets.append( nullptr );
            continue;
        }

        const QString checkName = model.data( index, Calamares::RequirementsModel::Name ).toString();
        const bool is_satisfied = model.data( index, Calamares::RequirementsModel::Satisfied ).toBool();
        const bool is_mandatory = model.data( index, Calamares::RequirementsModel::Mandatory ).toBool();
        ResultWidget* ciw = new ResultWidget( is_satisfied, is_mandatory );
        ciw->setObjectName( checkName );

        layout->addWidget( ciw );
        ciw->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

        ciw->setAutoFillBackground( true );
        QPalette pal( ciw->palette() );
        QColor bgColor = pal.window().color();
        int bgHue = ( is_satisfied ) ? bgColor.hue() : ( is_mandatory ) ? 0 : 60;
        bgColor.setHsv( bgHue, 64, bgColor.value() );
        pal.setColor( QPalette::Window, bgColor );
        ciw->setPalette( pal );

        resultWidgets.append( ciw );
    }
}

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
    QList< ResultWidget* > m_resultWidgets;  ///< One widget for each entry with details available
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

    createResultWidgets(
        entriesLayout, m_resultWidgets, model, []( const Calamares::RequirementsModel& m, QModelIndex i ) {
            return m.data( i, Calamares::RequirementsModel::HasDetails ).toBool();
        } );

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

    for ( auto i = 0; i < m_model.count(); i++ )
    {
        if ( m_resultWidgets[ i ] )
        {
            m_resultWidgets[ i ]->setText(
                m_model.data( m_model.index( i ), Calamares::RequirementsModel::Details ).toString() );
        }
    }
}


ResultsListWidget::ResultsListWidget( Config* config, QWidget* parent )
    : QWidget( parent )
    , m_config( config )
{
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    QBoxLayout* mainLayout = new QVBoxLayout;
    QBoxLayout* entriesLayout = new QVBoxLayout;

    setLayout( mainLayout );

    int paddingSize = qBound( 32, CalamaresUtils::defaultFontHeight() * 4, 128 );

    QHBoxLayout* spacerLayout = new QHBoxLayout;
    mainLayout->addLayout( spacerLayout );
    spacerLayout->addSpacing( paddingSize );
    spacerLayout->addLayout( entriesLayout );
    spacerLayout->addSpacing( paddingSize );
    CalamaresUtils::unmarginLayout( spacerLayout );

    auto* explanation = new QLabel( m_config->warningMessage() );
    explanation->setWordWrap( true );
    explanation->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    explanation->setOpenExternalLinks( false );
    explanation->setObjectName( "resultsExplanation" );
    entriesLayout->addWidget( explanation );

    connect( config, &Config::warningMessageChanged, explanation, &QLabel::setText );
    connect( explanation, &QLabel::linkActivated, this, &ResultsListWidget::linkClicked );

    // Check that all are satisfied (gives warnings if not) and
    // all *mandatory* entries are satisfied (gives errors if not).

    const bool requirementsSatisfied = config->requirementsModel()->satisfiedRequirements();
    auto isUnSatisfied = []( const Calamares::RequirementsModel& m, QModelIndex i ) {
        return !m.data( i, Calamares::RequirementsModel::Satisfied ).toBool();
    };

    createResultWidgets( entriesLayout, m_resultWidgets, *( config->requirementsModel() ), isUnSatisfied );

    if ( !requirementsSatisfied )
    {
        entriesLayout->insertSpacing( 1, CalamaresUtils::defaultFontHeight() / 2 );
        mainLayout->addStretch();
    }
    else
    {
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
                mainLayout->addWidget( imageLabel );
            }
        }
        explanation->setAlignment( Qt::AlignCenter );
    }

    CALAMARES_RETRANSLATE_SLOT( &ResultsListWidget::retranslate );
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
ResultsListWidget::retranslate()
{
    const auto& model = *( m_config->requirementsModel() );
    for ( auto i = 0; i < model.count(); i++ )
    {
        if ( m_resultWidgets[ i ] )
        {
            m_resultWidgets[ i ]->setText(
                model.data( model.index( i ), Calamares::RequirementsModel::NegatedText ).toString() );
        }
    }
}

#include "utils/moc-warnings.h"

#include "ResultsListWidget.moc"
