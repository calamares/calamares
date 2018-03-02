/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Rohan Garg <rohan@garg.io>
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#ifndef WEBVIEWPLUGIN_H
#define WEBVIEWPLUGIN_H

#include "WebViewConfig.h"

#include <utils/PluginFactory.h>
#include <viewpages/ViewStep.h>

#include <PluginDllMacro.h>

#include <QVariantMap>

#ifdef WEBVIEW_WITH_WEBKIT
#define C_QWEBVIEW QWebView
#else
#define C_QWEBVIEW QWebEngineView
#endif

class C_QWEBVIEW;

class PLUGINDLLEXPORT WebViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit WebViewStep( QObject* parent = nullptr );
    virtual ~WebViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;
    void onActivate() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    QList< Calamares::job_ptr > jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    C_QWEBVIEW *m_view;
    QString m_url;
    QString m_prettyName;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( WebViewStepFactory )

#endif // WEBVIEWPLUGIN_H
