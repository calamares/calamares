/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Kyle Robbertze <kyle@aims.ac.za>
 *   SPDX-FileCopyrightText: 2017-2018 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2022, shivanandvp <shivanandvp@rebornos.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include <QObject>

#include "PackageModel.h"

#include "utils/Logger.h"
#include "utils/Variant.h"
#include "utils/Yaml.h"

/** @brief Collects all the "source" values from @p groupList
 *
 * Iterates over @p groupList and returns all nonempty "source"
 * values from the maps.
 *
 */
static QStringList
collectSources( const QVariantList& groupList )
{
    QStringList sources;
    for ( const QVariant& group : groupList )
    {
        QVariantMap groupMap = group.toMap();
        if ( !groupMap[ "source" ].toString().isEmpty() )
        {
            sources.append( groupMap[ "source" ].toString() );
        }
    }

    return sources;
}

PackageModel::PackageModel( QObject* parent )
    : QAbstractItemModel( parent )
{
}

PackageModel::~PackageModel()
{
    delete m_rootItem;
}

QModelIndex
PackageModel::index( int row, int column, const QModelIndex& parent ) const
{
    if ( !m_rootItem || !hasIndex( row, column, parent ) )
    {
        return QModelIndex();
    }

    PackageTreeItem* parentItem;

    if ( !parent.isValid() )
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast< PackageTreeItem* >( parent.internalPointer() );
    }

    PackageTreeItem* childItem = parentItem->child( row );
    if ( childItem )
    {
        return createIndex( row, column, childItem );
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex
PackageModel::parent( const QModelIndex& index ) const
{
    if ( !m_rootItem || !index.isValid() )
    {
        return QModelIndex();
    }

    PackageTreeItem* child = static_cast< PackageTreeItem* >( index.internalPointer() );
    PackageTreeItem* parent = child->parentItem();

    if ( parent == m_rootItem )
    {
        return QModelIndex();
    }
    return createIndex( parent->row(), 0, parent );
}

int
PackageModel::rowCount( const QModelIndex& parent ) const
{
    if ( !m_rootItem || ( parent.column() > 0 ) )
    {
        return 0;
    }

    PackageTreeItem* parentItem;
    if ( !parent.isValid() )
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast< PackageTreeItem* >( parent.internalPointer() );
    }

    return parentItem->childCount();
}

int
PackageModel::columnCount( const QModelIndex& ) const
{
    return 2;
}

QVariant
PackageModel::data( const QModelIndex& index, int role ) const
{
    if ( !m_rootItem || !index.isValid() )
    {
        return QVariant();
    }

    PackageTreeItem* item = static_cast< PackageTreeItem* >( index.internalPointer() );
    switch ( role )
    {
    case Qt::CheckStateRole:
        return index.column() == NameColumn ? ( item->isImmutable() ? QVariant() : item->isSelected() ) : QVariant();
    case Qt::DisplayRole:
        return item->isHidden() ? QVariant() : item->data( index.column() );
    case MetaExpandRole:
        return item->isHidden() ? false : item->expandOnStart();
    default:
        return QVariant();
    }
}

bool
PackageModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    if ( !m_rootItem )
    {
        return false;
    }

    if ( role == Qt::CheckStateRole && index.isValid() )
    {
        PackageTreeItem* item = static_cast< PackageTreeItem* >( index.internalPointer() );
        item->setSelected( static_cast< Qt::CheckState >( value.toInt() ) );

        if ( this->isSharedState() && !item->isIgnoringShareState() )
        {
            Qt::CheckState state = item->isSelected();
            if( !item->isGroup() )
            {
                QString packageName = item->packageName();                
                this->applyStateToCopies( packageName, state );
            } else {
                applyStateToGroupAndCopies( state, *item );
            }
        }

        emit dataChanged( this->index( 0, 0 ),
                          index.sibling( index.column(), index.row() + 1 ),
                          QVector< int >( Qt::CheckStateRole ) );
    }
    return true;
}

