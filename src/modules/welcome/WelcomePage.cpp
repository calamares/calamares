/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2015,      Anke Boersma <demm@kaosx.us>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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
#include "CalamaresVersion.h"
#include "checker/RequirementsChecker.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"
#include "ViewManager.h"

#include <QApplication>
#include <QBoxLayout>
#include <QDesktopServices>
#include <QFocusEvent>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>

#include "Branding.h"


WelcomePage::WelcomePage( RequirementsChecker* requirementsChecker, QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::WelcomePage )
    , m_requirementsChecker( requirementsChecker )
{
    ui->setupUi( this );

    ui->verticalLayout->insertSpacing( 1, CalamaresUtils::defaultFontHeight() * 2 );
    initLanguages();

    ui->mainText->setAlignment( Qt::AlignCenter );
    ui->mainText->setWordWrap( true );
    ui->mainText->setOpenExternalLinks( true );

    cDebug() << "Welcome string" << Calamares::Branding::instance()->welcomeStyleCalamares()
        << *Calamares::Branding::VersionedName;

    CALAMARES_RETRANSLATE(
        ui->mainText->setText( (Calamares::Branding::instance()->welcomeStyleCalamares() ? tr( "<h1>Welcome to the Calamares installer for %1.</h1>" ) : tr( "<h1>Welcome to the %1 installer.</h1>" ))
                                .arg( *Calamares::Branding::VersionedName ) );
        ui->retranslateUi( this );
    )

    ui->aboutButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Information,
                                                             CalamaresUtils::Original,
                                                             2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                    CalamaresUtils::defaultFontHeight() ) ) );
    connect( ui->aboutButton, &QPushButton::clicked,
             this, [ this ]
    {
        QMessageBox mb( QMessageBox::Information,
                        tr( "About %1 installer" )
                            .arg( CALAMARES_APPLICATION_NAME ),
                        tr(
                            "<h1>%1</h1><br/>"
                            "<strong>%2<br/>"
                            "for %3</strong><br/><br/>"
                            "Copyright 2014-2017 Teo Mrnjavac &lt;teo@kde.org&gt;<br/>"
                            "Copyright 2017 Adriaan de Groot &lt;groot@kde.org&gt;<br/>"
                            "Thanks to: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Lisa Vitolo,"
                            " Philip Müller, Pier Luigi Fiorini, Rohan Garg and the <a "
                            "href=\"https://www.transifex.com/calamares/calamares/\">Calamares "
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

    ui->verticalLayout->insertWidget( 3, m_requirementsChecker->widget() );
}


void
WelcomePage::initLanguages()
{
    ui->languageWidget->setInsertPolicy( QComboBox::InsertAlphabetically );

    QLocale defaultLocale = QLocale( QLocale::system().name() );
    {
        bool isTranslationAvailable = false;

        const auto locales = QString( CALAMARES_TRANSLATION_LANGUAGES ).split( ';');
        for ( const QString& locale : locales )
        {
            QLocale thisLocale = QLocale( locale );
            QString lang = QLocale::languageToString( thisLocale.language() );
            if ( QLocale::countriesForLanguage( thisLocale.language() ).count() > 2 )
                lang.append( QString( " (%1)" )
                             .arg( QLocale::countryToString( thisLocale.country() ) ) );

            ui->languageWidget->addItem( lang, thisLocale );
            if ( thisLocale.language() == defaultLocale.language() &&
                 thisLocale.country() == defaultLocale.country() )
            {
                isTranslationAvailable = true;
                ui->languageWidget->setCurrentIndex( ui->languageWidget->count() - 1 );
                cDebug() << "Initial locale " << thisLocale.name();
                CalamaresUtils::installTranslator( thisLocale.name(),
                                                   Calamares::Branding::instance()->translationsPathPrefix(),
                                                   qApp );
            }
        }

        if ( !isTranslationAvailable )
        {
            for (int i = 0; i < ui->languageWidget->count(); i++)
            {
                QLocale thisLocale = ui->languageWidget->itemData( i, Qt::UserRole ).toLocale();
                if ( thisLocale.language() == defaultLocale.language() )
                {
                    isTranslationAvailable = true;
                    ui->languageWidget->setCurrentIndex( i );
                    cDebug() << "Initial locale " << thisLocale.name();
                    CalamaresUtils::installTranslator( thisLocale.name(),
                                                       Calamares::Branding::instance()->translationsPathPrefix(),
                                                       qApp );
                    break;
                }
            }
        }

        if ( !isTranslationAvailable )
        {
            for (int i = 0; i < ui->languageWidget->count(); i++)
            {
                QLocale thisLocale = ui->languageWidget->itemData( i, Qt::UserRole ).toLocale();
                if ( thisLocale == QLocale( QLocale::English, QLocale::UnitedStates ) )
                {
                    ui->languageWidget->setCurrentIndex( i );
                    cDebug() << "Translation unavailable, so initial locale set to " << thisLocale.name();
                    QLocale::setDefault( thisLocale );
                    CalamaresUtils::installTranslator( thisLocale.name(),
                                                       Calamares::Branding::instance()->translationsPathPrefix(),
                                                       qApp );
                    break;
                }
            }
        }

        connect( ui->languageWidget,
                 static_cast< void ( QComboBox::* )( int ) >( &QComboBox::currentIndexChanged ),
                 this, [ & ]( int newIndex )
        {
            QLocale selectedLocale = ui->languageWidget->itemData( newIndex, Qt::UserRole ).toLocale();
            cDebug() << "Selected locale" << selectedLocale.name();

            QLocale::setDefault( selectedLocale );
            CalamaresUtils::installTranslator( selectedLocale,
                                               Calamares::Branding::instance()->translationsPathPrefix(),
                                               qApp );
        } );
    }
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

