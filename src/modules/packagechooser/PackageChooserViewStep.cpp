/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PackageChooserViewStep.h"

#include "Config.h"
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
    , m_config( new Config( this ) )
    , m_widget( nullptr )
{
    emit nextStatusChanged( false );
}


PackageChooserViewStep::~PackageChooserViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
}


QString
PackageChooserViewStep::prettyName() const
{
    return m_config->prettyName();
}


QWidget*
PackageChooserViewStep::widget()
{
    if ( !m_widget )
    {
        m_widget = new PackageChooserPage( m_config->mode(), nullptr );
        connect( m_widget,
                 &PackageChooserPage::selectionChanged,
                 [ = ]() { emit nextStatusChanged( this->isNextEnabled() ); } );
        hookupModel();
    }
    return m_widget;
}


bool
PackageChooserViewStep::isNextEnabled() const
{
    if ( !m_widget )
    {
        // No way to have changed anything
        return true;
    }

    switch ( m_config->mode() )
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
        m_widget->setSelection( m_config->defaultSelectionIndex() );
    }
}

void
PackageChooserViewStep::onLeave()
{
    m_config->updateGlobalStorage( m_widget->selectedPackageIds() );
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
    m_config->setDefaultId( moduleInstanceKey() );
    m_config->setConfigurationMap( configurationMap );

    if ( m_widget )
    {
        hookupModel();
    }
}


void
PackageChooserViewStep::hookupModel()
{
    if ( !m_config->model() || !m_widget )
    {
        cError() << "Can't hook up model until widget and model both exist.";
        return;
    }

    m_widget->setModel( m_config->model() );
    m_widget->setIntroduction( m_config->introductionPackage() );
}
