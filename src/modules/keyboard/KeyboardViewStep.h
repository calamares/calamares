/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef KEYBOARDVIEWSTEP_H
#define KEYBOARDVIEWSTEP_H

#include "DllMacro.h"
#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include <QObject>

class KeyboardPage;

class PLUGINDLLEXPORT KeyboardViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit KeyboardViewStep( QObject* parent = nullptr );
    ~KeyboardViewStep() override;

    QString prettyName() const override;
    QString prettyStatus() const override;

    QWidget* widget() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    Calamares::JobList jobs() const override;

    void onActivate() override;
    void onLeave() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    KeyboardPage* m_widget;
    bool m_nextEnabled;
    QString m_prettyStatus;

    QString m_xOrgConfFileName;
    QString m_convertedKeymapPath;
    bool m_writeEtcDefaultKeyboard;

    Calamares::JobList m_jobs;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( KeyboardViewStepFactory )

#endif  // KEYBOARDVIEWSTEP_H
