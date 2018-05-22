/*
 *   Copyright 2016, Luca Giambonini <almack@chakraos.org>
 *   Copyright 2016, Lisa Vitolo     <shainer@chakraos.org>
 *   Copyright 2017, Kyle Robbertze  <krobbertze@gmail.com>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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


const char* NetInstallPage::HEADER_TEXT = "<h1>Package Selection</h1>";


NetInstallPage::NetInstallPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::Page_NetInst )
    , m_networkManager( this )
    , m_groups( nullptr )
{
    ui->setupUi( this );
    ui->header->setText( tr( HEADER_TEXT ) );
}

bool
NetInstallPage::readGroups( const QByteArray& yamlData )
{
    try
    {
        YAML::Node groups = YAML::Load( yamlData.constData() );

        if ( !groups.IsSequence() )
            cWarning() << "netinstall groups data does not form a sequence.";
        Q_ASSERT( groups.IsSequence() );
        m_groups = new PackageModel( groups );
        CALAMARES_RETRANSLATE(
            m_groups->setHeaderData( 0, Qt::Horizontal, tr( "Name" ) );
            m_groups->setHeaderData( 1, Qt::Horizontal, tr( "Description" ) ); )
        return true;

    }
    catch ( YAML::Exception& e )
    {
        CalamaresUtils::explainYamlException( e, yamlData, "netinstall groups data" );
        return false;
    }
}

void
NetInstallPage::dataIsHere( QNetworkReply* reply )
{
    bool is_valid_package_data = false;

    // If m_required is *false* then we still say we're ready
    // even if the reply is corrupt or missing.
    if ( reply->error() != QNetworkReply::NoError )
    {
        cWarning() << "unable to fetch netinstall package lists.";
        cDebug() << "  ..Netinstall reply error: " << reply->error();
        cDebug() << "  ..Request for url: " << reply->url().toString() << " failed with: " << reply->errorString();
        ui->netinst_status->setText( tr( "Network Installation. (Disabled: Unable to fetch package lists, check your network connection)" ) );
    }
    else
    {
        // Parse received YAML to create the PackageModel
        is_valid_package_data = readGroups( reply->readAll() );

        if ( !is_valid_package_data )
        {
            cWarning() << "netinstall groups data was received, but invalid.";
            cDebug() << "  ..Url:     " <<  reply->url().toString();
            cDebug() << "  ..Headers: " <<  reply->rawHeaderList();
            ui->netinst_status->setText( tr( "Network Installation. (Disabled: Received invalid groups data)" ) );
        }

        reply->deleteLater();
    }

    populateGroupsWidget( is_valid_package_data );
}

void
NetInstallPage::parseGroupList( const QVariantList& package_groups )
{
    // Convert netinstall.conf package groups to YAML
    YAML::Emitter package_groups_yaml;
    package_groups_yaml.SetOutputCharset(YAML::EscapeNonAscii);
    package_groups_yaml << YAML::BeginSeq;
    for ( int groups_n = 0; groups_n < package_groups.length(); ++groups_n )
    {
        QVariantMap package_group = package_groups.value(groups_n).toMap();
        std::string group_name = package_group["name"].toString().toStdString();
        std::string group_desc = package_group["description"].toString().toStdString();
        std::string group_critical = package_group["critical"].toString().toStdString();
        QStringList group_packages = package_group.value( "packages" ).toStringList();
        std::vector< std::string > packages;
        foreach ( const QString& package , group_packages )
            packages.push_back( package.toStdString() );

// TODO: deleteme DEBUG
cDebug() << "NetInstallPage::parseGroupList() package_group[name]=" << QString::fromStdString(group_name);
cDebug() << "NetInstallPage::parseGroupList() package_group[description]=" << QString::fromStdString(group_desc);
cDebug() << "NetInstallPage::parseGroupList() package_group[critical]=" << QString::fromStdString(group_critical);
cDebug() << "NetInstallPage::parseGroupList() package_group[packages]=" << group_packages;

        package_groups_yaml << YAML::BeginMap;
        package_groups_yaml << YAML::Key << "name"        << YAML::Value << group_name;
        package_groups_yaml << YAML::Key << "description" << YAML::Value << group_desc;
        package_groups_yaml << YAML::Key << "critical"    << YAML::Value << group_critical;
        package_groups_yaml << YAML::Key << "packages"    << YAML::Value << packages;
        package_groups_yaml << YAML::EndMap;
    }
    package_groups_yaml << YAML::EndSeq;

// TODO: deleteme DEBUG
// DBG << "NetInstallPage::parseGroupList() err=" << QString(package_groups_yaml.GetLastError());

    // Parse generated YAML to create the PackageModel
    bool is_valid_package_data = readGroups( QByteArray( package_groups_yaml.c_str() ) );

    if ( !is_valid_package_data )
        ui->netinst_status->setText( tr( "Package Selection. (Disabled: Invalid groups data)" ) );

    populateGroupsWidget( is_valid_package_data );
}

void
NetInstallPage::populateGroupsWidget( bool is_valid_package_data )
{
    if ( is_valid_package_data )
    {
        ui->groupswidget->setModel( m_groups );
        ui->groupswidget->header()->setSectionResizeMode( 0, QHeaderView::ResizeToContents );
        ui->groupswidget->header()->setSectionResizeMode( 1, QHeaderView::Stretch );
    }

    emit checkReady( is_valid_package_data || !m_required );
}

PackageModel::PackageItemDataList
NetInstallPage::selectedPackages() const
{
    if ( m_groups )
        return m_groups->getPackages();
    else
    {
        cWarning() << "no netinstall groups are available.";
        return PackageModel::PackageItemDataList();
    }
}

void
NetInstallPage::loadGroupList( const QString& confUrl )
{
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
