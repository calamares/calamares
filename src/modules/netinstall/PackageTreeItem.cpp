/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Kyle Robbertze <kyle@aims.ac.za>
 *   SPDX-FileCopyrightText: 2017 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PackageTreeItem.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

/** @brief Should a package be selected, given its parent's state? */
static Qt::CheckState
parentCheckState( PackageTreeItem* parent )
{
    if ( parent )
    {
        // Avoid partially-checked .. a package can't be partial
        return parent->isSelected() == Qt::Unchecked ? Qt::Unchecked : Qt::Checked;
    }
    else
    {
        return Qt::Unchecked;
    }
}

/** @brief Should a subgroup be marked critical?
 *
 * If set explicitly, then use that, otherwise use the parent's critical-ness.
 */
static bool
parentCriticality( const QVariantMap& groupData, PackageTreeItem* parent )
{
    if ( groupData.contains( "critical" ) )
    {
        return CalamaresUtils::getBool( groupData, "critical", false );
    }
    return parent ? parent->isCritical() : false;
}

PackageTreeItem::PackageTreeItem( const QString& packageName, PackageTreeItem* parent )
    : m_parentItem( parent )
    , m_packageName( packageName )
    , m_selected( parentCheckState( parent ) )
    , m_isGroup( false )
    , m_isCritical( parent ? parent->isCritical() : false )
    , m_showReadOnly( parent ? parent->isImmutable() : false )
{
}

PackageTreeItem::PackageTreeItem( const QVariantMap& groupData, PackageTag&& parent )
    : m_parentItem( parent.parent )
    , m_packageName( CalamaresUtils::getString( groupData, "name" ) )
    , m_selected( parentCheckState( parent.parent ) )
    , m_description( CalamaresUtils::getString( groupData, "description" ) )
    , m_isGroup( false )
    , m_isCritical( parent.parent ? parent.parent->isCritical() : false )
    , m_showReadOnly( parent.parent ? parent.parent->isImmutable() : false )
{
}

PackageTreeItem::PackageTreeItem( const QVariantMap& groupData, GroupTag&& parent )
    : m_parentItem( parent.parent )
    , m_name( CalamaresUtils::getString( groupData, "name" ) )
    , m_selected( parentCheckState( parent.parent ) )
    , m_description( CalamaresUtils::getString( groupData, "description" ) )
    , m_preScript( CalamaresUtils::getString( groupData, "pre-install" ) )
    , m_postScript( CalamaresUtils::getString( groupData, "post-install" ) )
    , m_source( CalamaresUtils::getString( groupData, "source" ) )
    , m_isGroup( true )
    , m_isCritical( parentCriticality( groupData, parent.parent ) )
    , m_isHidden( CalamaresUtils::getBool( groupData, "hidden", false ) )
    , m_showReadOnly( CalamaresUtils::getBool( groupData, "immutable", false ) )
    , m_startExpanded( CalamaresUtils::getBool( groupData, "expanded", false ) )
{
}

PackageTreeItem::PackageTreeItem::PackageTreeItem()
    : m_parentItem( nullptr )
    , m_name( QStringLiteral( "<root>" ) )
    , m_selected( Qt::Checked )
    , m_isGroup( true )
{
}

PackageTreeItem::~PackageTreeItem()
{
    qDeleteAll( m_childItems );
}

void
PackageTreeItem::appendChild( PackageTreeItem* child )
{
    m_childItems.append( child );
}

PackageTreeItem*
PackageTreeItem::child( int row )
{
    return m_childItems.value( row );
}

int
PackageTreeItem::childCount() const
{
    return m_childItems.count();
}

int
PackageTreeItem::row() const
{
    if ( m_parentItem )
    {
        return m_parentItem->m_childItems.indexOf( const_cast< PackageTreeItem* >( this ) );
    }
    return 0;
}

QVariant
PackageTreeItem::data( int column ) const
{
    switch ( column )
    {
    case 0:
        // packages have a packagename, groups don't
        return QVariant( isPackage() ? packageName() : name() );
    case 1:
        // packages often have a blank description
        return QVariant( description() );
    default:
        return QVariant();
    }
}

