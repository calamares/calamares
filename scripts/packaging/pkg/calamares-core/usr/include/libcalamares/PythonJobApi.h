/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PYTHONJOBAPI_H
#define PYTHONJOBAPI_H

#include "utils/BoostPython.h"

#include <qglobal.h>  // For qreal

namespace Calamares
{
class PythonJob;
}

namespace CalamaresPython
{

int mount( const std::string& device_path,
           const std::string& mount_point,
           const std::string& filesystem_name = std::string(),
           const std::string& options = std::string() );

int target_env_call( const std::string& command, const std::string& input = std::string(), int timeout = 0 );

int target_env_call( const boost::python::list& args, const std::string& input = std::string(), int timeout = 0 );

int check_target_env_call( const std::string& command, const std::string& input = std::string(), int timeout = 0 );

int check_target_env_call( const boost::python::list& args, const std::string& input = std::string(), int timeout = 0 );

std::string
check_target_env_output( const std::string& command, const std::string& input = std::string(), int timeout = 0 );

std::string
check_target_env_output( const boost::python::list& args, const std::string& input = std::string(), int timeout = 0 );

int target_env_process_output( const boost::python::list& args,
                               const boost::python::object& callback = boost::python::object(),
                               const std::string& input = std::string(),
                               int timeout = 0 );

int host_env_process_output( const boost::python::list& args,
                             const boost::python::object& callback = boost::python::object(),
                             const std::string& input = std::string(),
                             int timeout = 0 );

std::string obscure( const std::string& string );

boost::python::object gettext_path();

boost::python::list gettext_languages();

void debug( const std::string& s );
void warning( const std::string& s );
void error( const std::string& s );

/** @brief Loads YAML and returns (nested) dicts representing it
 *
 */
boost::python::dict load_yaml( const std::string& path );

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

}  // namespace CalamaresPython

#endif  // PYTHONJOBAPI_H
