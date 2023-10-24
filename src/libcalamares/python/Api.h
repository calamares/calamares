/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_PYTHON_API_H
#define CALAMARES_PYTHON_API_H

/** @file
 *
 * Contains the API that Python modules use from the Python code
 * of that module. This is the C++ side that implements the functions
 * imported by the Python code as `import libcalamares`.
 */

#include "python/Pybind11Helpers.h"

#include <string>

namespace Calamares
{

class GlobalStorage;
class PythonJob;

namespace Python __attribute__( ( visibility( "hidden" ) ) )
{
    std::string obscure( const std::string& string );

    void debug( const std::string& s );
    void warning( const std::string& s );
    // void warn( const std::string& s) is an alias of warning() defined at the Python level
    void error( const std::string& s );

    Dictionary load_yaml( const std::string& path );

    List gettext_languages();
    Object gettext_path();

    int target_env_call( const List& args, const std::string& input, int timeout );
    int check_target_env_call( const List& args, const std::string& input, int timeout );
    std::string check_target_env_output( const List& args, const std::string& input, int timeout );

    int target_env_process_output( const List& args, const Object& callback, const std::string& input, int timeout );
    int host_env_process_output( const List& args, const Object& callback, const std::string& input, int timeout );

    int mount( const std::string& device_path,
               const std::string& mount_point,
               const std::string& filesystem_name,
               const std::string& options );

    class Job;

    /** @brief Proxy class in Python for the Calamares Job class
     *
     * This is available as libcalamares.job in Python code.
     */
    class JobProxy
    {
    public:
        explicit JobProxy( Calamares::Python::Job* parent );

        std::string prettyName;
        std::string workingPath;
        std::string moduleName;

        Dictionary configuration;

        void setprogress( qreal progress );

    private:
        Calamares::Python::Job* m_parent;
    };

    class GlobalStorageProxy
    {
    public:
        explicit GlobalStorageProxy( Calamares::GlobalStorage* gs );

        bool contains( const std::string& key ) const;
        int count() const;
        void insert( const std::string& key, const Object& value );
        List keys() const;
        int remove( const std::string& key );
        Object value( const std::string& key ) const;

        // This is a helper for scripts that do not go through
        // the JobQueue (i.e. the module testpython script),
        // which allocate their own (singleton) GlobalStorage.
        static Calamares::GlobalStorage* globalStorageInstance() { return s_gs_instance; }

    private:
        Calamares::GlobalStorage* m_gs;
        static Calamares::GlobalStorage* s_gs_instance;  // See globalStorageInstance()
    };


}  // namespace Python
}  // namespace Calamares

#endif
