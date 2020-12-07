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

class ThemeInfoList;

class ThemesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum
    {
        LabelRole = Qt::DisplayRole,
        KeyRole = Qt::UserRole,
        ShownRole,  // Should theme be displayed
        SelectedRole,  // Is theme selected
        DescriptionRole,
        ImageRole
    };

    explicit ThemesModel( QObject* parent );

    int rowCount( const QModelIndex& = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    QHash< int, QByteArray > roleNames() const override;

    /// @brief Set the screenshot to go with the given @p id
    void setThemeImage( const QString& id, const QString& imagePath );

    /// @brief Call setThemeImage( key, value ) for all keys in @p images
    void setThemeImage( const QMap< QString, QString >& images );

    /// @brief Set whether to show the given theme @p id (or not)
    void showTheme( const QString& id, bool show = true );

    /// @brief Shows the keys in the @p onlyThese map, and hides the rest
    void showOnlyThemes( const QMap< QString, QString >& onlyThese );

    /** @brief Mark the @p themeId as current / selected
     *
     * One theme can be selected at a time; this will emit data
     * changed signals for any (one) theme already selected, and
     * the newly-selected theme. If @p themeId does not name any
     * theme, none are selected.
     */
    void select( const QString& themeId );

    /** @brief The size of theme Images
     *
     * The size is dependent on the font size used by Calamares,
     * and is constant within one run of Calamares, but may change
     * if the font settings do between runs.
     */
    static QSize imageSize();

private:
    ThemeInfoList* m_themes;
};


#endif
