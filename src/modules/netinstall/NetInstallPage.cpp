/*
 *   Copyright 2016, Luca Giambonini <almack@chakraos.org>
 *   Copyright 2016, Lisa Vitolo     <shainer@chakraos.org>
 *   Copyright 2017, Kyle Robbertze  <krobbertze@gmail.com>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2017, Gabriel Craciunescu <crazy@frugalware.org>
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

#include "NetInstallPage.h"

#include "PackageModel.h"
#include "ui_page_netinst.h"

#include "JobQueue.h"

#include "network/Manager.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/Yaml.h"

#include <QHeaderView>
#include <QNetworkReply>

using CalamaresUtils::yamlToVariant;

NetInstallPage::NetInstallPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::Page_NetInst )
    , m_reply( nullptr )
    , m_groups( nullptr )
{
    ui->setupUi( this );
}

bool
NetInstallPage::readGroups( const QByteArray& yamlData )
{
    try
    {
        YAML::Node groups = YAML::Load( yamlData.constData() );

        if ( !groups.IsSequence() )
        {
            cWarning() << "netinstall groups data does not form a sequence.";
        }
        Q_ASSERT( groups.IsSequence() );
        m_groups = new PackageModel( groups );
        CALAMARES_RETRANSLATE( m_groups->setHeaderData( 0, Qt::Horizontal, tr( "Name" ) );
                               m_groups->setHeaderData( 1, Qt::Horizontal, tr( "Description" ) ); )
        return true;
    }
    catch ( YAML::Exception& e )
    {
        CalamaresUtils::explainYamlException( e, yamlData, "netinstall groups data" );
        return false;
    }
}

/// @brief Convenience to zero out and deleteLater on the reply, used in dataIsHere
struct ReplyDeleter
{
    QNetworkReply*& p;

    ~ReplyDeleter()
    {
        if ( p )
        {
            p->deleteLater();
        }
        p = nullptr;
    }
};

void
NetInstallPage::dataIsHere()
{
    if ( !m_reply || !m_reply->isFinished() )
    {
        cWarning() << "NetInstall data called too early.";
        return;
    }

    cDebug() << "NetInstall group data received" << m_reply->url();

    ReplyDeleter d { m_reply };

    // If m_required is *false* then we still say we're ready
    // even if the reply is corrupt or missing.
    if ( m_reply->error() != QNetworkReply::NoError )
    {
        cWarning() << "unable to fetch netinstall package lists.";
        cDebug() << Logger::SubEntry << "Netinstall reply error: " << m_reply->error();
        cDebug() << Logger::SubEntry << "Request for url: " << m_reply->url().toString()
                 << " failed with: " << m_reply->errorString();
        ui->netinst_status->setText(
            tr( "Network Installation. (Disabled: Unable to fetch package lists, check your network connection)" ) );
        emit checkReady( !m_required );
        return;
    }

    if ( !readGroups( m_reply->readAll() ) )
    {
        cWarning() << "netinstall groups data was received, but invalid.";
        cDebug() << Logger::SubEntry << "Url:     " << m_reply->url().toString();
        cDebug() << Logger::SubEntry << "Headers: " << m_reply->rawHeaderList();
        ui->netinst_status->setText( tr( "Network Installation. (Disabled: Received invalid groups data)" ) );
        emit checkReady( !m_required );
        return;
    }

    ui->groupswidget->setModel( m_groups );
    ui->groupswidget->header()->setSectionResizeMode( 0, QHeaderView::ResizeToContents );
    ui->groupswidget->header()->setSectionResizeMode( 1, QHeaderView::Stretch );

    emit checkReady( true );
}

PackageModel::PackageItemDataList
NetInstallPage::selectedPackages() const
{
    if ( m_groups )
    {
        return m_groups->getPackages();
    }
    else
    {
        cWarning() << "no netinstall groups are available.";
        return PackageModel::PackageItemDataList();
    }
}

void
NetInstallPage::loadGroupList( const QString& confUrl )
{
    using namespace CalamaresUtils::Network;

    cDebug() << "NetInstall loading groups from" << confUrl;
    QNetworkReply* reply = Manager::instance().asynchronouseGet(
        QUrl( confUrl ),
        RequestOptions( RequestOptions::FakeUserAgent | RequestOptions::FollowRedirect, std::chrono::seconds( 30 ) ) );

    if ( !reply )
    {
        cDebug() << Logger::Continuation << "request failed immediately.";
        ui->netinst_status->setText( tr( "Network Installation. (Disabled: Incorrect configuration)" ) );
    }
    else
    {
        m_reply = reply;
        connect( reply, &QNetworkReply::finished, this, &NetInstallPage::dataIsHere );
    }
}

void
NetInstallPage::setRequired( bool b )
{
    m_required = b;
}


void
NetInstallPage::onActivate()
{
    ui->groupswidget->setFocus();
}
