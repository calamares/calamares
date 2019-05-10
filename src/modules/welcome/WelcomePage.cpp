/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2015,      Anke Boersma <demm@kaosx.us>
 *   Copyright 2017-2019, Adriaan de Groot <groot@kde.org>
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

#include "WelcomePage.h"

#include "ui_WelcomePage.h"
#include "checker/CheckerContainer.h"

#include "Branding.h"
#include "CalamaresVersion.h"
#include "Settings.h"
#include "ViewManager.h"

#include "locale/LabelModel.h"
#include "modulesystem/ModuleManager.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"

#include <QApplication>
#include <QBoxLayout>
#include <QComboBox>
#include <QDesktopServices>
#include <QFocusEvent>
#include <QLabel>
#include <QMessageBox>

WelcomePage::WelcomePage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::WelcomePage )
    , m_checkingWidget( new CheckerContainer( this ) )
    , m_languages( nullptr )
{
    connect( Calamares::ModuleManager::instance(), &Calamares::ModuleManager::requirementsResult, m_checkingWidget, &CheckerContainer::requirementsChecked );
    connect( Calamares::ModuleManager::instance(), &Calamares::ModuleManager::requirementsComplete, m_checkingWidget, &CheckerContainer::requirementsComplete );
    connect( Calamares::ModuleManager::instance(), &Calamares::ModuleManager::requirementsProgress, m_checkingWidget, &CheckerContainer::requirementsProgress );
    ui->setupUi( this );

    ui->verticalLayout->insertSpacing( 1, CalamaresUtils::defaultFontHeight() * 2 );
    initLanguages();

    ui->mainText->setAlignment( Qt::AlignCenter );
    ui->mainText->setWordWrap( true );
    ui->mainText->setOpenExternalLinks( true );

    cDebug() << "Welcome string" << Calamares::Branding::instance()->welcomeStyleCalamares()
        << *Calamares::Branding::VersionedName;

    CALAMARES_RETRANSLATE(
        QString message;

        if ( Calamares::Settings::instance()->isSetupMode() )
            message = Calamares::Branding::instance()->welcomeStyleCalamares()
                ? tr( "<h1>Welcome to the Calamares setup program for %1.</h1>" )
                : tr( "<h1>Welcome to %1 setup.</h1>" );
        else
            message = Calamares::Branding::instance()->welcomeStyleCalamares()
                ? tr( "<h1>Welcome to the Calamares installer for %1.</h1>" )
                : tr( "<h1>Welcome to the %1 installer.</h1>" );

        ui->mainText->setText( message.arg( *Calamares::Branding::VersionedName ) );
        ui->retranslateUi( this );
    )

    ui->aboutButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Information,
                                                             CalamaresUtils::Original,
                                                             2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                    CalamaresUtils::defaultFontHeight() ) ) );
    connect( ui->aboutButton, &QPushButton::clicked,
             this, [ this ]
    {
        QString title = Calamares::Settings::instance()->isSetupMode()
            ? tr( "About %1 setup" )
            : tr( "About %1 installer" );
        QMessageBox mb( QMessageBox::Information,
                        title.arg( CALAMARES_APPLICATION_NAME ),
                        tr(
                            "<h1>%1</h1><br/>"
                            "<strong>%2<br/>"
                            "for %3</strong><br/><br/>"
                            "Copyright 2014-2017 Teo Mrnjavac &lt;teo@kde.org&gt;<br/>"
                            "Copyright 2017-2019 Adriaan de Groot &lt;groot@kde.org&gt;<br/>"
                            "Thanks to <a href=\"https://calamares.io/team/\">the Calamares team</a> "
                            "and the <a href=\"https://www.transifex.com/calamares/calamares/\">Calamares "
                            "translators team</a>.<br/><br/>"
                            "<a href=\"https://calamares.io/\">Calamares</a> "
                            "development is sponsored by <br/>"
                            "<a href=\"http://www.blue-systems.com/\">Blue Systems</a> - "
                            "Liberating Software."
                        )
                        .arg( CALAMARES_APPLICATION_NAME )
                        .arg( CALAMARES_VERSION )
                        .arg( *Calamares::Branding::VersionedName ),
                        QMessageBox::Ok,
                        this );
        mb.setIconPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Squid,
                                                         CalamaresUtils::Original,
                                                         QSize( CalamaresUtils::defaultFontHeight() * 6,
                                                                CalamaresUtils::defaultFontHeight() * 6 ) ) );
        QGridLayout* layout = reinterpret_cast<QGridLayout *>( mb.layout() );
        if ( layout )
            layout->setColumnMinimumWidth( 2, CalamaresUtils::defaultFontHeight() * 24 );
        mb.exec();
    } );

    ui->verticalLayout->insertWidget( 3, m_checkingWidget);
}


