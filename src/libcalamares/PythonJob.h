/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
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

#ifndef CALAMARES_PYTHONJOB_H
#define CALAMARES_PYTHONJOB_H

#include "Job.h"
#include "modulesystem/InstanceKey.h"

#include <QVariantMap>

#include <memory>

namespace CalamaresPython
{
class PythonJobInterface;
class Helper;
}  // namespace CalamaresPython

namespace Calamares
{

class PythonJob : public Job
{
    Q_OBJECT
public:
    explicit PythonJob( const ModuleSystem::InstanceKey& instance,
                        const QString& scriptFile,
                        const QString& workingPath,
                        const QVariantMap& moduleConfiguration = QVariantMap(),
                        QObject* parent = nullptr );
    virtual ~PythonJob() override;

    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    JobResult exec() override;

    virtual qreal getJobWeight() const override;

private:
    struct Private;

    friend class CalamaresPython::PythonJobInterface;
    void emitProgress( double progressValue );

    std::unique_ptr< Private > m_d;
    QString m_scriptFile;
    QString m_workingPath;
    QString m_description;
    QVariantMap m_configurationMap;
    qreal m_weight;
};

}  // namespace Calamares

#endif  // CALAMARES_PYTHONJOB_H
