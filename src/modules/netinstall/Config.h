/*
 *   SPDX-FileCopyrightText: 2016 Luca Giambonini <almack@chakraos.org>
 *   SPDX-FileCopyrightText: 2016 Lisa Vitolo     <shainer@chakraos.org>
 *   SPDX-FileCopyrightText: 2017 Kyle Robbertze  <krobbertze@gmail.com>
 *   SPDX-FileCopyrightText: 2017-2018 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    ~Config() override;

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
