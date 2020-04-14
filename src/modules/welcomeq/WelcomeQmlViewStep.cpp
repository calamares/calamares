/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018,2020 Adriaan de Groot <groot@kde.org>
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

#include "WelcomeQmlViewStep.h"

#include "checker/GeneralRequirements.h"

#include "geoip/Handler.h"
#include "locale/LabelModel.h"
#include "locale/Lookup.h"
#include "utils/Logger.h"
#include "utils/Variant.h"
#include "utils/Dirs.h"

#include "Branding.h"
#include "modulesystem/ModuleManager.h"
#include <QQmlEngine>
#include "utils/Yaml.h"

#include <QFutureWatcher>
#include <QPixmap>
#include <QVariant>

CALAMARES_PLUGIN_FACTORY_DEFINITION( WelcomeQmlViewStepFactory, registerPlugin< WelcomeQmlViewStep >(); )

WelcomeQmlViewStep::WelcomeQmlViewStep( QObject* parent )
: Calamares::QmlViewStep(parent )
	, m_config( new Config( this ) ) // the qml singleton takes ownership and deletes it
//     , m_nextEnabled( false )
    , m_requirementsChecker( new GeneralRequirements( this ) )

{
// 	connect( m_config,
//              &Config::isNextEnabledChanged,
// 			 this,
// 			 &WelcomeQmlViewStep::nextStatusChanged );
//     emit nextStatusChanged(true);
}


QString
WelcomeQmlViewStep::prettyName() const
{
	return tr( "Welcome" );
}

bool
WelcomeQmlViewStep::isNextEnabled() const
{
	// TODO: should return true
//     return m_config->property("isNextEnabled").toBool();
    return true;
}

bool
WelcomeQmlViewStep::isBackEnabled() const
{
	// TODO: should return true (it's weird that you are not allowed to have welcome *after* anything
	return false;
}


bool
WelcomeQmlViewStep::isAtBeginning() const
{
	// TODO: adjust to "pages" in the QML
	return true;
}


bool
WelcomeQmlViewStep::isAtEnd() const
{
	// TODO: adjust to "pages" in the QML
	return true;
}


Calamares::JobList
WelcomeQmlViewStep::jobs() const
{
	return Calamares::JobList();
}

/** @brief Look up a URL for a button
 *
 * Looks up @p key in @p map; if it is a *boolean* value, then
 * assume an old-style configuration, and fetch the string from
 * the branding settings @p e. If it is a string, not a boolean,
 * use it as-is. If not found, or a weird type, returns empty.
 *
 * This allows switching the showKnownIssuesUrl and similar settings
 * in welcome.conf from a boolean (deferring to branding) to an
 * actual string for immediate use. Empty strings, as well as
 * "false" as a setting, will hide the buttons as before.
 */
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

void
WelcomeQmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
	using Calamares::Branding;
    m_config->setSupportUrl( jobOrBrandingSetting( Branding::SupportUrl, configurationMap, "showSupportUrl" ) );
    m_config->setKnownIssuesUrl( jobOrBrandingSetting( Branding::KnownIssuesUrl, configurationMap, "showKnownIssuesUrl" ) );
    m_config->setReleaseNotesUrl( jobOrBrandingSetting( Branding::ReleaseNotesUrl, configurationMap, "showReleaseNotesUrl" ) );
    m_config->setDonateUrl( CalamaresUtils::getString( configurationMap, "showDonateUrl" ) );

	// TODO: expand Config class and set the remaining fields // with the configurationMap all those properties can be accessed without having to declare a property, get and setter for each

	// TODO: figure out how the requirements (held by ModuleManager) should be accessible
	//          to QML as a model. //will be model as a qvariantmap containing a alert level and the message string
	if ( configurationMap.contains( "requirements" )
		 && configurationMap.value( "requirements" ).type() == QVariant::Map )
	{
		m_requirementsChecker->setConfigurationMap( configurationMap.value( "requirements" ).toMap() );

        m_config->requirementsModel().setRequirementsList( checkRequirements() );
	}
	else
		cWarning() << "no valid requirements map found in welcome "
					  "module configuration.";

	bool ok = false;
	QVariantMap geoip = CalamaresUtils::getSubMap( configurationMap, "geoip", ok );
	if ( ok )
	{
		using FWString = QFutureWatcher< QString >;

		auto* handler = new CalamaresUtils::GeoIP::Handler( CalamaresUtils::getString( geoip, "style" ),
															CalamaresUtils::getString( geoip, "url" ),
															CalamaresUtils::getString( geoip, "selector" ) );
		if ( handler->type() != CalamaresUtils::GeoIP::Handler::Type::None )
		{
			auto* future = new FWString();
			connect( future, &FWString::finished, [view = this, f = future, h = handler]() {
				QString countryResult = f->future().result();
				cDebug() << "GeoIP result for welcome=" << countryResult;
				view->setCountry( countryResult, h );
				f->deleteLater();
				delete h;
			} );
			future->setFuture( handler->queryRaw() );
		}
		else
		{
			// Would not produce useful country code anyway.
			delete handler;
		}
	}

	QString language = CalamaresUtils::getString( configurationMap, "languageIcon" );
	if ( !language.isEmpty() )
	{
		auto icon = Calamares::Branding::instance()->image( language, QSize( 48, 48 ) );
		if ( !icon.isNull() )
		{
			m_config->setLanguageIcon(language);
		}
	}

    Calamares::QmlViewStep::setConfigurationMap( configurationMap ); // call parent implementation last
    setContextProperty( "Welcome", m_config );
}

Calamares::RequirementsList
WelcomeQmlViewStep::checkRequirements()
{
	return m_requirementsChecker->checkRequirements();
}

QObject*
WelcomeQmlViewStep::getConfig()
{
	return m_config;
}

static inline void
logGeoIPHandler( CalamaresUtils::GeoIP::Handler* handler )
{
	if ( handler )
	{
		cDebug() << Logger::SubEntry << "Obtained from" << handler->url() << " ("
				 << static_cast< int >( handler->type() ) << handler->selector() << ')';
	}
}

void
WelcomeQmlViewStep::setCountry( const QString& countryCode, CalamaresUtils::GeoIP::Handler* handler )
{
	if ( countryCode.length() != 2 )
	{
		cDebug() << "Unusable country code" << countryCode;
		logGeoIPHandler( handler );
		return;
	}

	auto c_l = CalamaresUtils::Locale::countryData( countryCode );
	if ( c_l.first == QLocale::Country::AnyCountry )
	{
		cDebug() << "Unusable country code" << countryCode;
		logGeoIPHandler( handler );
		return;
	}
	else
	{
		int r = CalamaresUtils::Locale::availableTranslations()->find( countryCode );
		if ( r < 0 )
		{
			cDebug() << "Unusable country code" << countryCode << "(no suitable translation)";
		}
		if ( ( r >= 0 ) )
		{
			// TODO: update Config to point to selected language
			m_config->setCountryCode( countryCode );
		}
	}
}
