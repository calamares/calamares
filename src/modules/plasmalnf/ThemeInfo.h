/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PLASMALNF_THEMEINFO_H
#define PLASMALNF_THEMEINFO_H

#include <QAbstractListModel>
#include <QList>
#include <QString>

class KPluginMetaData;

/** @brief describes a single plasma LnF theme.
 *
 * A theme description has an id, which is really the name of the desktop
 * file (e.g. org.kde.breeze.desktop), a name which is human-readable and
 * translated, and an optional image Page, which points to a local screenshot
 * of that theme.
 */
struct ThemeInfo
{
    QString id;
    QString name;
    QString description;
    QString imagePath;
    bool show = true;

    ThemeInfo() {}

    explicit ThemeInfo( const QString& _id )
        : id( _id )
    {
    }

    explicit ThemeInfo( const QString& _id, const QString& image )
        : id( _id )
        , imagePath( image )
    {
    }

    explicit ThemeInfo( const KPluginMetaData& );

    bool isValid() const { return !id.isEmpty(); }
};

class ThemeInfoList : public QList< ThemeInfo >
{
public:
    std::pair< int, const ThemeInfo* > indexById( const QString& id ) const
    {
        int index = 0;
        for ( const ThemeInfo& i : *this )
        {
            if ( i.id == id )
            {
                return { index, &i };
            }
        }
        return { -1, nullptr };
    }

    std::pair< int, ThemeInfo* > indexById( const QString& id )
    {
        // Call the const version and then munge the types
        auto [ i, p ] = const_cast< const ThemeInfoList* >( this )->indexById( id );
        return { i, const_cast< ThemeInfo* >( p ) };
    }


    /** @brief Looks for a given @p id in the list of themes, returns nullptr if not found. */
    ThemeInfo* findById( const QString& id )
    {
        auto [ i, p ] = indexById( id );
        return p;
    }

    /** @brief Looks for a given @p id in the list of themes, returns nullptr if not found. */
    const ThemeInfo* findById( const QString& id ) const
    {
        auto [ i, p ] = indexById( id );
        return p;
    }

    /** @brief Checks if a given @p id is in the list of themes. */
    bool contains( const QString& id ) const { return findById( id ) != nullptr; }
};

class ThemesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum
    {
        LabelRole = Qt::DisplayRole,
        KeyRole = Qt::UserRole,
        ShownRole,
        ImageRole
    };

    explicit ThemesModel( QObject* parent );

    int rowCount( const QModelIndex& = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    QHash< int, QByteArray > roleNames() const override;

    const ThemeInfo* findById( const QString& id ) const { return m_themes.findById( id ); }

    /// @brief Set the screenshot to go with the given @p id
    void setThemeImage( const QString& id, const QString& imagePath );

    /// @brief Call setThemeImage( key, value ) for all keys in @p images
    void setThemeImage( const QMap< QString, QString >& images );

    /// @brief Set whether to show the given theme @p id (or not)
    void showTheme( const QString& id, bool show = true );

    /// @brief Shows the keys in the @p onlyThese map, and hides the rest
    void showOnlyThemes( const QMap< QString, QString >& onlyThese );

private:
    ThemeInfoList m_themes;
};


#endif
