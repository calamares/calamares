/*
 *   SPDX-FileCopyrightText: 2016 Luca Giambonini <almack@chakraos.org>
 *   SPDX-FileCopyrightText: 2016 Lisa Vitolo     <shainer@chakraos.org>
 *   SPDX-FileCopyrightText: 2017 Kyle Robbertze  <krobbertze@gmail.com>
 *   SPDX-FileCopyrightText: 2017-2018 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2017 Gabriel Craciunescu <crazy@frugalware.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "network/Manager.h"
#include "utils/Logger.h"
#include "utils/RAII.h"
#include "utils/Yaml.h"

#include <QNetworkReply>

Config::Config( QObject* parent )
    : QObject( parent )
    , m_model( new PackageModel( this ) )
{
}

Config::~Config() {}

QString
Config::status() const
{
    switch ( m_status )
    {
    case Status::Ok:
        return QString();
    case Status::FailedBadConfiguration:
        return tr( "Network Installation. (Disabled: Incorrect configuration)" );
    case Status::FailedBadData:
        return tr( "Network Installation. (Disabled: Received invalid groups data)" );
    case Status::FailedInternalError:
        return tr( "Network Installation. (Disabled: internal error)" );
    case Status::FailedNetworkError:
        return tr( "Network Installation. (Disabled: Unable to fetch package lists, check your network connection)" );
    }
    __builtin_unreachable();
}


void
Config::setStatus( Status s )
{
    m_status = s;
    emit statusChanged( status() );
}

void
Config::loadGroupList( const QVariantList& groupData )
{
    m_model->setupModelData( groupData );
    emit statusReady();
}

void
Config::loadGroupList( const QUrl& url )
{
    if ( !url.isValid() )
    {
        setStatus( Status::FailedBadConfiguration );
    }

    using namespace CalamaresUtils::Network;

    cDebug() << "NetInstall loading groups from" << url;
    QNetworkReply* reply = Manager::instance().asynchronousGet(
        url,
        RequestOptions( RequestOptions::FakeUserAgent | RequestOptions::FollowRedirect, std::chrono::seconds( 30 ) ) );

    if ( !reply )
    {
        cDebug() << Logger::Continuation << "request failed immediately.";
        setStatus( Status::FailedBadConfiguration );
    }
    else
    {
        m_reply = reply;
        connect( reply, &QNetworkReply::finished, this, &Config::receivedGroupData );
    }
}

void
Config::receivedGroupData()
{
    if ( !m_reply || !m_reply->isFinished() )
    {
        cWarning() << "NetInstall data called too early.";
        setStatus( Status::FailedInternalError );
        return;
    }

    cDebug() << "NetInstall group data received" << m_reply->size() << "bytes from" << m_reply->url();

    cqDeleter< QNetworkReply > d { m_reply };

    // If m_required is *false* then we still say we're ready
    // even if the reply is corrupt or missing.
    if ( m_reply->error() != QNetworkReply::NoError )
    {
        cWarning() << "unable to fetch netinstall package lists.";
        cDebug() << Logger::SubEntry << "Netinstall reply error: " << m_reply->error();
        cDebug() << Logger::SubEntry << "Request for url: " << m_reply->url().toString()
                 << " failed with: " << m_reply->errorString();
        setStatus( Status::FailedNetworkError );
        return;
    }

    QByteArray yamlData = m_reply->readAll();
    try
    {
        YAML::Node groups = YAML::Load( yamlData.constData() );

        if ( groups.IsSequence() )
        {
            loadGroupList( CalamaresUtils::yamlSequenceToVariant( groups ) );
        }
        else if ( groups.IsMap() )
        {
            auto map = CalamaresUtils::yamlMapToVariant( groups );
            loadGroupList( map.value( "groups" ).toList() );
        }
        else
        {
            cWarning() << "NetInstall groups data does not form a sequence.";
        }
        if ( m_model->rowCount() < 1 )
        {
            cWarning() << "NetInstall groups data was empty.";
        }
    }
    catch ( YAML::Exception& e )
    {
        CalamaresUtils::explainYamlException( e, yamlData, "netinstall groups data" );
        setStatus( Status::FailedBadData );
    }
}
