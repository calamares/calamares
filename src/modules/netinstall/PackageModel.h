/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Kyle Robbertze <kyle@aims.ac.za>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PACKAGEMODEL_H
#define PACKAGEMODEL_H

#include "PackageTreeItem.h"

#include <QObject>
#include <QAbstractItemModel>
#include <QString>

namespace YAML
{
class Node;
}  // namespace YAML

class PackageModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    // Names for columns (unused in the code)
    static constexpr const int NameColumn = 0;
    static constexpr const int DescriptionColumn = 1;

    /* The only interesting roles are DisplayRole (with text depending
     * on the column, and MetaExpandRole which tells if an index
     * should be initially expanded.
     */
    static constexpr const int MetaExpandRole = Qt::UserRole + 1;

    explicit PackageModel( QObject* parent = nullptr );
    ~PackageModel() override;

    void setupModelData( const QVariantList& l );

    bool isSharedState() { return m_shareState; }
    void setSharedState(bool s) { m_shareState = s; }

    QVariant data( const QModelIndex& index, int role ) const override;
    bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole ) override;
    Qt::ItemFlags flags( const QModelIndex& index ) const override;

    QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const override;
    QModelIndex parent( const QModelIndex& index ) const override;

    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;
    int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
    int columnCount( const QModelIndex& parent = QModelIndex() ) const override;

    /** @brief Sets the checked flag on matching groups in the tree
     *
     * Recursively traverses the tree pointed to by m_rootItem and
     * checks if a group name matches any of the items in @p selectNames.
     * If a match is found, set check the box for that group and it's children.
     *
     * Individual packages will not be matched.
     *
     */
    void setGroupSelections( const QStringList& selectNames );

    /** @brief Applies states @p selectStates to package names @p selectNames
    *
    * Sets states according to @p stateHashMap for all copies of package names
    * and selection states in each item of the hash-map
    *
    * Note: This function's behaviour is copy-aware
    */
    void applyStateToCopies( QHash<QString,Qt::CheckState>& stateHashMap );


    /** @brief Applies state @p selectState to package name @p selectName
    *
    * Sets state to @p selectState for all copies of "packageName"
    * @p selectName throughout the netinstall tree 
    *
    * Note: This function's behaviour is copy-aware
    */
    void applyStateToCopies( QString& selectName, Qt::CheckState& selectState );

    void applyInitialStateToCopies();

    /** @brief Obtain the selection states of packages
    *
    * Obtains the selection states of packages and stores them in the
    * hash-map @p stateHashMap with package names as keys and selection states as
    * values. Each package only appears once in the hash-map and the output eagerly
    * takes on a Qt::CheckState::Checked status if it is encountered for any 
    * of the package copies 
    *
    * Note: This function's behaviour is copy-aware 
    */
    void fetchDeduplicatedPackageStates( QHash<QString, Qt::CheckState>& stateHashMap );

    /** @brief Obtain the selection states of packages
    *
    * Obtain the selection states of packages and makes a cumulative
    * list of names in @p packageNames and selection states in @p packageStates
    * Note: This funtion's behaviour is copy-aware 
    */
    void fetchPackageStates( QList<QPair<PackageTreeItem*,Qt::CheckState>>& stateMap );    

    void resetToDefaults();

    PackageTreeItem::List getPackages() const;
    PackageTreeItem::List getItemPackages( PackageTreeItem* item ) const;

    /** @brief Appends groups to the tree
     *
     * Uses the data from @p groupList to add elements to the
     * existing tree that m_rootItem points to.  If m_rootItem
     * is not valid, it does nothing
     *
     * Before adding anything to the model, it ensures that there
     * is no existing data from the same source.  If there is, that
     * data is pruned first
     *
     */
    void appendModelData( const QVariantList& groupList );

private:
    friend class ItemTests;

    void setupModelData( const QVariantList& l, PackageTreeItem* parent );

    void storeInitialState();

    bool m_shareState = false;

    PackageTreeItem* m_rootItem = nullptr;
    PackageTreeItem::List m_hiddenItems;

    QHash<QString,Qt::CheckState>* m_InitialStateHashMap = nullptr;
    QList<QPair<PackageTreeItem*,Qt::CheckState>>* m_InitialStateMap = nullptr;

    /** @brief Applies state @p selectState to package name @p selectName
    * for items under @p item 
    *
    * Sets state to @p selectState for all copies of "packageName" @p selectName
    * throughout the tree under @p item. 
    * Note: This function's behaviour is copy-aware
    */
    void applyStateToCopies( QString& selectName, Qt::CheckState& selectState, PackageTreeItem& item );

    /** @brief Propagates selection state @p selectState over @p item
    *
    * Propagates @p selectState throughout the tree under @p item
    * and all the duplicates of its packages
    */
    void applyStateToGroupAndCopies( Qt::CheckState& selectState, PackageTreeItem& item );

    /** @brief Sets the checked flag on matching groups in the @p item tree
     *
     * Recursively traverses the tree pointed to by @p item and
     * checks if a group name matches any of the items in @p selectNames.
     * If a match is found, set check the box for that group and it's children.
     *
     * Individual packages will not be matched.
     *
     */
    void setGroupSelections( const QStringList& selectNames, PackageTreeItem* item );

    /** @brief Applies states from @p stateHashMap to package names @p selectNames
    * for items under @p item 
    *
    * Sets states according to @p stateHashMap for all copies of packages
    * throughout the tree under @p item. 
    *
    * Note: This function's behaviour is copy-aware
    */
    void applyStateToCopies( QHash<QString, Qt::CheckState>& stateHashMap, PackageTreeItem& item );       
};

#endif  // PACKAGEMODEL_H
