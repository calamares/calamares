/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#ifdef HAVE_XML
#include "ItemAppData.h"
#endif

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/Variant.h"


Config::Config( const QString& defaultId, QObject* parent )
    : Calamares::ModuleSystem::Config( parent )
    , m_model( new PackageListModel( this ) )
    , m_mode( PackageChooserMode::Required )
    , m_defaultId( defaultId )
{
}

Config::~Config() {}

const PackageItem&
Config::introductionPackage() const
{
    for ( int i = 0; i < m_model->packageCount(); ++i )
    {
        const auto& package = m_model->packageData( i );
        if ( package.isNonePackage() )
        {
            return package;
        }
    }

    static PackageItem* defaultIntroduction = nullptr;
    if ( !defaultIntroduction )
    {
        defaultIntroduction = new PackageItem(
            QString(),
            QT_TR_NOOP( "Package Selection" ),
            QT_TR_NOOP( "Please pick a product from the list. The selected product will be installed." ) );
        defaultIntroduction->screenshot = QPixmap( QStringLiteral( ":/images/no-selection.png" ) );
        // TODO: enable better translation
        // defaultIntroduction->name.setContext( metaObject()->className() );
        // defaultIntroduction->description.setContext( metaObject()->className() );
    }
    return *defaultIntroduction;
}

void
Config::updateGlobalStorage( const QStringList& selected ) const
{
    QString key = QStringLiteral( "packagechooser_%1" ).arg( m_id );
    QString value = selected.join( ',' );
    Calamares::JobQueue::instance()->globalStorage()->insert( key, value );

    cDebug() << "PackageChooser" << key << "selected" << value;
}


static void
fillModel( PackageListModel* model, const QVariantList& items )
{
    if ( items.isEmpty() )
    {
        cWarning() << "No *items* for PackageChooser module.";
        return;
    }

#ifdef HAVE_APPSTREAM
    std::unique_ptr< AppStream::Pool > pool;
    bool poolOk = false;
#endif

    cDebug() << "Loading PackageChooser model items from config";
    int item_index = 0;
    for ( const auto& item_it : items )
    {
        ++item_index;
        QVariantMap item_map = item_it.toMap();
        if ( item_map.isEmpty() )
        {
            cWarning() << "PackageChooser entry" << item_index << "is not valid.";
            continue;
        }

        if ( item_map.contains( "appdata" ) )
        {
#ifdef HAVE_XML
            model->addPackage( fromAppData( item_map ) );
#else
            cWarning() << "Loading AppData XML is not supported.";
#endif
        }
        else if ( item_map.contains( "appstream" ) )
        {
#ifdef HAVE_APPSTREAM
            if ( !pool )
            {
                pool = std::make_unique< AppStream::Pool >();
                pool->setLocale( QStringLiteral( "ALL" ) );
                poolOk = pool->load();
            }
            if ( pool && poolOk )
            {
                model->addPackage( fromAppStream( *pool, item_map ) );
            }
#else
            cWarning() << "Loading AppStream data is not supported.";
#endif
        }
        else
        {
            model->addPackage( PackageItem( item_map ) );
        }
    }
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    QString mode = CalamaresUtils::getString( configurationMap, "mode" );
    bool mode_ok = false;
    if ( !mode.isEmpty() )
    {
        m_mode = packageChooserModeNames().find( mode, mode_ok );
    }
    if ( !mode_ok )
    {
        m_mode = PackageChooserMode::Required;
    }

    m_id = CalamaresUtils::getString( configurationMap, "id" );
    if ( m_id.isEmpty() )
    {
        m_id = m_defaultId;
    }

    m_defaultModelIndex = QModelIndex();
    if ( configurationMap.contains( "items" ) )
    {
        fillModel( m_model, configurationMap.value( "items" ).toList() );
    }

    QString default_item_id = CalamaresUtils::getString( configurationMap, "default" );
    // find default item
    if ( !default_item_id.isEmpty() )
    {
        for ( int item_n = 0; item_n < m_model->packageCount(); ++item_n )
        {
            QModelIndex item_idx = m_model->index( item_n, 0 );
            QVariant item_id = m_model->data( item_idx, PackageListModel::IdRole );

            if ( item_id.toString() == default_item_id )
            {
                m_defaultModelIndex = item_idx;
                break;
            }
        }
    }
}
