/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef FINISHEDVIEWSTEP_H
#define FINISHEDVIEWSTEP_H

#include <QObject>

#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include "DllMacro.h"

class FinishedPage;

class PLUGINDLLEXPORT FinishedViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    enum class RestartMode
    {
        Never = 0,  ///< @brief Don't show button, just exit
        UserUnchecked,  ///< @brief Show button, starts unchecked
        UserChecked,  ///< @brief Show button, starts checked
        Always  ///< @brief Show button, can't change, checked
    };
    /// @brief Returns the config-name of the given restart-mode @p m
    static QString modeName( RestartMode m );

    explicit FinishedViewStep( QObject* parent = nullptr );
    virtual ~FinishedViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    void onActivate() override;

    Calamares::JobList jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

public slots:
    void onInstallationFailed( const QString& message, const QString& details );

private:
    FinishedPage* m_widget;

    /**
     * @brief At the end of installation (when this step is activated),
     *      send a desktop notification via DBus that the install is done.
     */
    void sendNotification();

    bool installFailed;
    bool m_notifyOnFinished;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( FinishedViewStepFactory )

#endif
