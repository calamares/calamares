/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#include "utils/PluginFactory.h"
#include "viewpages/QmlViewStep.h"

class DummyQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    DummyQmlViewStep( QObject* parent = nullptr );
    virtual ~DummyQmlViewStep() override;

    virtual QString prettyName() const override;

private:
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( DummyQmlViewStepFactory )

#endif
