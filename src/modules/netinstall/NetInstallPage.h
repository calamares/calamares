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

#ifndef NETINSTALLPAGE_H
#define NETINSTALLPAGE_H

#include "Typedefs.h"
#include <QWidget>
#include <QAbstractButton>
#include <QNetworkAccessManager>

// required forward declarations
class QByteArray;
class QNetworkReply;
class GroupSelectionWidget;

namespace Ui
{
class Page_NetInst;
}

// Representation of a package group.
struct Group
{
    Group()
        : Group( "","",false, false, false ) { }
    Group( QString name, QString description, bool selected, bool hidden, bool critical )
        : name( name ), description( description ), selected( selected ), hidden( hidden ), critical( critical ) { }
    Group( QString name, QString description )
        : Group( name, description, false, false, false ) { }

    QString name;
    QString description;
    QStringList packages;

    // See README.md for a description of these fields.
    bool selected = false;
    bool hidden = false;
    bool critical = false;
};

class NetInstallPage : public QWidget
{
    Q_OBJECT

public:
    NetInstallPage( QWidget* parent = nullptr );

    void onActivate();

    bool isReady();

    // Retrieves the groups, with name, description and packages, from
    // the remote URL configured in the settings. Assumes the URL is already
    // in the global storage. This should be called before displaying the page.
    void loadGroupList();

    // Return a list of groups currently selected. No data is cached here, so
    // this function does not run in constant time.
    QList<Group> selectedGroups() const;

public slots:
    void dataIsHere( QNetworkReply* );

signals:
    void checkReady( bool );

private:
    // Takes the YAML data representing the groups and reads them into the
    // m_groups and m_groupOrder internal structures. See the README.md
    // of this module to know the format expected of the YAML files.
    void readGroups( const QByteArray& yamlData );

    Ui::Page_NetInst* ui;

    // Handles connection with the remote URL storing the configuration.
    QNetworkAccessManager m_networkManager;

    QHash<QString, Group> m_groups;
    // For each group name, store the selection widget to retrieve UI
    // properties.
    QHash<QString, GroupSelectionWidget*> m_groupWidgets;
    QList<QString> m_groupOrder;
};

#endif // NETINSTALLPAGE_H
