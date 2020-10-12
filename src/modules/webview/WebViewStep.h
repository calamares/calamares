/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015 Rohan Garg <rohan@garg.io>
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef WEBVIEWPLUGIN_H
#define WEBVIEWPLUGIN_H

#include "WebViewConfig.h"

#include "DllMacro.h"
#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include <QVariantMap>

#ifdef WEBVIEW_WITH_WEBKIT
#define C_QWEBVIEW QWebView
#endif
#ifdef WEBVIEW_WITH_WEBENGINE
#ifdef C_QWEBVIEW
#error Both WEBENGINE and WEBKIT enabled
#endif
#define C_QWEBVIEW QWebEngineView
#endif
#ifndef C_QWEBVIEW
#error Neither WEBENGINE nor WEBKIT enabled
#endif

class C_QWEBVIEW;

class PLUGINDLLEXPORT WebViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit WebViewStep( QObject* parent = nullptr );
    ~WebViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    void onActivate() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    QList< Calamares::job_ptr > jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    C_QWEBVIEW* m_view;
    QString m_url;
    QString m_prettyName;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( WebViewStepFactory )

#endif  // WEBVIEWPLUGIN_H