Qt::ItemFlags
PackageModel::flags( const QModelIndex& index ) const
{
    if ( !m_rootItem || !index.isValid() )
    {
        return Qt::ItemFlags();
    }
    if ( index.column() == NameColumn )
    {
        PackageTreeItem* item = static_cast< PackageTreeItem* >( index.internalPointer() );
        if ( item->isImmutable() || item->isNoncheckable() )
        {
            return QAbstractItemModel::flags( index );  //Qt::NoItemFlags;
        } 
        // else if ( item->isNoncheckable() )
        // {
        //     return static_cast<Qt::ItemFlags>(~ Qt::ItemIsEnabled & QAbstractItemModel::flags( index ));
        // }
        return Qt::ItemIsUserCheckable | QAbstractItemModel::flags( index );
    }
    return QAbstractItemModel::flags( index );
}

QVariant
PackageModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole )
    {
        return ( section == NameColumn ) ? tr( "Name" ) : tr( "Description" );
    }
    return QVariant();
}

void
PackageModel::setGroupSelections( const QStringList& selectNames )
{
    if ( m_rootItem )
    {
        this->setGroupSelections( selectNames, m_rootItem );
    }
}

void
PackageModel::setGroupSelections( const QStringList& selectNames, PackageTreeItem* item )
{
    for ( int i = 0; i < item->childCount(); i++ )
    {
        auto* child = item->child( i );
        setGroupSelections( selectNames, child );
    }
    if ( item->isGroup() && selectNames.contains( item->name() ) )
    {
        item->setSelected( Qt::CheckState::Checked );
        if ( this->isSharedState() && !item->isIgnoringShareState() ) 
        {
            Qt::CheckState state = Qt::CheckState::Checked;
            this -> applyStateToGroupAndCopies( state, *item );
        }
    }
}

void
PackageModel::fetchDeduplicatedPackageStates( QHash<QString, Qt::CheckState>& stateHashMap )
{
    if ( m_rootItem )
    {
        ::fetchDeduplicatedPackageStates( stateHashMap, *m_rootItem );
    }
}

static void
fetchDeduplicatedPackageStates( QHash<QString, Qt::CheckState>& stateHashMap, PackageTreeItem& item )
{
    if ( !item.isGroup() )
    {
        QString packageName = item.packageName();
        Qt::CheckState packageState = item.isSelected();
        if ( 
            !packageName.isEmpty() 
            && (
                !stateHashMap.contains( packageName )
                || packageState == Qt::CheckState::Checked 
            ) 
        ){
            stateHashMap.insert( packageName, packageState );
        }
    }
    else
    {
        for ( int i = 0; i < item.childCount(); i++ )
        {
            auto* child = item.child( i );
            fetchDeduplicatedPackageStates( stateHashMap, *child );
        }
    }
}

void
PackageModel::fetchPackageStates( QList<QPair<PackageTreeItem*,Qt::CheckState>>& stateMap )
{
    if ( m_rootItem )
    {
        ::fetchPackageStates( stateMap, m_rootItem );
    }
}

static void
fetchPackageStates( QList<QPair<PackageTreeItem*,Qt::CheckState>>& stateMap, PackageTreeItem* item )
{
    if ( !item->isGroup() )
    {
        QString packageName = item->packageName();
        Qt::CheckState packageState = item->isSelected();
        if ( !packageName.isEmpty() )
        {
            stateMap.append( QPair( item, packageState ) );
        }
    }
    else
    {
        for ( int i = 0; i < item->childCount(); i++ )
        {
            auto* child = item->child( i );
            fetchPackageStates( stateMap, child );
        }
    }
}

void
PackageModel::applyStateToCopies( QHash<QString, Qt::CheckState>& stateHashMap )
{
    if ( m_rootItem )
    {
        this->applyStateToCopies( stateHashMap, *m_rootItem );
    }
}

