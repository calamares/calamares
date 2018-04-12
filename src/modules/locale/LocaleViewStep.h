/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
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

#ifndef LOCALEVIEWSTEP_H
#define LOCALEVIEWSTEP_H

#include <QObject>

#include <utils/PluginFactory.h>
#include <viewpages/ViewStep.h>

#include <PluginDllMacro.h>

#include <QFutureWatcher>

class LocalePage;
class WaitingWidget;

class PLUGINDLLEXPORT LocaleViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit LocaleViewStep( QObject* parent = nullptr );
    virtual ~LocaleViewStep() override;

    QString prettyName() const override;
    QString prettyStatus() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    QList< Calamares::job_ptr > jobs() const override;

    void onActivate() override;
    void onLeave() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private slots:
    void setUpPage();

private:
    void fetchGeoIpTimezone();
    QWidget* m_widget;
    QFutureWatcher< void > m_initWatcher;
    WaitingWidget* m_waitingWidget;

    LocalePage* m_actualWidget;
    bool m_nextEnabled;
    QString m_prettyStatus;

    QPair< QString, QString > m_startingTimezone;
    QString m_localeGenPath;
    QString m_geoipUrl;
    QString m_geoipStyle;

    QList< Calamares::job_ptr > m_jobs;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( LocaleViewStepFactory )

#endif // LOCALEVIEWSTEP_H
