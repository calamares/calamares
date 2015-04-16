/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2015,      Anke Boersma <demm@kaosx.us>
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

#include "GreetingPage.h"

#include "ui_GreetingPage.h"
#include "CalamaresVersion.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"
#include "ViewManager.h"

#include <QApplication>
#include <QBoxLayout>
#include <QDesktopServices>
#include <QFocusEvent>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>

#include "Branding.h"


GreetingPage::GreetingPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::GreetingPage )
{
    ui->setupUi( this );

    QLocale defaultLocale = QLocale( QLocale::system().name() );
    {
        bool isTranslationAvailable = false;

        foreach ( const QString& locale, QString( CALAMARES_TRANSLATION_LANGUAGES ).split( ';') )
        {
            QLocale thisLocale = QLocale( locale );
            QString lang = QLocale::languageToString( thisLocale.language() );
            if ( QLocale::countriesForLanguage( thisLocale.language() ).count() > 2 )
                lang.append( QString( " (%1)" )
                             .arg( QLocale::countryToString( thisLocale.country() ) ) );

            ui->languageWidget->addItem( lang );
            ui->languageWidget->item( ui->languageWidget->count() - 1 )
                            ->setData( Qt::UserRole, thisLocale );
            if ( thisLocale.language() == defaultLocale.language() &&
                 thisLocale.country() == defaultLocale.country() )
            {
                isTranslationAvailable = true;
                ui->languageWidget->setCurrentRow( ui->languageWidget->count() - 1 );
                cDebug() << "Initial locale " << thisLocale.name();
                CalamaresUtils::installTranslator( thisLocale.name(), qApp );
            }
        }
        ui->languageWidget->sortItems();

        if ( !isTranslationAvailable )
        {
            for (int i = 0; i < ui->languageWidget->count(); i++)
            {
                QLocale thisLocale = ui->languageWidget->item(i)->data( Qt::UserRole ).toLocale();
                if ( thisLocale.language() == defaultLocale.language() )
                {
                    isTranslationAvailable = true;
                    ui->languageWidget->setCurrentRow( i );
                    cDebug() << "Initial locale " << thisLocale.name();
                    CalamaresUtils::installTranslator( thisLocale.name(), qApp );
                    break;
                }
            }
        }

        if ( !isTranslationAvailable )
        {
            for (int i = 0; i < ui->languageWidget->count(); i++)
            {
                QLocale thisLocale = ui->languageWidget->item(i)->data( Qt::UserRole ).toLocale();
                if ( thisLocale == QLocale( QLocale::English, QLocale::UnitedStates ) )
                {
                    ui->languageWidget->setCurrentRow( i );
                    cDebug() << "Translation unavailable, so initial locale set to " << thisLocale.name();
                    QLocale::setDefault( thisLocale );
                    CalamaresUtils::installTranslator( thisLocale.name(), qApp );
                    break;
                }
            }
        }

        connect( ui->languageWidget, &QListWidget::currentItemChanged,
                 this, [ & ]( QListWidgetItem *current, QListWidgetItem *previous )
        {
            QLocale selectedLocale = current->data( Qt::UserRole ).toLocale();
            cDebug() << "Selected locale" << selectedLocale.name();

            QLocale::setDefault( selectedLocale );
            CalamaresUtils::installTranslator( selectedLocale.name(), qApp );
        } );

        connect( ui->languageWidget, &QListWidget::itemDoubleClicked,
                 this, []
        {
            Calamares::ViewManager::instance()->next();
        } );
    }

    ui->mainText->setAlignment( Qt::AlignCenter );
    ui->mainText->setWordWrap( true );
    ui->mainText->setOpenExternalLinks( true );

    CALAMARES_RETRANSLATE(
        ui->mainText->setText( tr( "<h1>Welcome to the %1 installer.</h1><br/>"
                                   "This program will ask you some questions and "
                                   "set up %2 on your computer." )
                                .arg( Calamares::Branding::instance()->
                                      string( Calamares::Branding::VersionedName ) )
                                .arg( Calamares::Branding::instance()->
                                      string( Calamares::Branding::ProductName ) ) );
        ui->retranslateUi( this );
    )

    ui->aboutButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Information,
                                                             CalamaresUtils::Original,
                                                             2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                    CalamaresUtils::defaultFontHeight() ) ) );
    connect( ui->aboutButton, &QPushButton::clicked,
             this, [ this ]
    {
        QMessageBox::about( this,
                            tr( "About %1 installer" )
                                .arg( CALAMARES_APPLICATION_NAME ),
                            tr(
                                "<h1>%1</h1><br/>"
                                "<strong>%2<br/>"
                                "for %3</strong><br/><br/>"
                                "Copyright 2014 Teo Mrnjavac &lt;teo@kde.org&gt;<br/>"
                                "Thanks to: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Philip Müller, "
                                "Pier Luigi Fiorini and Rohan Garg.<br/><br/>"
                                "<a href=\"http://calamares.io/\">Calamares</a> "
                                "development is sponsored by <br/>"
                                "<a href=\"http://www.blue-systems.com/\">Blue Systems</a> - "
                                "Liberating Software."
                            )
                            .arg( CALAMARES_APPLICATION_NAME )
                            .arg( CALAMARES_VERSION )
                            .arg( Calamares::Branding::instance()->string(
                                      Calamares::Branding::VersionedName ) ) );
    } );
}


void
GreetingPage::setUpLinks( bool showSupportUrl,
                          bool showKnownIssuesUrl,
                          bool showReleaseNotesUrl )
{
    using namespace Calamares;
    Branding* b = Branding::instance();
    if ( showSupportUrl && !b->string( Branding::SupportUrl ).isEmpty() )
    {
        CALAMARES_RETRANSLATE(
            ui->supportButton->setText( tr( "%1 support" )
                                        .arg( b->string( Branding::ShortProductName ) ) );
        )
        ui->supportButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Help,
                                                                   CalamaresUtils::Original,
                                                                   2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                          CalamaresUtils::defaultFontHeight() ) ) );
        connect( ui->supportButton, &QPushButton::clicked, []
        {
            QDesktopServices::openUrl( Branding::instance()->string( Branding::SupportUrl ) );
        } );
    }
    else
    {
        ui->supportButton->hide();
    }

    if ( showKnownIssuesUrl && !b->string( Branding::KnownIssuesUrl ).isEmpty() )
    {
        ui->knownIssuesButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Bugs,
                                                                       CalamaresUtils::Original,
                                                                       2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                              CalamaresUtils::defaultFontHeight() ) ) );
        connect( ui->knownIssuesButton, &QPushButton::clicked, []
        {
            QDesktopServices::openUrl( Branding::instance()->string( Branding::KnownIssuesUrl ) );
        } );
    }
    else
    {
        ui->knownIssuesButton->hide();
    }

    if ( showReleaseNotesUrl && !b->string( Branding::ReleaseNotesUrl ).isEmpty() )
    {
        ui->releaseNotesButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Release,
                                                                        CalamaresUtils::Original,
                                                                        2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                               CalamaresUtils::defaultFontHeight() ) ) );
        connect( ui->releaseNotesButton, &QPushButton::clicked, []
        {
            QDesktopServices::openUrl( Branding::instance()->string( Branding::ReleaseNotesUrl ) );
        } );
    }
    else
    {
        ui->releaseNotesButton->hide();
    }
}


void
GreetingPage::focusInEvent( QFocusEvent* e )
{
    if ( ui->languageWidget )
        ui->languageWidget->setFocus();
    e->accept();
}

