/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2015 Anke Boersma <demm@kaosx.us>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "WelcomePage.h"

#include "checker/CheckerContainer.h"
#include "ui_WelcomePage.h"

#include "Branding.h"
#include "CalamaresAbout.h"
#include "CalamaresVersion.h"
#include "Config.h"
#include "Settings.h"
#include "ViewManager.h"

#include "modulesystem/ModuleManager.h"
#include "modulesystem/RequirementsModel.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Retranslator.h"

#include <QApplication>
#include <QBoxLayout>
#include <QComboBox>
#include <QDesktopServices>
#include <QFocusEvent>
#include <QLabel>
#include <QMessageBox>

WelcomePage::WelcomePage( Config* config, QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::WelcomePage )
    , m_checkingWidget( new CheckerContainer( config, this ) )
    , m_languages( nullptr )
    , m_conf( config )
{
    using Branding = Calamares::Branding;

    const int defaultFontHeight = CalamaresUtils::defaultFontHeight();
    ui->setupUi( this );

    // insert system-check widget below welcome text
    const int welcome_text_idx = ui->verticalLayout->indexOf( ui->mainText );
    ui->verticalLayout->insertWidget( welcome_text_idx + 1, m_checkingWidget );

    // insert optional logo banner image above welcome text
    QString bannerPath = Branding::instance()->imagePath( Branding::ProductBanner );
    if ( !bannerPath.isEmpty() )
    {
        // If the name is not empty, the file exists -- Branding checks that at startup
        QPixmap bannerPixmap = QPixmap( bannerPath );
        if ( !bannerPixmap.isNull() )
        {
            QLabel* bannerLabel = new QLabel;
            bannerLabel->setPixmap( bannerPixmap );
            bannerLabel->setMinimumHeight( 64 );
            bannerLabel->setAlignment( Qt::AlignCenter );
            ui->aboveTextSpacer->changeSize( 20, defaultFontHeight );  // Shrink it down
            ui->aboveTextSpacer->invalidate();
            ui->verticalLayout->insertSpacing( welcome_text_idx, defaultFontHeight );
            ui->verticalLayout->insertWidget( welcome_text_idx, bannerLabel );
        }
    }

    initLanguages();

    CALAMARES_RETRANSLATE_SLOT( &WelcomePage::retranslate );

    connect( Calamares::ModuleManager::instance(),
             &Calamares::ModuleManager::requirementsComplete,
             m_checkingWidget,
             &CheckerContainer::requirementsComplete );
    connect( Calamares::ModuleManager::instance()->requirementsModel(),
             &Calamares::RequirementsModel::progressMessageChanged,
             m_checkingWidget,
             &CheckerContainer::requirementsProgress );
}

void
WelcomePage::init()
{
    //setup the url buttons
    setupButton( WelcomePage::Button::Support, m_conf->supportUrl() );
    setupButton( WelcomePage::Button::KnownIssues, m_conf->knownIssuesUrl() );
    setupButton( WelcomePage::Button::ReleaseNotes, m_conf->releaseNotesUrl() );
    setupButton( WelcomePage::Button::Donate, m_conf->donateUrl() );

    //language icon
    auto icon = Calamares::Branding::instance()->image( m_conf->languageIcon(), QSize( 48, 48 ) );
    if ( !icon.isNull() )
    {
        setLanguageIcon( icon );
    }
}

void
WelcomePage::initLanguages()
{
    // Fill the list of translations
    ui->languageWidget->clear();
    ui->languageWidget->setInsertPolicy( QComboBox::InsertAtBottom );

    ui->languageWidget->setModel( m_conf->languagesModel() );
    ui->languageWidget->setItemDelegate( new LocaleTwoColumnDelegate( ui->languageWidget ) );

    ui->languageWidget->setCurrentIndex( m_conf->localeIndex() );

    connect( ui->languageWidget,
             static_cast< void ( QComboBox::* )( int ) >( &QComboBox::currentIndexChanged ),
             m_conf,
             &Config::setLocaleIndex );
}

void
WelcomePage::setupButton( Button role, const QString& url )
{
    QPushButton* button = nullptr;
    CalamaresUtils::ImageType icon = CalamaresUtils::Information;

    switch ( role )
    {
    case Button::Donate:
        button = ui->donateButton;
        icon = CalamaresUtils::Donate;
        break;
    case Button::KnownIssues:
        button = ui->knownIssuesButton;
        icon = CalamaresUtils::Bugs;
        break;
    case Button::ReleaseNotes:
        button = ui->releaseNotesButton;
        icon = CalamaresUtils::Release;
        break;
    case Button::Support:
        button = ui->supportButton;
        icon = CalamaresUtils::Help;
        break;
    }
    if ( !button )
    {
        cWarning() << "Unknown button role" << smash( role );
        return;
    }

    if ( url.isEmpty() )
    {
        button->hide();
        return;
    }

    QUrl u( url );
    if ( u.isValid() )
    {
        auto size = 2 * QSize( CalamaresUtils::defaultFontHeight(), CalamaresUtils::defaultFontHeight() );
        button->setIcon( CalamaresUtils::defaultPixmap( icon, CalamaresUtils::Original, size ) );
        connect( button, &QPushButton::clicked, [ u ]() { QDesktopServices::openUrl( u ); } );
    }
    else
    {
        cWarning() << "Welcome button" << smash( role ) << "URL" << url << "is invalid.";
        button->hide();
    }
}

void
WelcomePage::focusInEvent( QFocusEvent* e )
{
    if ( ui->languageWidget )
    {
        ui->languageWidget->setFocus();
    }
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
    {
        ui->languageWidget->setCurrentIndex( row );
    }
}

void
WelcomePage::setLanguageIcon( QPixmap i )
{
    ui->languageIcon->setPixmap( i );
}

void
WelcomePage::retranslate()
{
    const QString message = m_conf->genericWelcomeMessage();

    ui->mainText->setText( message.arg( Calamares::Branding::instance()->versionedName() ) );
    ui->retranslateUi( this );
    ui->supportButton->setText( tr( "%1 support" ).arg( Calamares::Branding::instance()->shortProductName() ) );
}

void
LocaleTwoColumnDelegate::paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    QStyledItemDelegate::paint( painter, option, index );
    option.widget->style()->drawItemText(
        painter,
        option.rect,
        Qt::AlignRight | Qt::AlignVCenter,
        option.palette,
        false,
        index.data( CalamaresUtils::Locale::TranslationsModel::EnglishLabelRole ).toString() );
}
