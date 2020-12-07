/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2020 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef NOTESQMLVIEWSTEP_H
#define NOTESQMLVIEWSTEP_H

#include "DllMacro.h"
#include "locale/TranslatableConfiguration.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/PluginFactory.h"
#include "utils/Variant.h"
#include "viewpages/QmlViewStep.h"

class PLUGINDLLEXPORT NotesQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    NotesQmlViewStep( QObject* parent = nullptr );
    ~NotesQmlViewStep() override;

    QString prettyName() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    CalamaresUtils::Locale::TranslatedString* m_notesName;  // As it appears in the sidebar
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( NotesQmlViewStepFactory )

#endif