void
WelcomePage::initLanguages()
{
    // Fill the list of translations
    ui->languageWidget->clear();
    ui->languageWidget->setInsertPolicy( QComboBox::InsertAtBottom );

    m_languages = CalamaresUtils::Locale::availableTranslations();
    ui->languageWidget->setModel( m_languages );
    ui->languageWidget->setItemDelegate( new LocaleTwoColumnDelegate( ui->languageWidget ) );

    // Find the best initial translation
    QLocale defaultLocale = QLocale( QLocale::system().name() );

    cDebug() << "Matching locale" << defaultLocale;
    int matchedLocaleIndex = m_languages->find(
        [&](const QLocale& x){ return x.language() == defaultLocale.language() && x.country() == defaultLocale.country(); } );

    if ( matchedLocaleIndex < 0 )
    {
        cDebug() << Logger::SubEntry << "Matching approximate locale" << defaultLocale.language();

        matchedLocaleIndex = m_languages->find(
            [&](const QLocale& x){ return x.language() == defaultLocale.language(); } );
    }

    if ( matchedLocaleIndex < 0 )
    {
        QLocale en_us( QLocale::English, QLocale::UnitedStates );

        cDebug() << Logger::SubEntry << "Matching English (US)";
        matchedLocaleIndex = m_languages->find( en_us );

        // Now, if it matched, because we didn't match the system locale, switch to the one found
        if ( matchedLocaleIndex >= 0 )
            QLocale::setDefault( m_languages->locale( matchedLocaleIndex ).locale() );
    }

    if ( matchedLocaleIndex >= 0 )
    {
        QString name = m_languages->locale( matchedLocaleIndex ).name();
        cDebug() << Logger::SubEntry << "Matched with index" << matchedLocaleIndex << name;

        CalamaresUtils::installTranslator( name, Calamares::Branding::instance()->translationsDirectory(), qApp );
        ui->languageWidget->setCurrentIndex( matchedLocaleIndex );
    }
    else
        cWarning() << "No available translation matched" << defaultLocale;

    connect( ui->languageWidget,
             static_cast< void ( QComboBox::* )( int ) >( &QComboBox::currentIndexChanged ),
             this,
             [&]( int newIndex )
             {
                 const auto& selectedLocale = m_languages->locale( newIndex ).locale();
                 cDebug() << "Selected locale" << selectedLocale;

                 QLocale::setDefault( selectedLocale );
                 CalamaresUtils::installTranslator( selectedLocale,
                                                    Calamares::Branding::instance()->translationsDirectory(),
                                                    qApp );
             } );
}


void
WelcomePage::setUpLinks( bool showSupportUrl,
                          bool showKnownIssuesUrl,
                          bool showReleaseNotesUrl )
{
    using namespace Calamares;
    if ( showSupportUrl && !( *Branding::SupportUrl ).isEmpty() )
    {
        CALAMARES_RETRANSLATE(
            ui->supportButton->setText( tr( "%1 support" )
                                        .arg( *Branding::ShortProductName ) );
        )
        ui->supportButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Help,
                                                                   CalamaresUtils::Original,
                                                                   2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                          CalamaresUtils::defaultFontHeight() ) ) );
        connect( ui->supportButton, &QPushButton::clicked, []
        {
            QDesktopServices::openUrl( *Branding::SupportUrl );
        } );
    }
    else
    {
        ui->supportButton->hide();
    }

    if ( showKnownIssuesUrl && !( *Branding::KnownIssuesUrl ).isEmpty() )
    {
        ui->knownIssuesButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Bugs,
                                                                       CalamaresUtils::Original,
                                                                       2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                              CalamaresUtils::defaultFontHeight() ) ) );
        connect( ui->knownIssuesButton, &QPushButton::clicked, []
        {
            QDesktopServices::openUrl( *Branding::KnownIssuesUrl );
        } );
    }
    else
    {
        ui->knownIssuesButton->hide();
    }

    if ( showReleaseNotesUrl && !( *Branding::ReleaseNotesUrl ).isEmpty() )
    {
        ui->releaseNotesButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Release,
                                                                        CalamaresUtils::Original,
                                                                        2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                               CalamaresUtils::defaultFontHeight() ) ) );
        connect( ui->releaseNotesButton, &QPushButton::clicked, []
        {
            QDesktopServices::openUrl( *Branding::ReleaseNotesUrl );
        } );
    }
    else
    {
        ui->releaseNotesButton->hide();
    }
}


void
WelcomePage::focusInEvent( QFocusEvent* e )
{
    if ( ui->languageWidget )
        ui->languageWidget->setFocus();
    e->accept();
}

bool
WelcomePage::verdict() const
{
    return m_checkingWidget->verdict();
}

void
WelcomePage::externallySelectedLanguage( int row )
{
    if ( ( row >= 0 ) && ( row < ui->languageWidget->count() ) )
        ui->languageWidget->setCurrentIndex( row );
}


void
LocaleTwoColumnDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint( painter, option, index );
    option.widget->style()->drawItemText( painter, option.rect, Qt::AlignRight | Qt::AlignVCenter, option.palette, false, index.data( CalamaresUtils::Locale::LabelModel::EnglishLabelRole ).toString() );
}
