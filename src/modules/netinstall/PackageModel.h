/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Kyle Robbertze <kyle@aims.ac.za>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2022, shivanandvp <shivanandvp@rebornos.org> 
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

    /** @brief Applies selection states from @p stateHashMap to package names
    * @p selectNames and all copies
    *
    * Uses the hash-map @p stateHashMap to modify packages ( whose names are
    * stored as keys ) and all their copies, to the selection states specified
    * as the corresponding values of those keys
    */
    void applyStateToCopies( QHash<QString,Qt::CheckState>& stateHashMap );

    /** @brief Applies state @p selectState to package name @p selectName and 
    * all its copies
    *
    * Sets state to @p selectState for all copies of "packageName"
    * @p selectName throughout the netinstall tree 
    */
    void applyStateToCopies( QString& selectName, Qt::CheckState& selectState );

    /** @brief Propagates selection state @p selectState over @p item
    *
    * Propagates @p selectState throughout the tree under @p item
    * and all the copies of its packages
    */
    void applyStateToGroupAndCopies( Qt::CheckState& selectState, PackageTreeItem& item );

    /** @brief Initializes copies of the initially selected packages
    *
    * Shares the state of the initially selected packages to all their copies
    */
    void applyInitialStateToCopies();

    /** @brief Obtains the selection states of all packages into the output
    * @p stateMap
    *
    * Obtains the selection states of packages and makes a cumulative QList
    * of QPairs of packages and selection states. Copies of packages are treated
    * as separate items with their own selection states 
    */
    void fetchPackageStates( QList<QPair<PackageTreeItem*,Qt::CheckState>>& stateMap );

    /** @brief Obtains the selection states of all package names into 
    * the output @p stateHashMap
    *
    * Obtains the selection states of all package names and stores them in the
    * hash-map @p stateHashMap with package names as keys and selection states
    * as values. Each package only appears once in the hash-map and the output 
    * eagerly takes on a Qt::CheckState::Checked status if it is encountered for
    * any of the package copies 
    */
    void fetchDeduplicatedPackageStates( QHash<QString, Qt::CheckState>& stateHashMap );
   
    /** @brief Reset package selection states to the default values initially
    * recorded
    * 
    * Brings the selection states of packages to those initially recorded. This
    * function is smart - it recognizes and behaves differently according to 
    * the global "share-state" setting and honours local override through 
    * "ignore-share-state"
    */
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

    PackageTreeItem* m_rootItem = nullptr;
    PackageTreeItem::List m_hiddenItems;

    bool m_shareState = false;
    QHash<QString,Qt::CheckState>* m_InitialStateHashMap = nullptr;
    QList<QPair<PackageTreeItem*,Qt::CheckState>>* m_InitialStateMap = nullptr;  

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

    /** @brief Stores the initial selection states of packages smartly
     *
     * Either stores a list of packages and selection states or a hash-map of
     * package names and selection states depending upon the global
     * "share-state" setting
     */
    void storeInitialState();

    /** @brief Recursive helper function for another function with the same 
    * signature excluding @p item
    */
    void applyStateToCopies( QString& selectName, Qt::CheckState& selectState, PackageTreeItem& item );    

    /** @brief Recursive helper function for another function with the same 
    * signature excluding @p item
    */
    void applyStateToCopies( QHash<QString, Qt::CheckState>& stateHashMap, PackageTreeItem& item );       
};

#endif  // PACKAGEMODEL_H
