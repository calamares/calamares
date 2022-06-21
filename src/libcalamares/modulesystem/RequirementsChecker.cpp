/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
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

RequirementsChecker::RequirementsChecker( QVector< Module* > modules, RequirementsModel* model, QObject* parent )
    : QObject( parent )
    , m_modules( std::move( modules ) )
    , m_model( model )
    , m_progressTimer( nullptr )
    , m_progressTimeouts( 0 )
{
    m_watchers.reserve( m_modules.count() );
    connect( this, &RequirementsChecker::requirementsProgress, model, &RequirementsModel::setProgressMessage );
}

RequirementsChecker::~RequirementsChecker() {}

void
RequirementsChecker::run()
{
    m_progressTimer = new QTimer( this );
    connect( m_progressTimer, &QTimer::timeout, this, &RequirementsChecker::reportProgress );
    m_progressTimer->start( std::chrono::milliseconds( 1200 ) );

    for ( const auto& module : m_modules )
    {
        Watcher* watcher = new Watcher( this );
        watcher->setFuture( QtConcurrent::run( this, &RequirementsChecker::addCheckedRequirements, module ) );
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

    if ( m_progressTimer
         && std::all_of(
             m_watchers.cbegin(), m_watchers.cend(), []( const Watcher* w ) { return w && w->isFinished(); } ) )
    {
        cDebug() << "All requirements have been checked.";
        if ( m_progressTimer )
        {
            m_progressTimer->stop();
            delete m_progressTimer;
            m_progressTimer = nullptr;
        }

        m_model->describe();
        m_model->reCheckList();
        QTimer::singleShot( 0, this, &RequirementsChecker::done );
    }
}

void
RequirementsChecker::addCheckedRequirements( Module* m )
{
    RequirementsList l = m->checkRequirements();
    if ( l.count() > 0 )
    {
        cDebug() << "Got" << l.count() << "requirement results from" << m->name();
        m_model->addRequirementsList( l );
    }

    Q_EMIT requirementsProgress( tr( "Requirements checking for module '%1' is complete." ).arg( m->name() ) );
}

void
RequirementsChecker::reportProgress()
{
    m_progressTimeouts++;

    QStringList remainingNames;
    auto remaining = std::count_if( m_watchers.cbegin(),
                                    m_watchers.cend(),
                                    [ & ]( const Watcher* w )
                                    {
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
        Q_EMIT requirementsProgress( waiting + QString( " " ) + elapsed );
    }
    else
    {
        Q_EMIT requirementsProgress( tr( "System-requirements checking is complete." ) );
    }
}

}  // namespace Calamares
