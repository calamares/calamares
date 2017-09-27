/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARES_PYTHONJOB_H
#define CALAMARES_PYTHONJOB_H

#include "Job.h"

#include <QVariant>

namespace CalamaresPython
{
class PythonJobInterface;
class Helper;
}

namespace Calamares {

class PythonJob : public Job
{
    Q_OBJECT
public:
    explicit PythonJob( const QString& scriptFile,
                        const QString& workingPath,
                        const QVariantMap& moduleConfiguration = QVariantMap(),
                        QObject* parent = nullptr );
    virtual ~PythonJob() override;

    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    JobResult exec() override;

private:
    friend class CalamaresPython::Helper;
    friend class CalamaresPython::PythonJobInterface;
    void emitProgress( double progressValue );

    CalamaresPython::Helper* helper();
    QString m_scriptFile;
    QString m_workingPath;
    QString m_description;
    QVariantMap m_configurationMap;
};

} // namespace Calamares

#endif // CALAMARES_PYTHONJOB_H
