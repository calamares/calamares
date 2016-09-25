/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARES_CPPJOB_H
#define CALAMARES_CPPJOB_H

#include <QObject>
#include <QVariant>

#include "DllMacro.h"
#include "Typedefs.h"
#include "Job.h"

namespace Calamares
{

class DLLEXPORT CppJob : public Job
{
    Q_OBJECT
public:
    explicit CppJob( QObject* parent = nullptr );
    virtual ~CppJob();

    void setModuleInstanceKey( const QString& instanceKey );
    QString moduleInstanceKey() const { return m_instanceKey; }

    virtual void setConfigurationMap( const QVariantMap& configurationMap );

protected:
    QString m_instanceKey;
};

}

#endif // CALAMARES_CPPJOB_H
