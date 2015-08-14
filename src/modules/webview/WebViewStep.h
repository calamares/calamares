/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015, Rohan Garg <rohan@garg.io>
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

#include <QObject>

#include "viewpages/ViewStep.h"
#include "PluginDllMacro.h"

#include <QVariantMap>

class QWebView;

class PLUGINDLLEXPORT WebViewStep : public Calamares::ViewStep
{
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "calamares.ViewModule/1.0" )

    Q_INTERFACES( Calamares::ViewStep )

public:
    explicit WebViewStep( QObject* parent = nullptr );
    virtual ~WebViewStep();

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
    QWebView *m_view;
    QString m_url;
    QString m_prettyName;
};

#endif // WEBVIEWPLUGIN_H
