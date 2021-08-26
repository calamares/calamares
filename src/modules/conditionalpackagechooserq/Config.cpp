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
    };
    return names;
}

Config::Config( QObject* parent )
    : Calamares::ModuleSystem::Config( parent )
    , m_model( new PackageListModel( this ) )
    , m_mode( PackageChooserMode::Required )
    , m_selections( QStringList() )
    , m_entryIds( QStringList() )
    , m_entryNames( QStringList() )
    , m_entryDescriptions( QStringList() )
    , m_entryScreenshots( QVector<QString>() )
    , m_entryPackages( QVector<QStringList>() )
    , m_entrySelectedStates( QVector<bool>() )
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
        defaultIntroduction->screenshot = QStringLiteral( ":/images/no-selection.png" );
        defaultIntroduction->name = CalamaresUtils::Locale::TranslatedString( name, metaObject()->className() );
        defaultIntroduction->description
            = CalamaresUtils::Locale::TranslatedString( description, metaObject()->className() );
    }
    return *defaultIntroduction;
}

void
Config::updateGlobalStorage() const
{

    Calamares::JobQueue::instance()->globalStorage()->insert( m_outputConditionName, m_selections );

    if ( m_method == PackageChooserMethod::Legacy )
    {
        //QString value = m_selections.join( ',' );
        QString value = ( m_pkgc );
        Calamares::JobQueue::instance()->globalStorage()->insert( m_id, value );
        cDebug() << m_id<< "selected" << value;
    }
    else if ( m_method == PackageChooserMethod::Packages )
    {
        cDebug() << "m_selections: " << m_selections;
        QStringList packageNames = m_model->getInstallPackagesForNames( m_selections );
        cDebug() << m_defaultId << "packages to install" << packageNames;
        CalamaresUtils::Packages::setGSPackageAdditions(
            Calamares::JobQueue::instance()->globalStorage(), m_defaultId, packageNames );
    }
    else
    {
        cWarning() << "Unknown packagechooser method" << smash( m_method );
    }
}

void
Config::setPkgc( const QString& pkgc )
{
    m_pkgc = pkgc;
    emit pkgcChanged( m_pkgc );
}

QString
Config::prettyStatus() const
{
    return tr( "Install option: <strong>%1</strong>" ).arg( m_pkgc );
}

static void
fillModel( PackageListModel* model, const QVariantList& items )
{
    if ( items.isEmpty() )
    {
        cWarning() << "No *items* for ConditionalPackageChooser module.";
        return;
    }

#ifdef HAVE_APPSTREAM
    std::unique_ptr< AppStream::Pool > pool;
    bool poolOk = false;
#endif

    cDebug() << "Loading ConditionalPackageChooser model items from config";
    int item_index = 0;
    for ( const auto& item_it : items )
    {
        ++item_index;
        QVariantMap item_map = item_it.toMap();
        if ( item_map.isEmpty() )
        {
            cWarning() << "ConditionalPackageChooser entry" << item_index << "is not valid.";
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
                                                 PackageChooserMethod::Packages );
    m_pkgc = CalamaresUtils::getString( configurationMap, "pkgc" );
    m_outputConditionName = CalamaresUtils::getString( configurationMap, "outputconditionname" );

    if ( m_method == PackageChooserMethod::Legacy )
    {
        const QString configId = CalamaresUtils::getString( configurationMap, "id" );
        const QString base = QStringLiteral( "packagechooser_" );
        if ( configId.isEmpty() )
        {
            if ( m_defaultId.id().isEmpty() )
            {
                // We got nothing to work with
                m_id = base;
            }
            else
            {
                m_id = base + m_defaultId.id();
            }
            cDebug() << "Using default ID" << m_id << "from" << m_defaultId.toString();
        }
        else
        {
            m_id = base + configId;
            cDebug() << "Using configured ID" << m_id;
        }
    }

    if ( configurationMap.contains( "items" ) )
    {
        fillModel( m_model, configurationMap.value( "items" ).toList() );
    }

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

    PackageItem entryData;
    for(int i=0; i< m_model-> packageCount(); i++) {
        entryData = m_model -> packageData(i);
        m_entryIds.append(entryData.id);  
        m_entryNames.append(entryData.name.get());    
        m_entryDescriptions.append(entryData.description.get());
        m_entryScreenshots.append(entryData.screenshot);
        m_entryPackages.append(entryData.packageNames);
        m_entrySelectedStates.append(entryData.selected);
    }

    cDebug() << "entryIds: " << m_entryIds;
    cDebug() << "entryNames: " << m_entryNames;
    cDebug() << "entryDescriptions: " << m_entryDescriptions;
    cDebug() << "entryScreenshots: " << m_entryScreenshots;
    cDebug() << "entryPackages: " << m_entryPackages;
    cDebug() << "entrySelectedStates: " << m_entrySelectedStates;
    cDebug() << "outputConditionName: " << m_outputConditionName;
}

void Config::addSelection(const QString& selection)
{
    if ( !m_selections.contains(selection) )
    {
        cDebug() << m_defaultId << " Adding " << selection << " as a selection...";
        m_selections.append(selection);
        cDebug() << "m_selections: " << m_selections;
    } else {
        cWarning() << m_defaultId << " Selection " << selection << " already exists in the list of selections. This is a bug";
    }
}

void Config::removeSelection(const QString& selection)
{
    if ( m_selections.contains(selection) )
    {
        cDebug() << m_defaultId << " Removing " << selection << " from selections...";
        m_selections.removeAll(selection);
        cDebug() << "m_selections: " << m_selections;
    }  else {
        cWarning() << m_defaultId << " Selection " << selection << " did not exist in the list of selections while deselecting. This is a bug";
    }
}
