/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
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
    m_progressTimer->start( 1200 );  // msec

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
        m_model->changeRequirementsList();
        QTimer::singleShot( 0, this, &RequirementsChecker::done );
    }
}

void
RequirementsChecker::addCheckedRequirements( Module* m )
{
    RequirementsList l = m->checkRequirements();
    cDebug() << "Got" << l.count() << "requirement results from" << m->name();
    if ( l.count() > 0 )
    {
        m_model->addRequirementsList( l );
    }

    requirementsProgress( tr( "Requirements checking for module <i>%1</i> is complete." ).arg( m->name() ) );
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