void
PackageModel::applyStateToCopies( QHash<QString, Qt::CheckState>& stateHashMap, PackageTreeItem& item )
{
    if ( !this->isSharedState() || item.isIgnoringShareState() ) {
        return;
    }

    if ( item.isGroup() )
    {
        for ( int i = 0; i < item.childCount(); i++ )
        {
            auto* child = item.child( i );
            applyStateToCopies( stateHashMap, *child );
        }
    }
    else 
    {
        QString packageName = item.packageName();
        Qt::CheckState packageState = item.isSelected();
        if ( 
            !packageName.isEmpty()
            && !item.isImmutable() 
            && stateHashMap.contains( packageName )             
            && packageState != stateHashMap.value( packageName ) 
        )
        {
            item.setSelected( stateHashMap.value( packageName ) );
        }
    }
}

void
PackageModel::applyStateToCopies( QString& selectName, Qt::CheckState& selectState )
{
    if ( m_rootItem )
    {
        this->applyStateToCopies( selectName, selectState, *m_rootItem );
    }
}

void
PackageModel::applyStateToCopies( QString& selectName, Qt::CheckState& selectState, PackageTreeItem& item )
{
    QHash<QString, Qt::CheckState> stateHashMap = QHash<QString, Qt::CheckState>();    
    stateHashMap.insert( selectName, selectState );
    this->applyStateToCopies( stateHashMap, item );
}

void 
PackageModel::applyInitialStateToCopies()
{
    QHash<QString,Qt::CheckState> stateHashMap = QHash<QString,Qt::CheckState>();
    this->fetchDeduplicatedPackageStates( stateHashMap );
    this->applyStateToCopies( stateHashMap );
}

void
PackageModel::applyStateToGroupAndCopies( Qt::CheckState& selectState, PackageTreeItem& item )
{

    if ( !this->isSharedState() || item.isIgnoringShareState() ) {
        return;
    }

    if ( selectState != Qt::PartiallyChecked && item.isGroup() )
    {
        for ( int i = 0; i < item.childCount(); i++ )
        {
            auto* child = item.child( i );
            if ( !child->isGroup() )
            {
                QString packageName = child->packageName();
                this->applyStateToCopies( packageName, selectState );
            }
            else
            {
                applyStateToGroupAndCopies(selectState, *child);
            }
        }
    }
}

void
PackageModel::storeInitialState()
{  
    if ( this->isSharedState() ) {
        m_InitialStateHashMap = new QHash<QString,Qt::CheckState>();        
        this->fetchDeduplicatedPackageStates( *m_InitialStateHashMap );
    } else {
        m_InitialStateMap = new QList<QPair<PackageTreeItem*,Qt::CheckState>>();    
        this->fetchPackageStates( *m_InitialStateMap );    
    }
}

void
PackageModel::resetToDefaults()
{
    if ( this->isSharedState() ) {
        this->applyStateToCopies( *m_InitialStateHashMap );
    } else {
        QListIterator<QPair<PackageTreeItem*, Qt::CheckState>> i(*m_InitialStateMap);
        while( i.hasNext() )
        {
            QPair<PackageTreeItem*, Qt::CheckState> p = i.next();
            p.first->setSelected(p.second);
        }
    }
}

PackageTreeItem::List
PackageModel::getPackages() const
{
    if ( !m_rootItem )
    {
        return PackageTreeItem::List();
    }

    auto items = getItemPackages( m_rootItem );
    for ( auto package : m_hiddenItems )
    {
        if ( package->hiddenSelected() )
        {
            items.append( getItemPackages( package ) );
        }
    }
    return items;
}

PackageTreeItem::List
PackageModel::getItemPackages( PackageTreeItem* item ) const
{
    PackageTreeItem::List selectedPackages;
    for ( int i = 0; i < item->childCount(); i++ )
    {
        auto* child = item->child( i );
        if ( child->isSelected() == Qt::Unchecked )
        {
            continue;
        }

        if ( child->isPackage() )  // package
        {
            selectedPackages.append( child );
        }
        else
        {
            selectedPackages.append( getItemPackages( child ) );
        }
    }
    return selectedPackages;
}

