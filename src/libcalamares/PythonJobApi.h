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

#ifndef PYTHONJOBAPI_H
#define PYTHONJOBAPI_H

#include "CalamaresVersion.h"

#include "PythonJob.h"

#undef slots
#include <boost/python/dict.hpp>

namespace CalamaresPython
{

int mount( const std::string& device_path,
           const std::string& mount_point,
           const std::string& filesystem_name = std::string(),
           const std::string& options = std::string() );

int chroot_call( const std::string& command,
                 const std::string& stdin = std::string(),
                 int timeout = 0 );

int chroot_call( const boost::python::list& args,
                 const std::string& stdin = std::string(),
                 int timeout = 0 );

int check_chroot_call( const std::string& command,
                       const std::string& stdin = std::string(),
                       int timeout = 0 );

int check_chroot_call( const boost::python::list& args,
                       const std::string& stdin = std::string(),
                       int timeout = 0 );

std::string check_chroot_output( const std::string& command,
                                 const std::string& stdin = std::string(),
                                 int timeout = 0 );

std::string check_chroot_output( const boost::python::list& args,
                                 const std::string& stdin = std::string(),
                                 int timeout = 0 );


inline int _handle_check_chroot_call_error( int ec, const QString& cmd );

void debug( const std::string& s );

class PythonJobInterface
{
public:
    explicit PythonJobInterface( Calamares::PythonJob* parent );

    std::string moduleName;
    std::string prettyName;
    std::string workingPath;

    boost::python::dict configuration;

    void setprogress( qreal progress );

private:
    Calamares::PythonJob* m_parent;
};

}

#endif // PYTHONJOBAPI_H
