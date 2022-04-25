/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#ifdef HAVE_APPDATA
#include "ItemAppData.h"
#endif

#ifdef HAVE_APPSTREAM
#include "ItemAppStream.h"
#include <AppStreamQt/pool.h>
#include <memory>
#endif


#include "GlobalStorage.h"
#include "JobQueue.h"
#include "packages/Globals.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

/** @brief This removes any values from @p groups that match @p source
 *
 * This is used to remove duplicates from the netinstallAdd structure
 * It iterates over @p groups and for each map in the list, if the
 * "source" element matches @p source, it is removed from the returned
 * list.
 */
static QVariantList
pruneNetinstallAdd( const QString& source, const QVariant& groups )
{
    QVariantList newGroupList;
    const QVariantList groupList = groups.toList();
    for ( const QVariant& group : groupList )
    {
        QVariantMap groupMap = group.toMap();
        if ( groupMap.value( "source", "" ).toString() != source )
        {
            newGroupList.append( groupMap );
        }
    }
    return newGroupList;
}

const NamedEnumTable< PackageChooserMode >&
packageChooserModeNames()
{
    static const NamedEnumTable< PackageChooserMode > names {
        { "optional", PackageChooserMode::Optional },
        { "required", PackageChooserMode::Required },
        { "optionalmultiple", PackageChooserMode::OptionalMultiple },
        { "requiredmultiple", PackageChooserMode::RequiredMultiple },
        // and a bunch of aliases
        { "zero-or-one", PackageChooserMode::Optional },
        { "radio", PackageChooserMode::Required },
        { "one", PackageChooserMode::Required },
        { "set", PackageChooserMode::OptionalMultiple },
        { "zero-or-more", PackageChooserMode::OptionalMultiple },
        { "multiple", PackageChooserMode::RequiredMultiple },
        { "one-or-more", PackageChooserMode::RequiredMultiple }
    };
    return names;
}

const NamedEnumTable< PackageChooserMethod >&
PackageChooserMethodNames()
{
    static const NamedEnumTable< PackageChooserMethod > names {
        { "legacy", PackageChooserMethod::Legacy },
        { "custom", PackageChooserMethod::Legacy },
        { "contextualprocess", PackageChooserMethod::Legacy },
        { "packages", PackageChooserMethod::Packages },
        { "netinstall-add", PackageChooserMethod::NetAdd },
        { "netinstall-select", PackageChooserMethod::NetSelect },
    };
    return names;
}

Config::Config( QObject* parent )
    : Calamares::ModuleSystem::Config( parent )
    , m_model( new PackageListModel( this ) )
    , m_mode( PackageChooserMode::Required )
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
        const auto name = QT_TR_NOOP( "Package Selection" );
        const auto description
            = QT_TR_NOOP( "Please pick a product from the list. The selected product will be installed." );
        defaultIntroduction = new PackageItem( QString(), name, description );
        defaultIntroduction->screenshot = QPixmap( QStringLiteral( ":/images/no-selection.png" ) );
        defaultIntroduction->name = CalamaresUtils::Locale::TranslatedString( name, metaObject()->className() );
        defaultIntroduction->description
            = CalamaresUtils::Locale::TranslatedString( description, metaObject()->className() );
    }
    return *defaultIntroduction;
}

static inline QString
make_gs_key( const Calamares::ModuleSystem::InstanceKey& key )
{
    return QStringLiteral( "packagechooser_" ) + key.id();
}

