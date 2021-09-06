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

#ifndef NETINSTALL_LOADERQUEUE_H
#define NETINSTALL_LOADERQUEUE_H

#include <QQueue>
#include <QUrl>
#include <QVariantList>

class Config;
class QNetworkReply;

/** @brief Data about an entry in *groupsUrl*
 *
 * This can be a specific URL, or "local" which uses data stored
 * in the configuration file itself.
 */
struct SourceItem
{
    QUrl url;
    QVariantList data;

    bool isUrl() const { return url.isValid(); }
    bool isLocal() const { return !data.isEmpty(); }
    bool isValid() const { return isUrl() || isLocal(); }
    /** @brief Create a SourceItem
     *
     * If the @p groupsUrl is @c "local" then the *groups* key in
     * the @p configurationMap is used as the source; otherwise the
     * string is used as an actual URL.
     */
    static SourceItem makeSourceItem( const QString& groupsUrl, const QVariantMap& configurationMap );
};

/** @brief Queue of source items to load
 *
 * Queue things up by calling append() and then kick things off
 * by calling load(). This will try to load the items, in order;
 * the first one that succeeds will end the loading process.
 *
 * Signal done() is emitted when done (also when all of the items fail).
 */
class LoaderQueue : public QObject
{
    Q_OBJECT
public:
    LoaderQueue( Config* parent );

    void append( SourceItem&& i );
    int count() const { return m_queue.count(); }

public Q_SLOTS:
    void load();

    void fetchNext();
    void fetch( const QUrl& url );
    void dataArrived();

Q_SIGNALS:
    void done();

private:
    QQueue< SourceItem > m_queue;
    Config* m_config = nullptr;
    QNetworkReply* m_reply = nullptr;
};

#endif
