/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Dominic Hayes <ferenosdev@outlook.com>
 *   Copyright 2019, Gabriel Craciunescu <crazy@frugalware.org>
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#ifndef SETTINGS_H
#define SETTINGS_H

#include "DllMacro.h"
#include "modulesystem/Actions.h"

#include <QObject>
#include <QStringList>


namespace Calamares
{

class DLLEXPORT Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings( const QString& settingsFilePath, bool debugMode, QObject* parent = nullptr );

    static Settings* instance();

    QStringList modulesSearchPaths() const;

    using InstanceDescription = QMap< QString, QString >;
    using InstanceDescriptionList = QList< InstanceDescription >;
    InstanceDescriptionList customModuleInstances() const;

    using ModuleSequence = QList< QPair< ModuleSystem::Action, QStringList > >;
    ModuleSequence modulesSequence() const;

    QString brandingComponentName() const;

    bool showPromptBeforeExecution() const;

    bool debugMode() const;

    bool doChroot() const;
    /** @brief Distinguish between "install" and "setup" modes.
     *
     * This influences user-visible strings, for instance using the
     * word "setup" instead of "install" where relevant.
     */
    bool isSetupMode() const { return m_isSetupMode; }

    /** @brief Global setting of disable-cancel: can't cancel ever. */
    bool disableCancel() const;
    /** @brief Temporary setting of disable-cancel: can't cancel during exec. */
    bool disableCancelDuringExec() const;

private:
    static Settings* s_instance;

    QStringList m_modulesSearchPaths;

    InstanceDescriptionList m_customModuleInstances;
    ModuleSequence m_modulesSequence;

    QString m_brandingComponentName;

    bool m_debug;
    bool m_doChroot;
    bool m_isSetupMode;
    bool m_promptInstall;
    bool m_disableCancel;
    bool m_disableCancelDuringExec;
};

}  // namespace Calamares

#endif  // SETTINGS_H
