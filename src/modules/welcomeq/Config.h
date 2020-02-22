/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
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

#ifndef WELCOMEQ_CONFIG_H
#define WELCOMEQ_CONFIG_H

#include <QObject>
#include <QUrl>

class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QUrl helpUrl READ helpUrl CONSTANT FINAL )
    Q_PROPERTY( QUrl issuesUrl READ issuesUrl CONSTANT FINAL )
    Q_PROPERTY( QUrl notesUrl READ notesUrl CONSTANT FINAL )
    Q_PROPERTY( QUrl donateUrl READ donateUrl CONSTANT FINAL )
public:
    Config();
    virtual ~Config();

    void setHelpUrl( const QUrl& url ) { m_helpUrl = url; }
    void setIssuesUrl( const QUrl& url ) { m_issuesUrl = url; }
    void setNotesUrl( const QUrl& url ) { m_notesUrl = url; }
    void setDonateUrl( const QUrl& url ) { m_donateUrl = url; }

public slots:
    QUrl helpUrl() const { return m_helpUrl; }
    QUrl issuesUrl() const { return m_issuesUrl; }
    QUrl notesUrl() const { return m_notesUrl; }
    QUrl donateUrl() const { return m_donateUrl; }

private:
    QUrl m_helpUrl, m_issuesUrl, m_notesUrl, m_donateUrl;
};

#endif
