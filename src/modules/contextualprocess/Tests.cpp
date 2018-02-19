/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "Tests.h"
#include "ContextualProcessJob.h"

#include "utils/CommandList.h"
#include "utils/YamlUtils.h"

#include <yaml-cpp/yaml.h>

#include <QtTest/QtTest>

#include <QFileInfo>
#include <QStringList>

QTEST_GUILESS_MAIN( ContextualProcessTests )

using CommandList = CalamaresUtils::CommandList;

ContextualProcessTests::ContextualProcessTests()
{
}

ContextualProcessTests::~ContextualProcessTests()
{
}

void
ContextualProcessTests::initTestCase()
{
}

void
ContextualProcessTests::testProcessListSampleConfig()
{
    YAML::Node doc;

    QStringList dirs { "src/modules/contextualprocess", "." };
    for ( const auto& dir : dirs )
    {
        QString filename = dir + "/contextualprocess.conf";
        if ( QFileInfo::exists( filename ) )
        {
            doc = YAML::LoadFile( filename.toStdString() );
            break;
        }
    }

    ContextualProcessJob job;
    job.setConfigurationMap( CalamaresUtils::yamlMapToVariant( doc ).toMap() );

    QCOMPARE(job.count(), 1); // Only "firmwareType"
    QCOMPARE(job.count("firmwareType"), 4);
}

