/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
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

#include "Config.h"

#include "Branding.h"
#include "Settings.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"

void
RequirementsModel::setRequirementsList( const Calamares::RequirementsList& requirements )
{
    CALAMARES_RETRANSLATE_SLOT( &RequirementsModel::retranslate )

    emit beginResetModel();
    m_requirements = requirements;

    auto isUnSatisfied = []( const Calamares::RequirementEntry& e ) { return !e.satisfied; };
    auto isMandatoryAndUnSatisfied = []( const Calamares::RequirementEntry& e ) { return e.mandatory && !e.satisfied; };

    m_satisfiedRequirements = std::none_of( m_requirements.begin(), m_requirements.end(), isUnSatisfied );
    m_satisfiedMandatory = std::none_of( m_requirements.begin(), m_requirements.end(), isMandatoryAndUnSatisfied );

    emit satisfiedRequirementsChanged( m_satisfiedRequirements );
    emit satisfiedMandatoryChanged();
    emit endResetModel();
}

int
RequirementsModel::rowCount( const QModelIndex& ) const
{
    return m_requirements.count();
}

QVariant
RequirementsModel::data( const QModelIndex& index, int role ) const
{
    const auto requirement = m_requirements.at( index.row() );

    switch ( role )
    {
    case Roles::Name:
        return requirement.name;
    case Roles::Details:
        return requirement.enumerationText();
    case Roles::NegatedText:
        return requirement.negatedText();
    case Roles::Satisfied:
        return requirement.satisfied;
    case Roles::Mandatory:
        return requirement.mandatory;
    default:
        return QVariant();
    }
}

QHash< int, QByteArray >
RequirementsModel::roleNames() const
{
    static QHash< int, QByteArray > roles;
    roles[ Roles::Name ] = "name";
    roles[ Roles::Details ] = "details";
    roles[ Roles::NegatedText ] = "negatedText";
    roles[ Roles::Satisfied ] = "satisfied";
    roles[ Roles::Mandatory ] = "mandatory";
    return roles;
}

Config::Config( QObject* parent )
    : QObject( parent )
    , m_requirementsModel( new RequirementsModel( this ) )
    , m_languages( CalamaresUtils::Locale::availableTranslations() )
{
    connect( m_requirementsModel, &RequirementsModel::satisfiedRequirementsChanged, this, &Config::setIsNextEnabled );

    initLanguages();

    CALAMARES_RETRANSLATE_SLOT( &Config::retranslate )
}

void
Config::retranslate()
{
    m_genericWelcomeMessage = genericWelcomeMessage().arg( *Calamares::Branding::VersionedName );
    emit genericWelcomeMessageChanged();

    m_requirementsModel->retranslate();
}

CalamaresUtils::Locale::LabelModel*
Config::languagesModel() const
{
    return m_languages;
}

QString
Config::languageIcon() const
{
    return m_languageIcon;
}

void
Config::initLanguages()
{
    // Find the best initial translation
    QLocale defaultLocale = QLocale( QLocale::system().name() );

    cDebug() << "Matching locale" << defaultLocale;
    int matchedLocaleIndex = m_languages->find( [&]( const QLocale& x ) {
        return x.language() == defaultLocale.language() && x.country() == defaultLocale.country();
    } );

    if ( matchedLocaleIndex < 0 )
    {
        cDebug() << Logger::SubEntry << "Matching approximate locale" << defaultLocale.language();

        matchedLocaleIndex
            = m_languages->find( [&]( const QLocale& x ) { return x.language() == defaultLocale.language(); } );
    }

    if ( matchedLocaleIndex < 0 )
    {
        QLocale en_us( QLocale::English, QLocale::UnitedStates );

        cDebug() << Logger::SubEntry << "Matching English (US)";
        matchedLocaleIndex = m_languages->find( en_us );

        // Now, if it matched, because we didn't match the system locale, switch to the one found
        if ( matchedLocaleIndex >= 0 )
        {
            QLocale::setDefault( m_languages->locale( matchedLocaleIndex ).locale() );
        }
    }

    if ( matchedLocaleIndex >= 0 )
    {
        QString name = m_languages->locale( matchedLocaleIndex ).name();
        cDebug() << Logger::SubEntry << "Matched with index" << matchedLocaleIndex << name;

        CalamaresUtils::installTranslator( name, Calamares::Branding::instance()->translationsDirectory() );
        setLocaleIndex( matchedLocaleIndex );
    }
    else
    {
        cWarning() << "No available translation matched" << defaultLocale;
    }
}