void
Config::updateGlobalStorage( const QStringList& selected ) const
{
    if ( m_packageChoice.has_value() )
    {
        cWarning() << "Inconsistent package choices -- both model and single-selection QML";
    }
    if ( m_method == PackageChooserMethod::Legacy )
    {
        QString value = selected.join( ',' );
        Calamares::JobQueue::instance()->globalStorage()->insert( make_gs_key( m_defaultId ), value );
        cDebug() << m_defaultId << "selected" << value;
    }
    else if ( m_method == PackageChooserMethod::Packages )
    {
        QStringList packageNames = m_model->getInstallPackagesForNames( selected );
        cDebug() << m_defaultId << "packages to install" << packageNames;
        CalamaresUtils::Packages::setGSPackageAdditions(
            Calamares::JobQueue::instance()->globalStorage(), m_defaultId, packageNames );
    }
    else if ( m_method == PackageChooserMethod::NetAdd )
    {
        QVariantList netinstallDataList = m_model->getNetinstallDataForNames( selected );
        if ( netinstallDataList.isEmpty() )
        {
            cWarning() << "No netinstall information found for " << selected;
        }
        else
        {
            // If an earlier packagechooser instance added this data to global storage, combine them
            auto* gs = Calamares::JobQueue::instance()->globalStorage();
            if ( gs->contains( "netinstallAdd" ) )
            {
                netinstallDataList
                    += pruneNetinstallAdd( QStringLiteral( "packageChooser" ), gs->value( "netinstallAdd" ) );
            }
            gs->insert( "netinstallAdd", netinstallDataList );
        }
    }
    else if ( m_method == PackageChooserMethod::NetSelect )
    {
        cDebug() << m_defaultId << "groups to select in netinstall" << selected;
        QStringList newSelected = selected;
        auto* gs = Calamares::JobQueue::instance()->globalStorage();

        // If an earlier packagechooser instance added this data to global storage, combine them
        if ( gs->contains( "netinstallSelect" ) )
        {
            auto selectedOrig = gs->value( "netinstallSelect" );
            if ( selectedOrig.canConvert( QVariant::StringList ) )
            {
                newSelected += selectedOrig.toStringList();
            }
            else
            {
                cWarning() << "Invalid NetinstallSelect data in global storage.  Earlier selections purged";
            }
            gs->remove( "netinstallSelect" );
        }
        gs->insert( "netinstallSelect", newSelected );
    }
    else
    {
        cWarning() << "Unknown packagechooser method" << smash( m_method );
    }
}

void
Config::updateGlobalStorage() const
{
    if ( m_model->packageCount() > 0 )
    {
        cWarning() << "Inconsistent package choices -- both model and single-selection QML";
    }
    if ( m_method == PackageChooserMethod::Legacy )
    {
        auto* gs = Calamares::JobQueue::instance()->globalStorage();
        if ( m_packageChoice.has_value() )
        {
            gs->insert( make_gs_key( m_defaultId ), m_packageChoice.value() );
        }
        else
        {
            gs->remove( make_gs_key( m_defaultId ) );
        }
    }
    else if ( m_method == PackageChooserMethod::Packages )
    {
        cWarning() << "Unsupported single-selection packagechooser method 'Packages'";
    }
    else
    {
        cWarning() << "Unknown packagechooser method" << smash( m_method );
    }
}


void
Config::setPackageChoice( const QString& packageChoice )
{
    if ( packageChoice.isEmpty() )
    {
        m_packageChoice.reset();
    }
    else
    {
        m_packageChoice = packageChoice;
    }
    emit packageChoiceChanged( m_packageChoice.value_or( QString() ) );
}

QString
Config::prettyName() const
{
    return m_stepName ? m_stepName->get() : tr( "Packages" );
}

QString
Config::prettyStatus() const
{
    return tr( "Install option: <strong>%1</strong>" ).arg( m_packageChoice.value_or( tr( "None" ) ) );
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
    cDebug() << Logger::SubEntry << "Loaded PackageChooser with" << model->packageCount() << "entries.";
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_mode = packageChooserModeNames().find( CalamaresUtils::getString( configurationMap, "mode" ),
                                             PackageChooserMode::Required );
    m_method = PackageChooserMethodNames().find( CalamaresUtils::getString( configurationMap, "method" ),
                                                 PackageChooserMethod::Legacy );

    if ( m_method == PackageChooserMethod::Legacy )
    {
        cDebug() << "Using module ID" << m_defaultId;
    }

    if ( configurationMap.contains( "items" ) )
    {
        fillModel( m_model, configurationMap.value( "items" ).toList() );

        QString default_item_id = CalamaresUtils::getString( configurationMap, "default" );
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
    else
    {
        setPackageChoice( CalamaresUtils::getString( configurationMap, "packageChoice" ) );
        if ( m_method != PackageChooserMethod::Legacy )
        {
            cWarning() << "Single-selection QML module must use 'Legacy' method.";
        }
    }

    bool labels_ok = false;
    auto labels = CalamaresUtils::getSubMap( configurationMap, "labels", labels_ok );
    if ( labels_ok )
    {
        if ( labels.contains( "step" ) )
        {
            m_stepName = new CalamaresUtils::Locale::TranslatedString( labels, "step" );
        }
    }
}
