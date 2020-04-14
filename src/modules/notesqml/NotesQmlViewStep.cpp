/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
 *   Copyright 2020, Anke Boersma <demm@kaosx.us>
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

#include "NotesQmlViewStep.h"

#include <QVariant>

NotesQmlViewStep::NotesQmlViewStep( QObject* parent )
    : Calamares::QmlViewStep( parent )
{
}

NotesQmlViewStep::~NotesQmlViewStep() {}

QString
NotesQmlViewStep::prettyName() const
{
    return m_notesName ? m_notesName->get() : tr( "Notes" );
}

void
NotesQmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    bool qmlLabel_ok = false;
    auto qmlLabel = CalamaresUtils::getSubMap( configurationMap, "qmlLabel", qmlLabel_ok );

    if ( qmlLabel.contains( "notes" ) )
    {
        m_notesName = new CalamaresUtils::Locale::TranslatedString( qmlLabel, "notes" );
    }

    Calamares::QmlViewStep::setConfigurationMap( configurationMap ); // call parent implementation last
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( NotesQmlViewStepFactory, registerPlugin< NotesQmlViewStep >(); )
