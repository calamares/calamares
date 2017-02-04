/*
 *   Copyright 2016, Luca Giambonini <almack@chakraos.org>
 *   Copyright 2016, Lisa Vitolo     <shainer@chakraos.org>
 *   Copyright 2017, Kyle Robbertze  <krobbertze@gmail.com>
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
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/YamlUtils.h"

#include <QFile>
#include <QMap>
#include <QTextStream>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QHeaderView>
#include <QtDebug>
#include <QtGlobal>
#include <QWidget>
#include <QSignalMapper>

#include <yaml-cpp/yaml.h>

using CalamaresUtils::yamlToVariant;

NetInstallPage::NetInstallPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::Page_NetInst )
    , m_networkManager( this )
{
    ui->setupUi( this );
}

bool
NetInstallPage::isReady()
{
    // nothing to wait for, the data are immediately ready
    // if the user does not select any group nothing is installed
    return true;
}

void NetInstallPage::readGroups( const QByteArray& yamlData )
{
    YAML::Node groups = YAML::Load( yamlData.constData() );
    Q_ASSERT( groups.IsSequence() );
    m_groups = new PackageModel( groups );
    CALAMARES_RETRANSLATE(
        m_groups->setHeaderData( 0, Qt::Horizontal, tr( "Name" ) );
        m_groups->setHeaderData( 0, Qt::Horizontal, tr( "Description" ) ); )
}

void
NetInstallPage::dataIsHere( QNetworkReply* reply )
{
    if ( reply->error() != QNetworkReply::NoError )
    {
        cDebug() << reply->errorString();
        ui->netinst_status->setText( tr( "Network Installation. (Disabled: Unable to fetch package lists, check your network connection)" ) );
        return;
    }

    readGroups( reply->readAll() );

    ui->groupswidget->setModel( m_groups );
    ui->groupswidget->header()->setSectionResizeMode( 0, QHeaderView::ResizeToContents );
    ui->groupswidget->header()->setSectionResizeMode( 1, QHeaderView::Stretch );

    reply->deleteLater();
    emit checkReady( isReady() );
}

QList<PackageTreeItem::ItemData> NetInstallPage::selectedPackages() const
{
    return m_groups->getPackages();
}

void NetInstallPage::loadGroupList()
{
    QString confUrl(
        Calamares::JobQueue::instance()->globalStorage()->value(
            "groupsUrl" ).toString() );

    QNetworkRequest request;
    request.setUrl( QUrl( confUrl ) );
    // Follows all redirects except unsafe ones (https to http).
    request.setAttribute( QNetworkRequest::FollowRedirectsAttribute, true );
    // Not everybody likes the default User Agent used by this class (looking at you,
    // sourceforge.net), so let's set a more descriptive one.
    request.setRawHeader( "User-Agent", "Mozilla/5.0 (compatible; Calamares)" );

    connect( &m_networkManager, &QNetworkAccessManager::finished,
             this, &NetInstallPage::dataIsHere );
    m_networkManager.get( request );
}

void NetInstallPage::onActivate()
{
    ui->groupswidget->setFocus();
}
