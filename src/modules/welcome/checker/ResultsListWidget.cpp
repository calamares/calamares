/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, 2019, Adriaan de Groot <groot@kde.org>
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

#include "ResultsListWidget.h"

#include "ResultWidget.h"

#include "Branding.h"
#include "Settings.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "widgets/FixedAspectRatioLabel.h"

#include <QAbstractButton>
#include <QBoxLayout>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>

static void
createResultWidgets( QLayout* layout,
                     QList< ResultWidget* >& resultWidgets,
                     const Calamares::RequirementsList& checkEntries,
                     std::function< bool( const Calamares::RequirementEntry& ) > predicate )
{
    for ( const auto& entry : checkEntries )
    {
        if ( !predicate( entry ) )
        {
            continue;
        }

        ResultWidget* ciw = new ResultWidget( entry.satisfied, entry.mandatory );
        layout->addWidget( ciw );
        ciw->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

        ciw->setAutoFillBackground( true );
        QPalette pal( ciw->palette() );
        QColor bgColor = pal.window().color();
        int bgHue = ( entry.satisfied ) ? bgColor.hue() : ( entry.mandatory ) ? 0 : 60;
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
public:
    /** @brief Create a dialog for the given @p checkEntries list of requirements.
     *
     * The list must continue to exist for the lifetime of the dialog,
     * or UB happens.
     */
    ResultsListDialog( QWidget* parent, const Calamares::RequirementsList& checkEntries );
    virtual ~ResultsListDialog();

private:
    QLabel* m_title;
    QList< ResultWidget* > m_resultWidgets;  ///< One widget for each entry with details available
    const Calamares::RequirementsList& m_entries;

    void retranslate();
};

ResultsListDialog::ResultsListDialog( QWidget* parent, const Calamares::RequirementsList& checkEntries )
    : QDialog( parent )
    , m_entries( checkEntries )
{
    auto* mainLayout = new QVBoxLayout;
    auto* entriesLayout = new QVBoxLayout;

    m_title = new QLabel( this );

    createResultWidgets( entriesLayout, m_resultWidgets, checkEntries, []( const Calamares::RequirementEntry& e ) {
        return e.hasDetails();
    } );

    QDialogButtonBox* buttonBox = new QDialogButtonBox( QDialogButtonBox::Close, Qt::Horizontal, this );

    mainLayout->addWidget( m_title );
    mainLayout->addLayout( entriesLayout );
    mainLayout->addWidget( buttonBox );

    setLayout( mainLayout );

    CALAMARES_RETRANSLATE_SLOT( &ResultsListDialog::retranslate )

    connect( buttonBox, &QDialogButtonBox::clicked, this, &QDialog::close );
    retranslate();  // Do it now to fill in the texts
}

ResultsListDialog::~ResultsListDialog() {}

void
ResultsListDialog::retranslate()
{
    m_title->setText( tr( "For best results, please ensure that this computer:" ) );
    setWindowTitle( tr( "System requirements" ) );

    int i = 0;
    for ( const auto& entry : m_entries )
    {
        if ( !entry.hasDetails() )
        {
            continue;
        }
        m_resultWidgets[ i ]->setText( entry.enumerationText() );
        i++;
    }
}


ResultsListWidget::ResultsListWidget( QWidget* parent, const Calamares::RequirementsList& checkEntries )
    : QWidget( parent )
    , m_entries( checkEntries )
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

    // Check that all are satisfied (gives warnings if not) and
    // all *mandatory* entries are satisfied (gives errors if not).
    auto isUnSatisfied = []( const Calamares::RequirementEntry& e ) { return !e.satisfied; };
    auto isMandatoryAndUnSatisfied = []( const Calamares::RequirementEntry& e ) { return e.mandatory && !e.satisfied; };
    const bool requirementsSatisfied = std::none_of( checkEntries.begin(), checkEntries.end(), isUnSatisfied );
    const bool mandatorySatisfied = std::none_of( checkEntries.begin(), checkEntries.end(), isMandatoryAndUnSatisfied );

    for ( const auto& entry : checkEntries )
    {
        if ( !entry.satisfied )
        {
            ResultWidget* ciw = new ResultWidget( entry.satisfied, entry.mandatory );
            CALAMARES_RETRANSLATE( ciw->setText( entry.negatedText() ); )
            entriesLayout->addWidget( ciw );
            ciw->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
            ciw->setAutoFillBackground( true );
            QPalette pal( ciw->palette() );
            QColor bgColor = pal.window().color();
            int bgHue = ( entry.satisfied ) ? bgColor.hue() : ( entry.mandatory ) ? 0 : 60;
            bgColor.setHsv( bgHue, 64, bgColor.value() );
            pal.setColor( QPalette::Window, bgColor );
            ciw->setPalette( pal );
        }
    }

    QLabel* textLabel = new QLabel;

    textLabel->setWordWrap( true );
    entriesLayout->insertWidget( 0, textLabel );
    textLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

    if ( !requirementsSatisfied )
    {
        entriesLayout->insertSpacing( 1, CalamaresUtils::defaultFontHeight() / 2 );

        if ( !mandatorySatisfied )
        {
            CALAMARES_RETRANSLATE( QString message = Calamares::Settings::instance()->isSetupMode()
                                       ? tr( "This computer does not satisfy the minimum "
                                             "requirements for setting up %1.<br/>"
                                             "Setup cannot continue. "
                                             "<a href=\"#details\">Details...</a>" )
                                       : tr( "This computer does not satisfy the minimum "
                                             "requirements for installing %1.<br/>"
                                             "Installation cannot continue. "
                                             "<a href=\"#details\">Details...</a>" );
                                   textLabel->setText( message.arg( *Calamares::Branding::ShortVersionedName ) ); )
            textLabel->setOpenExternalLinks( false );
            connect( textLabel, &QLabel::linkActivated, this, &ResultsListWidget::linkClicked );
        }
        else
        {
            CALAMARES_RETRANSLATE( QString message = Calamares::Settings::instance()->isSetupMode()
                                       ? tr( "This computer does not satisfy some of the "
                                             "recommended requirements for setting up %1.<br/>"
                                             "Setup can continue, but some features "
                                             "might be disabled." )
                                       : tr( "This computer does not satisfy some of the "
                                             "recommended requirements for installing %1.<br/>"
                                             "Installation can continue, but some features "
                                             "might be disabled." );
                                   textLabel->setText( message.arg( *Calamares::Branding::ShortVersionedName ) ); )
        }
    }

    if ( requirementsSatisfied && mandatorySatisfied )
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
                mainLayout->addWidget( imageLabel );
                imageLabel->setAlignment( Qt::AlignCenter );
                imageLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
            }
        }
        CALAMARES_RETRANSLATE( textLabel->setText( tr( "This program will ask you some questions and "
                                                       "set up %2 on your computer." )
                                                       .arg( *Calamares::Branding::ProductName ) );
                               textLabel->setAlignment( Qt::AlignCenter ); )
    }
    else
    {
        mainLayout->addStretch();
    }
}


void
ResultsListWidget::linkClicked( const QString& link )
{
    if ( link == "#details" )
    {
        auto* dialog = new ResultsListDialog( this, m_entries );
        dialog->exec();
        dialog->deleteLater();
    }
}
