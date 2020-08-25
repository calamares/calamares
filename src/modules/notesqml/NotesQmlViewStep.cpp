/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2020 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
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

    Calamares::QmlViewStep::setConfigurationMap( configurationMap );  // call parent implementation last
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( NotesQmlViewStepFactory, registerPlugin< NotesQmlViewStep >(); )
