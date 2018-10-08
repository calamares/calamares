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

class CoreBackend;  // From KPMCore
class Device;  // From KPMCore
class Partition;

class PLUGINDLLEXPORT ResizeFSJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    /** @brief Size expressions
     *
     * Sizes can be specified in MiB or percent (of the device they
     * are on). This class handles parsing of such strings from the
     * config file.
     */
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

        int value() const { return m_value; }
        Unit unit() const { return m_unit; }

        bool isValid() const
        {
            return ( unit() != None ) && ( value() > 0 );
        }

        /** @brief Apply this size to the number of sectors @p totalSectors .
         *
         * Each sector has size @p sectorSize , for converting absolute
         * sizes in MiB to sector counts.
         *
         * For invalid sizes, returns -1.
         * For absolute sizes, returns the number of sectors needed.
         * For percent sizes, returns that percent of the number of sectors.
         */
        qint64 apply( qint64 totalSectors, qint64 sectorSize );

        /** @brief Apply this size to the given device.
         *
         * Equivalent to apply( d->totalLogical(), d->logicalSize() )
         */
        qint64 apply( Device* d );

    private:
        int m_value;
        Unit m_unit;
    } ;

    explicit ResizeFSJob( QObject* parent = nullptr );
    virtual ~ResizeFSJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    /** @brief Is the configuration of this job valid? */
    bool isValid() const
    {
        return ( !m_fsname.isEmpty() || !m_devicename.isEmpty() ) &&
               m_size.isValid();
    }

private:
    RelativeSize m_size;
    RelativeSize m_atleast;
    QString m_fsname;  // Either this, or devicename, is set, not both
    QString m_devicename;
    bool m_required;

    using PartitionMatch = QPair<Device*, Partition*>;
    /** @brief Find the configured FS using KPMCore @p backend */
    PartitionMatch findPartition( CoreBackend* backend );

    /** @brief Return a new end-sector for the given dev-part pair. */
    qint64 findGrownEnd( PartitionMatch );
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( ResizeFSJobFactory )

#endif // RESIZEFSJOB_H
