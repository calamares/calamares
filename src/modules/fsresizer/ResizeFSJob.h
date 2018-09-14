/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#ifndef RESIZEFSJOB_H
#define RESIZEFSJOB_H

#include <QObject>
#include <QVariantMap>

#include <CppJob.h>

#include <utils/PluginFactory.h>

#include <PluginDllMacro.h>

class PLUGINDLLEXPORT ResizeFSJob : public Calamares::CppJob
{
    Q_OBJECT

    class RelativeSize
    {
    public:
        RelativeSize();
        RelativeSize( const QString& );

        enum Unit
        {
            None,
            Percent,
            Absolute
        };

        quint64 value() const { return m_value; }
        Unit unit() const { return m_unit; }

    private:
        quint64 m_value;
        Unit m_unit;
    } ;

public:
    explicit ResizeFSJob( QObject* parent = nullptr );
    virtual ~ResizeFSJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    RelativeSize m_size;
    RelativeSize m_atleast;
    QString m_fsname;  // Either this, or devicename, is set, not both
    QString m_devicename;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( ResizeFSJobFactory )

#endif // RESIZEFSJOB_H
