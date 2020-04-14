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

#ifndef OEMVIEWSTEP_H
#define OEMVIEWSTEP_H

#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include "DllMacro.h"

#include <QVariantMap>

class OEMPage;

class PLUGINDLLEXPORT OEMViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit OEMViewStep( QObject* parent = nullptr );
    virtual ~OEMViewStep() override;

    QString prettyName() const override;
    QString prettyStatus() const override;

    QWidget* widget() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    void onActivate() override;
    void onLeave() override;

    Calamares::JobList jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    QString m_conf_batchIdentifier;
    QString m_user_batchIdentifier;
    OEMPage* m_widget;
    bool m_visited;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( OEMViewStepFactory )

#endif
