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
#include "ItemFlatpak.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "locale/TranslatableConfiguration.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include <ext/stdio_filebuf.h>
#include <fstream>
#include <iostream>

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#ifdef HAVE_APPSTREAM
#include "ItemAppStream.h"
#include <AppStreamQt/pool.h>
#include <memory>
#endif

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
    QString flatpak("flatpak");
    QString empty;
    m_config->updateGlobalStorage( empty, m_widget->selectedPackageIds(empty) );
    m_config->updateGlobalStorage( flatpak, m_widget->selectedPackageIds(flatpak) );
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

#ifdef HAVE_APPSTREAM
    int pid;
    int pipefd[2];
    std::unique_ptr< AppStream::Pool > pool;
    bool poolOk = false;
    pipe(pipefd);

    pid = fork();
    if (0 == pid)
    {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        execlp("flatpak", "flatpak", "search", "--columns=application", "", NULL);
    }
    close(pipefd[1]);

    pool = std::make_unique< AppStream::Pool >();
    pool->setLocale( QStringLiteral( "ALL" ) );
    poolOk = pool->load();

    std::string line;
    __gnu_cxx::stdio_filebuf<char> filebuf(pipefd[0], std::ios::in);
    std::istream stream(&filebuf);

    while (!stream.eof())
    {
      getline(stream, line);
      QVariantMap item_map;

      item_map.insert("appstream", QVariant(QString::fromStdString(line)));
      item_map.insert("id", QVariant(QString::fromStdString(line)));

      m_config->model()->addPackage( fromFlatpak( *pool, item_map) );
    }

    waitpid(pid, nullptr, 0);
#endif
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
