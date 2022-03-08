/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PACKAGEMODEL_H
#define PACKAGEMODEL_H

#include "locale/TranslatableConfiguration.h"
#include "utils/NamedEnum.h"

#include <QAbstractListModel>
#include <QObject>
#include <QPixmap>
#include <QVector>


struct PackageItem
{
    QString id;
    CalamaresUtils::Locale::TranslatedString name;
    CalamaresUtils::Locale::TranslatedString description;
    QPixmap screenshot;
    QStringList packageNames;
    QVariantMap netinstallData;

    /// @brief Create blank PackageItem
    PackageItem();
    /** @brief Creates a PackageItem from given strings
     *
     * This constructor sets all the text members,
     * but leaves the screenshot blank. Set that separately.
     */
    PackageItem( const QString& id, const QString& name, const QString& description );

    /** @brief Creates a PackageItem from given strings.
     *
     * Set all the text members and load the screenshot from the given
     * @p screenshotPath, which may be a QRC path (:/path/in/qrc) or
     * a filesystem path, whatever QPixmap understands.
     */
    PackageItem( const QString& id, const QString& name, const QString& description, const QString& screenshotPath );

    /** @brief Creates a PackageItem from a QVariantMap
     *
     * This is intended for use when loading PackageItems from a
     * configuration map. It will look up the various keys in the map
     * and handle translation strings as well.
     *
     * The following keys are used:
     *  - *id*: the identifier for this item; if it is the empty string
     *    then this is the special "no-package".
     *  - *name* (and *name[lang]*): for the name and its translations
     *  - *description* (and *description[lang]*)
     *  - *screenshot*: a path to a screenshot for this package
     *  - *packages*: a list of package names
     */
    PackageItem( const QVariantMap& map );

    /** @brief Is this item valid?
     *
     * A valid item has an untranslated name available.
     */
    bool isValid() const { return !name.isEmpty(); }

    /** @brief Is this a (the) No-Package package?
     *
     * There should be at most one No-Package item in a collection
     * of PackageItems. That one will be used to describe a
     * "no package" situation.
     */
    bool isNonePackage() const { return id.isEmpty(); }
};

using PackageList = QVector< PackageItem >;

class PackageListModel : public QAbstractListModel
{
public:
    PackageListModel( PackageList&& items, QObject* parent );
    PackageListModel( QObject* parent );
    ~PackageListModel() override;

    /** @brief Add a package @p to the model
     *
     * Only valid packages are added -- that is, they must have a name.
     */
    void addPackage( PackageItem&& p );

    int rowCount( const QModelIndex& index ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    /// @brief Direct (non-abstract) access to package data
    const PackageItem& packageData( int r ) const { return m_packages[ r ]; }
    /// @brief Direct (non-abstract) count of package data
    int packageCount() const { return m_packages.count(); }

    /** @brief Does a name lookup (based on id) and returns the packages member
     *
     * If there is a package with the given @p id, returns its packages
     * (e.g. the names of underlying packages to install for it); returns
     * an empty list if the id is not found.
     */
    QStringList getInstallPackagesForName( const QString& id ) const;
    /** @brief Name-lookup all the @p ids and returns the packages members
     *
     * Concatenates installPackagesForName() for each id in @p ids.
     */
    QStringList getInstallPackagesForNames( const QStringList& ids ) const;

    /** @brief Does a name lookup (based on id) and returns the netinstall data
     *
     * If there is a package with an id in @p ids, returns their netinstall data
     *
     * returns a list of netinstall data or an emply list if none is found
     */
    QVariantList getNetinstallDataForNames( const QStringList& ids ) const;

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
