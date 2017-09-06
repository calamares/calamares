/*
 *   Copyright 2016, Luca Giambonini <almack@chakraos.org>
 *   Copyright 2016, Lisa Vitolo     <shainer@chakraos.org>
 *   Copyright 2017, Kyle Robbertze  <krobbertze@gmail.com>
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
    , m_groups( nullptr )
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

bool
NetInstallPage::readGroups( const QByteArray& yamlData )
{
    try
    {
        YAML::Node groups = YAML::Load( yamlData.constData() );

        if ( !groups.IsSequence() )
            cDebug() << "WARNING: netinstall groups data does not form a sequence.";
        Q_ASSERT( groups.IsSequence() );
        m_groups = new PackageModel( groups );
        CALAMARES_RETRANSLATE(
            m_groups->setHeaderData( 0, Qt::Horizontal, tr( "Name" ) );
            m_groups->setHeaderData( 0, Qt::Horizontal, tr( "Description" ) ); )
        return true;

    }
    catch ( YAML::Exception& e )
    {
        cDebug() << "WARNING: YAML error " << e.what() << "in netinstall groups data.";
        if ( ( e.mark.line >= 0 ) && ( e.mark.column >= 0 ) )
        {
            // Try to show the line where it happened.
            int linestart = 0;
            for ( int linecount = 0; linecount < e.mark.line; ++linecount )
            {
                linestart = yamlData.indexOf( '\n', linestart );
                // No more \ns found, weird
                if ( linestart < 0 )
                    break;
                linestart += 1;  // Skip that \n
            }
            int lineend = linestart;
            if ( linestart >= 0 )
            {
                lineend = yamlData.indexOf( '\n', linestart );
                if ( lineend < 0 )
                    lineend = yamlData.length();
            }

            int rangestart = linestart;
            int rangeend = lineend;
            // Adjust range (linestart..lineend) so it's not too long
            if ( ( linestart >= 0 ) && ( e.mark.column > 30 ) )
                rangestart += ( e.mark.column - 30 );
            if ( ( linestart >= 0 ) && ( rangeend - rangestart > 40 ) )
                rangeend = rangestart + 40;

            if ( linestart >= 0 )
                cDebug() << "WARNING: offending YAML data:" << yamlData.mid( rangestart, rangeend-rangestart ).constData();
        }
        return false;
    }
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

    if ( !readGroups( reply->readAll() ) )
    {
        cDebug() << "Netinstall groups data was received, but invalid.";
        ui->netinst_status->setText( tr( "Network Installation. (Disabled: Unable to fetch package lists, check your network connection)" ) );
        reply->deleteLater();
        return;
    }

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