PackageTreeItem*
PackageTreeItem::parentItem()
{
    return m_parentItem;
}

const PackageTreeItem*
PackageTreeItem::parentItem() const
{
    return m_parentItem;
}


bool
PackageTreeItem::hiddenSelected() const
{
    if ( !m_isHidden )
    {
        return m_selected != Qt::Unchecked;
    }

    if ( m_selected == Qt::Unchecked )
    {
        return false;
    }

    const PackageTreeItem* currentItem = parentItem();
    while ( currentItem != nullptr )
    {
        if ( !currentItem->isHidden() )
        {
            return currentItem->isSelected() != Qt::Unchecked;
        }
        currentItem = currentItem->parentItem();
    }

    /* Has no non-hidden parents */
    return m_selected != Qt::Unchecked;
}


void
PackageTreeItem::setSelected( Qt::CheckState isSelected )
{
    if ( parentItem() == nullptr )
    {
        // This is the root, it is always checked so don't change state
        return;
    }

    m_selected = isSelected;
    setChildrenSelected( isSelected );

    // Look for suitable parent item which may change checked-state
    // when one of its children changes.
    PackageTreeItem* currentItem = parentItem();
    while ( ( currentItem != nullptr ) && ( currentItem->childCount() == 0 ) )
    {
        currentItem = currentItem->parentItem();
    }
    if ( currentItem == nullptr )
    {
        // Reached the root .. don't bother
        return;
    }

    currentItem->updateSelected();
}

void
PackageTreeItem::updateSelected()
{
    // Figure out checked-state based on the children
    int childrenSelected = 0;
    int childrenPartiallySelected = 0;
    for ( int i = 0; i < childCount(); i++ )
    {
        if ( child( i )->isSelected() == Qt::Checked )
        {
            childrenSelected++;
        }
        if ( child( i )->isSelected() == Qt::PartiallyChecked )
        {
            childrenPartiallySelected++;
        }
    }
    if ( !childrenSelected && !childrenPartiallySelected )
    {
        setSelected( Qt::Unchecked );
    }
    else if ( childrenSelected == childCount() )
    {
        setSelected( Qt::Checked );
    }
    else
    {
        setSelected( Qt::PartiallyChecked );
    }
}


void
PackageTreeItem::setChildrenSelected( Qt::CheckState isSelected )
{
    if ( isSelected != Qt::PartiallyChecked )
        // Children are never root; don't need to use setSelected on them.
        for ( auto child : m_childItems )
        {
            child->m_selected = isSelected;
            child->setChildrenSelected( isSelected );
        }
}

void
PackageTreeItem::removeChild( int row )
{
    if ( 0 <= row && row < m_childItems.count() )
    {
        m_childItems.removeAt( row );
    }
    else
    {
        cWarning() << "Attempt to remove invalid child in removeChild() at row " << row;
    }
}

int
PackageTreeItem::type() const
{
    return QStandardItem::UserType;
}

QVariant
PackageTreeItem::toOperation() const
{
    // If it's a package with a pre- or post-script, replace
    // with the more complicated datastructure.
    if ( !m_preScript.isEmpty() || !m_postScript.isEmpty() )
    {
        QMap< QString, QVariant > sdetails;
        sdetails.insert( "pre-script", m_preScript );
        sdetails.insert( "package", m_packageName );
        sdetails.insert( "post-script", m_postScript );
        return sdetails;
    }
    else
    {
        return m_packageName;
    }
}

bool
PackageTreeItem::operator==( const PackageTreeItem& rhs ) const
{
    if ( isGroup() != rhs.isGroup() )
    {
        // Different kinds
        return false;
    }

    if ( isGroup() )
    {
        return name() == rhs.name() && description() == rhs.description() && preScript() == rhs.preScript()
            && postScript() == rhs.postScript() && isCritical() == rhs.isCritical() && isHidden() == rhs.isHidden()
            && m_showReadOnly == rhs.m_showReadOnly && expandOnStart() == rhs.expandOnStart();
    }
    else
    {
        return packageName() == rhs.packageName();
    }
}
