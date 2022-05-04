/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015 Rohan Garg <rohan@garg.io>
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "WebViewStep.h"

#include <QVariant>

#ifdef WEBVIEW_WITH_WEBKIT
#include <QWebView>
#else
#include <QWebEngineView>
#include <QtWebEngine>
#endif

CALAMARES_PLUGIN_FACTORY_DEFINITION( WebViewStepFactory, registerPlugin< WebViewStep >(); )

WebViewStep::WebViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
{
    emit nextStatusChanged( true );
#ifdef WEBVIEW_WITH_WEBENGINE
    QtWebEngine::initialize();
#endif
    m_view = new WebViewWidget();
#ifdef WEBVIEW_WITH_WEBKIT
    m_view->settings()->setFontFamily( QWebSettings::StandardFont,
                                       m_view->settings()->fontFamily( QWebSettings::SansSerifFont ) );
    m_view->setRenderHints( QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform );
#endif
}


WebViewStep::~WebViewStep()
{
    if ( m_view && m_view->parent() == nullptr )
    {
        m_view->deleteLater();
    }
}


QString
WebViewStep::prettyName() const
{
    return m_prettyName;
}


QWidget*
WebViewStep::widget()
{
    return m_view;
}


bool
WebViewStep::isNextEnabled() const
{
    return true;
}


bool
WebViewStep::isBackEnabled() const
{
    return true;
}


bool
WebViewStep::isAtBeginning() const
{
    return true;
}


bool
WebViewStep::isAtEnd() const
{
    return true;
}

void
WebViewStep::onActivate()
{
    m_view->load( QUrl( m_url ) );
    m_view->show();
}

QList< Calamares::job_ptr >
WebViewStep::jobs() const
{
    return QList< Calamares::job_ptr >();
}


void
WebViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    if ( configurationMap.contains( "url" ) && configurationMap.value( "url" ).type() == QVariant::String )
    {
        m_url = configurationMap.value( "url" ).toString();
    }

    if ( configurationMap.contains( "prettyName" )
         && configurationMap.value( "prettyName" ).type() == QVariant::String )
    {
        m_prettyName = configurationMap.value( "prettyName" ).toString();
    }
}
