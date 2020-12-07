/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
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
    explicit PythonJob( const QString& scriptFile,
                        const QString& workingPath,
                        const QVariantMap& moduleConfiguration = QVariantMap(),
                        QObject* parent = nullptr );
    ~PythonJob() override;

    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    JobResult exec() override;

private:
    struct Private;

    friend class CalamaresPython::PythonJobInterface;
    void emitProgress( double progressValue );

    std::unique_ptr< Private > m_d;
    QString m_scriptFile;
    QString m_workingPath;
    QString m_description;
    QVariantMap m_configurationMap;
};

}  // namespace Calamares

#endif  // CALAMARES_PYTHONJOB_H