void
PackageModel::setupModelData( const QVariantList& groupList, PackageTreeItem* parent )
{
    for ( const auto& group : groupList )
    {
        QVariantMap groupMap = group.toMap();
        if ( groupMap.isEmpty() )
        {
            continue;
        }

        PackageTreeItem* item = new PackageTreeItem( groupMap, PackageTreeItem::GroupTag { parent } );
        if ( groupMap.contains( "selected" ) )
        {
            item->setSelected( CalamaresUtils::getBool( groupMap, "selected", false ) ? Qt::Checked : Qt::Unchecked );
        }
        if ( groupMap.contains( "packages" ) )
        {
            for ( const auto& packageName : groupMap.value( "packages" ).toList() )
            {
                if ( packageName.type() == QVariant::String )
                {
                    item->appendChild( new PackageTreeItem( packageName.toString(), item ) );
                }
                else
                {
                    QVariantMap m = packageName.toMap();
                    if ( !m.isEmpty() )
                    {
                        item->appendChild( new PackageTreeItem( m, PackageTreeItem::PackageTag { item } ) );
                    }
                }
            }
            if ( !item->childCount() )
            {
                cWarning() << "*packages* under" << item->name() << "is empty.";
            }
        }
        if ( groupMap.contains( "subgroups" ) )
        {
            bool haveWarned = false;
            const auto& subgroupValue = groupMap.value( "subgroups" );
            if ( !subgroupValue.canConvert( QVariant::List ) )
            {
                cWarning() << "*subgroups* under" << item->name() << "is not a list.";
                haveWarned = true;
            }

            QVariantList subgroups = groupMap.value( "subgroups" ).toList();
            if ( !subgroups.isEmpty() )
            {
                setupModelData( subgroups, item );
                // The children might be checked while the parent isn't (yet).
                // Children are added to their parent (below) without affecting
                // the checked-state -- do it manually. Items with subgroups
                // but no children have only hidden children -- those get
                // handled specially.
                if ( item->childCount() > 0 )
                {
                    item->updateSelected();
                }
            }
            else
            {
                if ( !haveWarned )
                {
                    cWarning() << "*subgroups* list under" << item->name() << "is empty.";
                }
            }
        }
        if ( item->isHidden() )
        {
            m_hiddenItems.append( item );
            if ( !item->isSelected() )
            {
                cWarning() << "Item" << ( item->parentItem() ? item->parentItem()->name() : QString() ) << '.'
                           << item->name() << "is hidden, but not selected.";
            }
        }
        else
        {
            item->setCheckable( true );
            parent->appendChild( item );
        }
    }
}

void
PackageModel::setupModelData( const QVariantList& l )
{
    beginResetModel();
    delete m_rootItem;
    m_rootItem = new PackageTreeItem();
    setupModelData( l, m_rootItem );    
    endResetModel();
    this->storeInitialState();
}

void
PackageModel::appendModelData( const QVariantList& groupList )
{
    if ( m_rootItem )
    {
        beginResetModel();

        const QStringList sources = collectSources( groupList );

        if ( !sources.isEmpty() )
        {
            // Prune any existing data from the same source
            QList< int > removeList;
            for ( int i = 0; i < m_rootItem->childCount(); i++ )
            {
                PackageTreeItem* child = m_rootItem->child( i );
                if ( sources.contains( child->source() ) )
                {
                    if ( this->isSharedState() && !child->isIgnoringShareState() )
                    {
                        Qt::CheckState state = Qt::CheckState::Unchecked;
                        this->applyStateToGroupAndCopies( state, *child );
                    }
                    removeList.insert( 0, i );                    
                }
            }
            for ( const int& item : qAsConst( removeList ) )
            {
                m_rootItem->removeChild( item );
            }
        }

        // Add the new data to the model
        setupModelData( groupList, m_rootItem );

        endResetModel();
    }
}
