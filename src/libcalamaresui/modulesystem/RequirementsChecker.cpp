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

#include "Module.h"
#include "Requirement.h"

#include "utils/Logger.h"

#include <QTimer>

namespace Calamares
{

RequirementsChecker::RequirementsChecker( QVector< Module* > modules, QObject* parent )
    : QObject( parent )
    , m_modules( std::move( modules ) )
{
}

RequirementsChecker::~RequirementsChecker()
{
}

void
RequirementsChecker::run()
{
    bool acceptable = true;

    for (const auto& module : m_modules )
    {
        RequirementsList l = module->checkRequirements();
        if ( l.length() > 0 )
        {
            cDebug() << "  .." << module->name() << "has" << l.length() << "requirements";
            emit requirementsResult( l );
        }

        int count = 0;
        for (const auto& r : l)
        {
            if ( r.mandatory && !r.satisfied )
            {
                cDebug() << "  .. requirement" << count << r.name << "is not satisfied.";
                acceptable = false;
            }
            ++count;
        }
    }

    emit requirementsComplete( acceptable );

    QTimer::singleShot(0, this, &RequirementsChecker::done );
}


}
