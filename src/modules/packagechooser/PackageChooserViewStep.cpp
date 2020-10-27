/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PackageChooserViewStep.h"

#ifdef HAVE_XML
#include "ItemAppData.h"
#endif
#ifdef HAVE_APPSTREAM
#include "ItemAppStream.h"
#include <AppStreamQt/pool.h>
#include <memory>
#endif
#include "PackageChooserPage.h"
#include "PackageModel.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include "locale/TranslatableConfiguration.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QDesktopServices>
#include <QVariantMap>

CALAMARES_PLUGIN_FACTORY_DEFINITION( PackageChooserViewStepFactory, registerPlugin< PackageChooserViewStep >(); )

PackageChooserViewStep::PackageChooserViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( nullptr )
    , m_model( nullptr )
    , m_mode( PackageChooserMode::Required )
    , m_stepName( nullptr )
{
    emit nextStatusChanged( false );
}


PackageChooserViewStep::~PackageChooserViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
    delete m_model;
    delete m_stepName;
}


QString
PackageChooserViewStep::prettyName() const
{
    return m_stepName ? m_stepName->get() : tr( "Packages" );
}


QWidget*
PackageChooserViewStep::widget()
{
    if ( !m_widget )
    {
        m_widget = new PackageChooserPage( m_mode, nullptr );
        connect( m_widget, &PackageChooserPage::selectionChanged, [=]() {
            emit nextStatusChanged( this->isNextEnabled() );
        } );

        if ( m_model )
        {
            hookupModel();
        }
        else
        {
            cWarning() << "PackageChooser Widget created before model.";
        }
    }
    return m_widget;
}


bool
PackageChooserViewStep::isNextEnabled() const
{
    if ( !m_model )
    {
        return false;
    }

    if ( !m_widget )
    {
        // No way to have changed anything
        return true;
    }

    switch ( m_mode )
    {
    case PackageChooserMode::Optional:
    case PackageChooserMode::OptionalMultiple:
        // zero or one OR zero or more
        return true;
    case PackageChooserMode::Required:
    case PackageChooserMode::RequiredMultiple:
        // exactly one OR one or more
        return m_widget->hasSelection();
    }
    __builtin_unreachable();
}


bool
PackageChooserViewStep::isBackEnabled() const
{
    return true;
}


bool
PackageChooserViewStep::isAtBeginning() const
{
    return true;
}


bool
PackageChooserViewStep::isAtEnd() const
{
    return true;
}

void
PackageChooserViewStep::onActivate()
{
    if ( !m_widget->hasSelection() )
    {
        m_widget->setSelection( m_defaultIdx );
    }
}

void
PackageChooserViewStep::onLeave()
{
    QString key = QStringLiteral( "packagechooser_%1" ).arg( m_id );
    QString value;
    if ( m_widget->hasSelection() )
    {
        value = m_widget->selectedPackageIds().join( ',' );
    }
    Calamares::JobQueue::instance()->globalStorage()->insert( key, value );

    cDebug() << "PackageChooser" << key << "selected" << value;
}

Calamares::JobList
PackageChooserViewStep::jobs() const
{
    Calamares::JobList l;
    return l;
}

void
PackageChooserViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    QString mode = CalamaresUtils::getString( configurationMap, "mode" );
    bool mode_ok = false;
    if ( !mode.isEmpty() )
    {
        m_mode = roleNames().find( mode, mode_ok );
    }
    if ( !mode_ok )
    {
        m_mode = PackageChooserMode::Required;
    }

    m_id = CalamaresUtils::getString( configurationMap, "id" );
    if ( m_id.isEmpty() )
    {
        // Not set, so use the instance id
        m_id = moduleInstanceKey().id();
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

    QString default_item_id = CalamaresUtils::getString( configurationMap, "default" );
    m_defaultIdx = QModelIndex();

    bool first_time = !m_model;
    if ( configurationMap.contains( "items" ) )
    {
        fillModel( configurationMap.value( "items" ).toList() );
    }

    if ( first_time && m_widget && m_model )
    {
        hookupModel();
    }

    // find default item
    if ( first_time && m_model && !default_item_id.isEmpty() )
    {
        for ( int item_n = 0; item_n < m_model->packageCount(); ++item_n )
        {
            QModelIndex item_idx = m_model->index( item_n, 0 );
            QVariant item_id = m_model->data( item_idx, PackageListModel::IdRole );

            if ( item_id.toString() == default_item_id )
            {
                m_defaultIdx = item_idx;
                break;
            }
        }
    }
}

void
PackageChooserViewStep::fillModel( const QVariantList& items )
{
    if ( !m_model )
    {
        m_model = new PackageListModel( nullptr );
    }

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
            m_model->addPackage( fromAppData( item_map ) );
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
                m_model->addPackage( fromAppStream( *pool, item_map ) );
            }
#else
            cWarning() << "Loading AppStream data is not supported.";
#endif
        }
        else
        {
            m_model->addPackage( PackageItem( item_map ) );
        }
    }
}

void
PackageChooserViewStep::hookupModel()
{
    if ( !m_model || !m_widget )
    {
        cError() << "Can't hook up model until widget and model both exist.";
        return;
    }

    m_widget->setModel( m_model );
    for ( int i = 0; i < m_model->packageCount(); ++i )
    {
        const auto& package = m_model->packageData( i );
        if ( package.id.isEmpty() )
        {
            m_widget->setIntroduction( package );
            break;
        }
    }
}
