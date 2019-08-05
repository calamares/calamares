/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#ifndef PACKAGEMODEL_H
#define PACKAGEMODEL_H

#include "locale/TranslatableConfiguration.h"
#include "utils/NamedEnum.h"

#include <QAbstractListModel>
#include <QObject>
#include <QPixmap>
#include <QVector>

enum class PackageChooserMode
{
    Optional,  // zero or one
    Required,  // exactly one
    OptionalMultiple,  // zero or more
    RequiredMultiple  // one or more
};

const NamedEnumTable< PackageChooserMode >& roleNames();

struct PackageItem
{
    QString id;
    // TODO: may need more than one
    QString package;
    CalamaresUtils::Locale::TranslatedString name;
    CalamaresUtils::Locale::TranslatedString description;
    // TODO: may be more than one
    QPixmap screenshot;

    /// @brief Create blank PackageItem
    PackageItem();
    /** @brief Creates a PackageItem from given strings
     *
     * This constructor sets all the text members,
     * but leaves the screenshot blank. Set that separately.
     */
    PackageItem( const QString& id, const QString& package, const QString& name, const QString& description );

    PackageItem( const QString& id,
                 const QString& package,
                 const QString& name,
                 const QString& description,
                 const QString& screenshotPath );

    // TODO: implement this
    PackageItem fromAppStream( const QString& filename );
};

using PackageList = QVector< PackageItem >;

class PackageListModel : public QAbstractListModel
{
public:
    PackageListModel( PackageList&& items, QObject* parent );
    PackageListModel( QObject* parent );
    virtual ~PackageListModel() override;

    void addPackage( PackageItem&& p );

    int rowCount( const QModelIndex& index ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    enum Roles : int
    {
        NameRole = Qt::DisplayRole,
        DescriptionRole = Qt::UserRole,
        ScreenshotRole,
        IdRole
    };

private:
    PackageList m_packages;
};

#endif
