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

#include "PythonJobApi.h"

#include "PythonHelper.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsSystem.h"

#include <QDir>

#undef slots
#include <boost/python/extract.hpp>


namespace CalamaresPython
{

int
mount( const std::string& device_path,
       const std::string& mount_point,
       const std::string& filesystem_name,
       const std::string& options )
{
    return CalamaresUtils::mount( QString::fromStdString( device_path ),
                                  QString::fromStdString( mount_point ),
                                  QString::fromStdString( filesystem_name ),
                                  QString::fromStdString( options ) );
}


int
chroot_call( const std::string& command,
             const std::string& stdin,
             int timeout )
{
    return CalamaresUtils::chrootCall( QString::fromStdString( command ),
                                       QString::fromStdString( stdin ),
                                       timeout );
}


int
chroot_call( const boost::python::list& args,
             const std::string& stdin,
             int timeout )
{
    QStringList list;
    for ( int i = 0; i < boost::python::len( args ); ++i )
    {
        list.append( QString::fromStdString(
            boost::python::extract< std::string >( args[ i ] ) ) );
    }
    return CalamaresUtils::chrootCall( list.join( ' ' ),
                                       QString::fromStdString( stdin ),
                                       timeout );
}


void
debug( const std::string& s )
{
    cDebug() << "[PYTHON JOB]: " << QString::fromStdString( s );
}


PythonJobInterface::PythonJobInterface( Calamares::PythonJob* parent )
    : m_parent( parent )
{
    moduleName = QDir( m_parent->m_workingPath ).dirName().toStdString();
    prettyName = m_parent->prettyName().toStdString();
    workingPath = m_parent->m_workingPath.toStdString();
    configuration = CalamaresPython::variantMapToPyDict( m_parent->m_configurationMap );
}


void
PythonJobInterface::setprogress( qreal progress )
{
    if ( progress >= 0 && progress <= 1 )
        m_parent->emitProgress( progress );
}


}
