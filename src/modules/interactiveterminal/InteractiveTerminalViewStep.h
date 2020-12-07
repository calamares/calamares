/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef INTERACTIVETERMINALPAGEPLUGIN_H
#define INTERACTIVETERMINALPAGEPLUGIN_H

#include <QObject>

#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include "DllMacro.h"

class InteractiveTerminalPage;

class PLUGINDLLEXPORT InteractiveTerminalViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit InteractiveTerminalViewStep( QObject* parent = nullptr );
    ~InteractiveTerminalViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    QList< Calamares::job_ptr > jobs() const override;

    void onActivate() override;

protected:
    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    InteractiveTerminalPage* m_widget;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( InteractiveTerminalViewStepFactory )

#endif  // INTERACTIVETERMINALPAGEPLUGIN_H
