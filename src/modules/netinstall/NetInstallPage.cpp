/*
 *   Copyright 2016, Luca Giambonini <almack@chakraos.org>
 *   Copyright 2016, Lisa Vitolo     <shainer@chakraos.org>
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

#include "widgets/groupselectionwidget.h"
#include "ui_page_netinst.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/YamlUtils.h"

#include <QFile>
#include <QMap>
#include <QTextStream>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

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

    for ( YAML::const_iterator it = groups.begin(); it != groups.end(); ++it )
    {
        const YAML::Node groupDefinition = *it;

        QString name( tr( yamlToVariant(groupDefinition["name"]).toByteArray() ) );
        QString description( tr( yamlToVariant(groupDefinition["description"]).toByteArray() ) );
        QStringList packages;

        for ( YAML::const_iterator it = groupDefinition["packages"].begin();
                it != groupDefinition["packages"].end(); ++it )
            packages.append( yamlToVariant(*it).toString() );

        m_groups[name].name = name;
        m_groups[name].description = description;
        m_groups[name].packages = packages;

        if ( groupDefinition["selected"] )
            m_groups[name].selected = yamlToVariant( groupDefinition["selected"] ).toBool();

        if ( groupDefinition["hidden"] )
            m_groups[name].hidden = yamlToVariant( groupDefinition["hidden"] ).toBool();

        m_groupOrder.append( name );
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

    readGroups( reply->readAll() );

    QSignalMapper* mapper = new QSignalMapper( this );
    foreach ( const QString& groupKey, m_groupOrder )
    {
        Group group = m_groups[groupKey];
        if ( group.hidden )
        {
            // Do not present on view.
            continue;
        }

        GroupSelectionWidget* groupWidget = new GroupSelectionWidget( group.name, group.description, group.packages, this );
        m_groupWidgets.insert( groupKey, groupWidget );
        ui->groupswidget->layout()->addWidget( groupWidget );

        mapper->setMapping( groupWidget, groupKey );
        connect( groupWidget, &GroupSelectionWidget::toggled, mapper,
                 static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map) );
    }

    reply->deleteLater();
    emit checkReady( isReady() );
}

QStringList NetInstallPage::selectedPackages() const
{
    QStringList selectedPackages;

    // Add all the packages for groups that are toggled in the view.
    for ( auto it = m_groupWidgets.constBegin(); it != m_groupWidgets.constEnd(); it++ )
    {
        if ( it.value()->isToggled() )
            selectedPackages += m_groups[it.key()].packages;
    }

    // Add all the packages for groups that are hidden but selected.
    for ( const Group& group : m_groups.values() )
    {
        if ( group.hidden && group.selected )
            selectedPackages += group.packages;
    }

    return selectedPackages;
}

void NetInstallPage::loadGroupList()
{
    QString confUrl(
        Calamares::JobQueue::instance()->globalStorage()->value(
            "groupsUrl" ).toString() );

    QNetworkRequest request;
    request.setUrl( QUrl( confUrl ) );
    // Follows all redirects except unsafe ones (https to http).
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    // Not everybody likes the default User Agent used by this class (looking at you,
    // sourceforge.net), so let's set a more descriptive one.
    request.setRawHeader( "User-Agent", "Mozilla/5.0 (compatible; Calamares)" );

    connect(&m_networkManager, &QNetworkAccessManager::finished,
            this, &NetInstallPage::dataIsHere);
    m_networkManager.get(request);
}

void NetInstallPage::onActivate()
{
    ui->groupswidget->setFocus();
}
