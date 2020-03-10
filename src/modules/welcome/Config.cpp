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
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "Branding.h"
#include "Settings.h"

#include <QApplication>

void
RequirementsModel::setRequirementsList( const Calamares::RequirementsList& requirements )
{
    emit beginResetModel();
    m_requierements = requirements;
    m_satisfiedRequirements = true;

    auto isUnSatisfied = []( const Calamares::RequirementEntry& e ) { return !e.satisfied; };
    auto isMandatoryAndUnSatisfied = []( const Calamares::RequirementEntry& e ) { return e.mandatory && !e.satisfied; };

    m_satisfiedRequirements = std::none_of( m_requierements.begin(), m_requierements.end(), isUnSatisfied );
    m_satisfiedMandatory = std::none_of( m_requierements.begin(), m_requierements.end(), isMandatoryAndUnSatisfied );

    emit satisfiedRequirementsChanged(m_satisfiedRequirements);
    emit satisfiedMandatoryChanged();
    emit endResetModel();
}

int
RequirementsModel::rowCount( const QModelIndex& ) const
{
    return m_requierements.count();
}

QVariant
RequirementsModel::data( const QModelIndex& index, int role ) const
{
    const auto requirement = m_requierements.at( index.row() );

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

QHash<int, QByteArray>
RequirementsModel::roleNames() const
{
    static QHash<int, QByteArray> roles;
	roles[Roles::Name] = "name";
	roles[Roles::Details] = "details";
	roles[Roles::NegatedText] = "negatedText";
	roles[Roles::Satisfied] = "satisfied";
	roles[Roles::Mandatory] = "mandatory";
	return roles;
}

Config::Config( QObject* parent ) : QObject( parent )
    , m_requirementsModel( new RequirementsModel( this ))
    , m_languages( CalamaresUtils::Locale::availableTranslations() )
{
    connect(m_requirementsModel, &RequirementsModel::satisfiedRequirementsChanged, this, &Config::setIsNextEnabled);

    initLanguages();

    CALAMARES_RETRANSLATE_SLOT( &Config::retranslate )

}

void
Config::retranslate()
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

    m_genericWelcomeMessage = message.arg( *Calamares::Branding::VersionedName );
    emit genericWelcomeMessageChanged();

//     ui->supportButton->setText( tr( "%1 support" ).arg( *Calamares::Branding::ShortProductName ) );
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

        CalamaresUtils::installTranslator( name, Calamares::Branding::instance()->translationsDirectory(), qApp );
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
    setLocaleIndex(CalamaresUtils::Locale::availableTranslations()->find( m_countryCode ));

	emit countryCodeChanged( m_countryCode );
}

void
Config::setLanguageIcon(const QString &languageIcon )
{
	m_languageIcon = languageIcon;
}

void
Config::setLocaleIndex(const int& index)
{
    if(index ==  m_localeIndex || index > CalamaresUtils::Locale::availableTranslations()->rowCount(QModelIndex()) || index < 0)
        return;

    m_localeIndex = index;

    const auto& selectedLocale = m_languages->locale( m_localeIndex ).locale();
    cDebug() << "Selected locale" << selectedLocale;

    QLocale::setDefault( selectedLocale );
    CalamaresUtils::installTranslator(
        selectedLocale, Calamares::Branding::instance()->translationsDirectory(), qApp );

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

QString Config::donateUrl() const
{
    return m_donateUrl;
}

void Config::setDonateUrl(const QString& url)
{
    m_donateUrl = url;
}

QString Config::knownIssuesUrl() const
{
    return m_knownIssuesUrl;
}

void Config::setKnownIssuesUrl(const QString& url)
{
    m_knownIssuesUrl = url;
}

void Config::setReleaseNotesUrl(const QString& url)
{
  m_releaseNotesUrl = url;
}

QString Config::releaseNotesUrl() const
{
    return m_releaseNotesUrl;
}

QString Config::supportUrl() const
{
    return m_supportUrl;
}

void Config::setSupportUrl(const QString& url)
{
    m_supportUrl = url;
}









