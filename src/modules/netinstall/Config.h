/*
 *   Copyright 2016, Luca Giambonini <almack@chakraos.org>
 *   Copyright 2016, Lisa Vitolo     <shainer@chakraos.org>
 *   Copyright 2017, Kyle Robbertze  <krobbertze@gmail.com>
 *   Copyright 2017-2018, 2020, Adriaan de Groot <groot@kde.org>
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

#ifndef NETINSTALL_CONFIG_H
#define NETINSTALL_CONFIG_H

#include "PackageModel.h"

#include <QObject>
#include <QUrl>

class QNetworkReply;

class Config : public QObject
{
    Q_OBJECT

    Q_PROPERTY( PackageModel* packageModel MEMBER m_model FINAL )
    Q_PROPERTY( QString status READ status NOTIFY statusChanged FINAL )

public:
    Config( QObject* parent = nullptr );
    virtual ~Config();

    enum class Status
    {
        Ok,
        FailedBadConfiguration,
        FailedInternalError,
        FailedNetworkError,
        FailedBadData
    };

    QString status() const;
    void setStatus( Status s );

    bool required() const { return m_required; }
    void setRequired( bool r ) { m_required = r; }

    /** @brief Retrieves the groups, with name, description and packages
     *
     * Loads data from the given URL. Once done, the data is parsed
     * and passed on to the other loadGroupList() method.
     */
    void loadGroupList( const QUrl& url );

    /** @brief Fill model from parsed data.
     *
     * Fills the model with a list of groups -- which can contain
     * subgroups and packages -- from @p groupData.
     */
    void loadGroupList( const QVariantList& groupData );

    PackageModel* model() const { return m_model; }

signals:
    void statusChanged( QString status );  ///< Something changed
    void statusReady();  ///< Loading groups is complete

private slots:
    void receivedGroupData();  ///< From async-loading group data

private:
    PackageModel* m_model = nullptr;
    QNetworkReply* m_reply = nullptr;  // For fetching data
    Status m_status = Status::Ok;
    bool m_required = false;
};

#endif
