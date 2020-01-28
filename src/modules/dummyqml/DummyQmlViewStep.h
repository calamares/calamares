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

#ifndef DUMMYQMLVIEWSTEP_H
#define DUMMYQMLVIEWSTEP_H

#include "PluginDllMacro.h"
#include "locale/TranslatableConfiguration.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Variant.h"
#include "utils/PluginFactory.h"
#include "viewpages/QmlViewStep.h"

class PLUGINDLLEXPORT DummyQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    DummyQmlViewStep( QObject* parent = nullptr );
    virtual ~DummyQmlViewStep() override;

    QString prettyName() const override;
    
    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    CalamaresUtils::Locale::TranslatedString* m_notesName;  // As it appears in the sidebar
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( DummyQmlViewStepFactory )

#endif
