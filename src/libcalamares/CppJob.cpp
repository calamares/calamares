/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2016, Kevin Kofler <kevin.kofler@chello.at>
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

#include "CppJob.h"

namespace Calamares
{

CppJob::CppJob( QObject* parent )
    : Job( parent )
{}


CppJob::~CppJob()
{}


void
CppJob::setModuleInstanceKey( const QString& instanceKey )
{
    m_instanceKey = instanceKey;
}


void
CppJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    Q_UNUSED( configurationMap );
}

}
