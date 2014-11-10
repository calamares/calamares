/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "CalamaresVersion.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtils.h"
#include "ViewManager.h"

#include <QApplication>
#include <QBoxLayout>
#include <QFocusEvent>
#include <QLabel>
#include <QListWidget>

#include "Branding.h"


GreetingPage::GreetingPage( QWidget* parent )
    : QWidget()
{
    QBoxLayout *mainLayout = new QHBoxLayout;
    setLayout( mainLayout );

    QString defaultLocale = QLocale::system().name();

    m_languageWidget = new QListWidget( this );
    mainLayout->addWidget( m_languageWidget );
    {
        foreach ( const QString& locale, QString( CALAMARES_TRANSLATION_LANGUAGES ).split( ';') )
        {
            QLocale thisLocale = QLocale( locale );
            QString lang = QLocale::languageToString( thisLocale.language() );
            if ( QLocale::countriesForLanguage( thisLocale.language() ).count() > 2 )
                lang.append( QString( " (%1)" )
                             .arg( QLocale::countryToString( thisLocale.country() ) ) );

            m_languageWidget->addItem( lang );
            m_languageWidget->item( m_languageWidget->count() - 1 )
                            ->setData( Qt::UserRole, thisLocale );
            if ( thisLocale.language() == QLocale( defaultLocale ).language() &&
                 thisLocale.country() == QLocale( defaultLocale ).country() )
                m_languageWidget->setCurrentRow( m_languageWidget->count() - 1 );
        }
        m_languageWidget->sortItems();

        connect( m_languageWidget, &QListWidget::currentItemChanged,
                 this, [ & ]( QListWidgetItem *current, QListWidgetItem *previous )
        {
            QLocale selectedLocale = current->data( Qt::UserRole ).toLocale();
            cDebug() << "Selected locale" << selectedLocale.name();

            QLocale::setDefault( selectedLocale );
            CalamaresUtils::installTranslator( selectedLocale.name(), qApp );
        } );

        connect( m_languageWidget, &QListWidget::itemActivated,
                 this, []
        {
            Calamares::ViewManager::instance()->next();
        } );
    }

    QLabel* text = new QLabel( tr( "<h1>Welcome to the %1 installer.</h1><br/>"
                                   "This program will ask you some questions and "
                                   "set up %2 on your computer." )
                               .arg( Calamares::Branding::instance()->
                                     string( Calamares::Branding::VersionedName ) )
                               .arg( Calamares::Branding::instance()->
                                     string( Calamares::Branding::ProductName ) ), this );
    text->setAlignment( Qt::AlignCenter );
    text->setWordWrap( true );
    text->setOpenExternalLinks( true );

    mainLayout->addStretch();
    mainLayout->addWidget( text );
    mainLayout->addStretch();
}


void
GreetingPage::changeEvent( QEvent* e )
{
    QWidget::changeEvent( e );
    switch ( e->type() )
    {
        case QEvent::LanguageChange:
            //TODO: retranslate all widgets
            break;

        default:
            break;
    }
}


void
GreetingPage::focusInEvent( QFocusEvent* e )
{
    if ( m_languageWidget )
        m_languageWidget->setFocus();
    e->accept();
}
