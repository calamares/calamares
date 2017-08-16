/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
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

int target_env_call( const std::string& command,
                 const std::string& stdin = std::string(),
                 int timeout = 0 );

int target_env_call( const boost::python::list& args,
                 const std::string& stdin = std::string(),
                 int timeout = 0 );

int check_target_env_call( const std::string& command,
                       const std::string& stdin = std::string(),
                       int timeout = 0 );

int check_target_env_call( const boost::python::list& args,
                       const std::string& stdin = std::string(),
                       int timeout = 0 );

std::string check_target_env_output( const std::string& command,
                                 const std::string& stdin = std::string(),
                                 int timeout = 0 );

std::string check_target_env_output( const boost::python::list& args,
                                 const std::string& stdin = std::string(),
                                 int timeout = 0 );

std::string obscure( const std::string& string );

boost::python::object gettext_path();

boost::python::list gettext_languages();

void debug( const std::string& s );

inline int _handle_check_target_env_call_error( int ec, const QString& cmd );

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
