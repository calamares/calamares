/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include <QDebug>

Config::Config( QObject* parent ) : QObject( parent )
{
}

Config::~Config()
{
}

CalamaresUtils::Locale::LabelModel*
Config::languagesModel() const
{
	return CalamaresUtils::Locale::availableTranslations();
}

static QString
jobOrBrandingSetting( Calamares::Branding::StringEntry e, const QVariantMap& map, const QString& key )
{
	if ( !map.contains( key ) )
	{
		return QString();
	}
	auto v = map.value( key );
	if ( v.type() == QVariant::Bool )
	{
		return v.toBool() ? ( *e ) : QString();
	}
	if ( v.type() == QVariant::String )
	{
		return v.toString();
	}

	return QString();
}

QUrl
Config::donateUrl() const
{
	return jobOrBrandingSetting( Calamares::Branding::SupportUrl, m_configurationMap, "showDonateUrl" );
}

QUrl
Config::knownIssuesUrl() const
{
	return jobOrBrandingSetting( Calamares::Branding::SupportUrl, m_configurationMap, "showKnownIssuesUrl" );
}

QUrl
Config::releaseNotesUrl() const
{
	return jobOrBrandingSetting( Calamares::Branding::SupportUrl, m_configurationMap, "showReleaseNotesUrl" );
}

QUrl
Config::supportUrl() const
{
	 return jobOrBrandingSetting( Calamares::Branding::SupportUrl, m_configurationMap, "showSupportUrl" );
}

QString
Config::languageIcon() const
{
	return m_languageIcon;
}

void
Config::setConfigurationMap(const QVariantMap& configurationMap)
{
	m_configurationMap = configurationMap;
}

void
Config::setCountryCode(const QString& countryCode)
{
	m_countryCode = countryCode;
	m_localeIndex = CalamaresUtils::Locale::availableTranslations()->find( m_countryCode );

	emit countryCodeChanged( m_countryCode );
	emit localeIndexChanged( m_localeIndex );
}

void
Config::setLanguageIcon(const QString languageIcon)
{
	m_languageIcon = languageIcon;
}

void Config::setRequirementsCheck(const QVariantMap& requirementsCheck)
{
	m_requirementsCheck = requirementsCheck;

	qDebug() << m_requirementsCheck;
	emit requirementsCheckChanged( m_requirementsCheck );
}







