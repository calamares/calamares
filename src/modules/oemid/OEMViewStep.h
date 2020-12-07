/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    ~OEMViewStep() override;

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