void
Config::setCountryCode( const QString& countryCode )
{
    m_countryCode = countryCode;
    setLocaleIndex( CalamaresUtils::Locale::availableTranslations()->find( m_countryCode ) );

    emit countryCodeChanged( m_countryCode );
}

void
Config::setLanguageIcon( const QString& languageIcon )
{
    m_languageIcon = languageIcon;
}

void
Config::setLocaleIndex( const int& index )
{
    if ( index == m_localeIndex || index > CalamaresUtils::Locale::availableTranslations()->rowCount( QModelIndex() )
         || index < 0 )
    {
        return;
    }

    m_localeIndex = index;

    const auto& selectedLocale = m_languages->locale( m_localeIndex ).locale();
    cDebug() << "Selected locale" << selectedLocale;

    QLocale::setDefault( selectedLocale );
    CalamaresUtils::installTranslator( selectedLocale, Calamares::Branding::instance()->translationsDirectory() );

    emit localeIndexChanged( m_localeIndex );
}

RequirementsModel&
Config::requirementsModel() const
{
    return *m_requirementsModel;
}

void
Config::setIsNextEnabled( const bool& isNextEnabled )
{
    m_isNextEnabled = isNextEnabled;
    emit isNextEnabledChanged( m_isNextEnabled );
}

QString
Config::donateUrl() const
{
    return m_donateUrl;
}

void
Config::setDonateUrl( const QString& url )
{
    m_donateUrl = url;
    emit donateUrlChanged();
}

QString
Config::knownIssuesUrl() const
{
    return m_knownIssuesUrl;
}

void
Config::setKnownIssuesUrl( const QString& url )
{
    m_knownIssuesUrl = url;
    emit knownIssuesUrlChanged();
}

void
Config::setReleaseNotesUrl( const QString& url )
{
    m_releaseNotesUrl = url;
    emit releaseNotesUrlChanged();
}

QString
Config::releaseNotesUrl() const
{
    return m_releaseNotesUrl;
}

QString
Config::supportUrl() const
{
    return m_supportUrl;
}

void
Config::setSupportUrl( const QString& url )
{
    m_supportUrl = url;
    emit supportUrlChanged();
}

void
RequirementsModel::retranslate()
{
    if ( !m_satisfiedRequirements )
    {
        QString message;
        const bool setup = Calamares::Settings::instance()->isSetupMode();

        if ( !m_satisfiedMandatory )
        {
            message = setup ? tr( "This computer does not satisfy the minimum "
                                  "requirements for setting up %1.<br/>"
                                  "Setup cannot continue. "
                                  "<a href=\"#details\">Details...</a>" )
                            : tr( "This computer does not satisfy the minimum "
                                  "requirements for installing %1.<br/>"
                                  "Installation cannot continue. "
                                  "<a href=\"#details\">Details...</a>" );
        }
        else
        {
            message = setup ? tr( "This computer does not satisfy some of the "
                                  "recommended requirements for setting up %1.<br/>"
                                  "Setup can continue, but some features "
                                  "might be disabled." )
                            : tr( "This computer does not satisfy some of the "
                                  "recommended requirements for installing %1.<br/>"
                                  "Installation can continue, but some features "
                                  "might be disabled." );
        }

        m_warningMessage = message.arg( *Calamares::Branding::ShortVersionedName );
    }
    else
    {
        m_warningMessage = tr( "This program will ask you some questions and "
                               "set up %2 on your computer." )
                               .arg( *Calamares::Branding::ProductName );
    }

    emit warningMessageChanged();
}

QString
Config::genericWelcomeMessage()
{
    QString message;

    if ( Calamares::Settings::instance()->isSetupMode() )
    {
        message = Calamares::Branding::instance()->welcomeStyleCalamares()
            ? tr( "<h1>Welcome to the Calamares setup program for %1.</h1>" )
            : tr( "<h1>Welcome to %1 setup.</h1>" );
    }
    else
    {
        message = Calamares::Branding::instance()->welcomeStyleCalamares()
            ? tr( "<h1>Welcome to the Calamares installer for %1.</h1>" )
            : tr( "<h1>Welcome to the %1 installer.</h1>" );
    }

    return message;
}
