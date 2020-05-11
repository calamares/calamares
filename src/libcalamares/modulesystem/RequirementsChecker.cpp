/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "RequirementsChecker.h"

#include "modulesystem/Module.h"
#include "modulesystem/Requirement.h"
#include "modulesystem/RequirementsModel.h"
#include "utils/Logger.h"

#include <QFuture>
#include <QFutureWatcher>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

#include <algorithm>

namespace Calamares
{

static void
registerMetatypes()
{
    static bool done = false;

    if ( !done )
    {
        qRegisterMetaType< RequirementEntry >( "RequirementEntry" );
        // It's sensitive to the names of types in parameters; in particular
        // althrough QList<RequirementEntry> is the same as RequirementsList,
        // because we *name* the type as  RequirementsList in the parameters,
        // we need to register that (as well). Here, be safe and register
        // both names.
        qRegisterMetaType< QList< RequirementEntry > >( "QList<RequirementEntry>" );
        qRegisterMetaType< RequirementsList >( "RequirementsList" );
        done = true;
    }
}

static void
check( Module* const& m, RequirementsChecker* c )
{
    RequirementsList l = m->checkRequirements();
    if ( l.count() > 0 )
    {
        c->addCheckedRequirements( l );
    }
    c->requirementsProgress(
        QObject::tr( "Requirements checking for module <i>%1</i> is complete." ).arg( m->name() ) );
}

RequirementsChecker::RequirementsChecker( QVector< Module* > modules, RequirementsModel* model, QObject* parent )
    : QObject( parent )
    , m_modules( std::move( modules ) )
    , m_model( model )
    , m_progressTimer( nullptr )
    , m_progressTimeouts( 0 )
{
    m_watchers.reserve( m_modules.count() );

    registerMetatypes();
}

RequirementsChecker::~RequirementsChecker() {}

void
RequirementsChecker::run()
{
    m_progressTimer = new QTimer( this );
    connect( m_progressTimer, &QTimer::timeout, this, &RequirementsChecker::reportProgress );
    m_progressTimer->start( 1200 );  // msec

    for ( const auto& module : m_modules )
    {
        Watcher* watcher = new Watcher( this );
        watcher->setFuture( QtConcurrent::run( check, module, this ) );
        watcher->setObjectName( module->name() );
        m_watchers.append( watcher );
        connect( watcher, &Watcher::finished, this, &RequirementsChecker::finished );
    }

    QTimer::singleShot( 0, this, &RequirementsChecker::finished );
}

void
RequirementsChecker::finished()
{
    static QMutex finishedMutex;
    QMutexLocker lock( &finishedMutex );

    if ( m_progressTimer && std::all_of( m_watchers.cbegin(), m_watchers.cend(), []( const Watcher* w ) {
             return w && w->isFinished();
         } ) )
    {
        cDebug() << "All requirements have been checked.";
        if ( m_progressTimer )
        {
            m_progressTimer->stop();
            delete m_progressTimer;
            m_progressTimer = nullptr;
        }

        m_model->describe();
        emit requirementsComplete( m_model->satisfiedMandatory() );
        QTimer::singleShot( 0, this, &RequirementsChecker::done );
    }
}

void
RequirementsChecker::addCheckedRequirements( RequirementsList l )
{
    m_model->addRequirementsList( l );
    cDebug() << "Added" << l.count() << "requirement results";
    emit requirementsResult( l );
}

void
RequirementsChecker::reportProgress()
{
    m_progressTimeouts++;

    QStringList remainingNames;
    auto remaining = std::count_if( m_watchers.cbegin(), m_watchers.cend(), [&]( const Watcher* w ) {
        if ( w && !w->isFinished() )
        {
            remainingNames << w->objectName();
            return true;
        }
        return false;
    } );
    if ( remaining > 0 )
    {
        cDebug() << "Remaining modules:" << remaining << Logger::DebugList( remainingNames );
        unsigned int posInterval = ( m_progressTimer->interval() < 0 ) ? 1000 : uint( m_progressTimer->interval() );
        QString waiting = tr( "Waiting for %n module(s).", "", remaining );
        QString elapsed = tr( "(%n second(s))", "", m_progressTimeouts * posInterval / 1000 );
        emit requirementsProgress( waiting + QString( " " ) + elapsed );
    }
    else
    {
        emit requirementsProgress( tr( "System-requirements checking is complete." ) );
    }
}

}  // namespace Calamares
