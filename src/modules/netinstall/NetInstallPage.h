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

// required forward declarations
class KJob;
class QByteArray;
class GroupSelectionWidget;

namespace Ui
{
class Page_NetInst;
}

class NetInstallPage : public QWidget
{
    Q_OBJECT

    // Internal representation of a package group.
    struct Group
    {
        Group()
            : Group( "","",false, false ) { }
        Group( QString name, QString description, bool selected, bool hidden )
            : name( name ), description( description ), selected( selected ), hidden( hidden ) { }
        Group( QString name, QString description )
            : Group( name, description, false, false ) { }

        QString name;
        QString description;
        QStringList packages;

        // See README.md for a description of these two fields.
        bool selected = false;
        bool hidden = false;
    };

public:
    NetInstallPage( QWidget* parent = nullptr );
    void onActivate();

    bool isReady();

    // Retrieves the groups, with name, description and packages, from
    // the remote URL configured in the settings. Assumes the URL is already
    // in the global storage. This should be called before displaying the page.
    void loadGroupList();

    // Returns the list of packages belonging to groups that are
    // selected in the view in this given moment. No data is cached here, so
    // this function does not have constant time.
    QStringList selectedPackages() const;

public slots:
    void dataIsHere( KJob* );

signals:
    void checkReady( bool );

private:
    // Takes the YAML data representing the groups and reads them into the
    // m_groups and m_groupOrder internal structures. See the README.md
    // of this module to know the format expected of the YAML files.
    void ReadGroups( const QByteArray& yamlData );

    Ui::Page_NetInst* ui;

    QHash<QString, Group> m_groups;
    // For each group name, store the selection widget to retrieve UI
    // properties.
    QHash<QString, GroupSelectionWidget*> m_groupWidgets;
    QList<QString> m_groupOrder;
};

#endif // NETINSTALLPAGE_H
