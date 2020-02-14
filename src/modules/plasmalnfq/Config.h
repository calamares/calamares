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

#ifndef PLASMALNF_CONFIG_H
#define PLASMALNF_CONFIG_H

#include <QObject>

#include <QList>
#include <QString>
#include <QStringList>
#include <QWidget>
#include <QAbstractListModel>

#include "ThemeInfo.h"

class ThemesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex WRITE setCurrentIndex READ currentIndex NOTIFY currentIndexChanged)
    using QAbstractListModel::QAbstractListModel;

public:

    enum ThemeRoles : uint
    {
      Name,
      Id,
      Description,
      Image
    };

    void setThemes(const ThemeInfoList &themes);

    int rowCount(const QModelIndex& = QModelIndex()) const override
    {
        return m_list.count();
    }

    QVariant data(const QModelIndex& index, int role) const override
    {
        if(!index.isValid())
            return QVariant();
        const auto item = m_list.at(index.row());
        switch(static_cast<ThemeRoles>(role))
        {
            case Name: return item["name"];
            case Id: return item["id"];
            case Image: return item["image"];
            case Description: return item["description"];
            default: return QVariant();
        }
    }

    void setCurrentIndex(const int &index)
    {
        if(index >= m_list.count() || index < 0)
            return;

        m_currentIndex = index;
        emit currentIndexChanged(m_currentIndex);
        emit themeSelected(item(index)["id"]);
    }

    int currentIndex() const
    {
        return m_currentIndex;
    }

    const QMap<QString, QString> item(const int &index) const
    {
        if(index >= m_list.count() || index < 0)
            return QMap<QString, QString>();

        return m_list.at(index);
    }

protected:
    QHash<int, QByteArray> roleNames() const override
    {
        return {{ThemeRoles::Name, "name"}, {ThemeRoles::Id, "id"}, {ThemeRoles::Description, "descriptio"}, {ThemeRoles::Image, "image"}};
    }

private:
    int m_currentIndex =-1;
    QVector<QMap<QString, QString>> m_list;

signals:
    void currentIndexChanged(int index);
    void themeSelected(QString id);
};


class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ThemesModel * themesModel READ themesModel CONSTANT FINAL)
    Q_PROPERTY(QString prettyStatus READ prettyStatus NOTIFY prettyStatusChanged FINAL)

public:
    Config( QObject* parent = nullptr );

        void setLnfPath( const QString& path );
    /** @brief enable only the listed themes.
     *
     * Shows the listed @p themes with full information (e.g. screenshot).
     * If @p showAll is true, then also show all installed themes
     * not explicitly listed (without a screenshot).
     */
    void setEnabledThemes( const ThemeInfoList& themes, bool showAll );
    /** @brief enable all installed plasma themes. */
    void setEnabledThemesAll();
    /** @brief set which theme is to be preselected. */
    void setPreselect( const QString& id );

    QString prettyStatus() const
    {
        return m_prettyStatus;
    }

    ThemesModel * themesModel() const
    {
        return m_themesModel;
    }

signals:
    void plasmaThemeSelected( const QString& id );
    void prettyStatusChanged();

private:
    /** @brief Intersect the list of enabled themes with the installed ones. */
    void winnowThemes();
    /** @brief Get the translated names for all enabled themes. */
    void updateThemeNames();

    QString m_lnfPath;
    QString m_preselect;
    QString m_prettyStatus;
    bool m_showAll;  // If true, don't winnow according to enabledThemes
    ThemeInfoList m_enabledThemes;
    ThemesModel *m_themesModel;
};

#endif
