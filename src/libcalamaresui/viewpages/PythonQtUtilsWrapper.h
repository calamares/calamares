/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

#ifndef PYTHONQTUTILSWRAPPER_H
#define PYTHONQTUTILSWRAPPER_H

#include <PythonQtObjectPtr.h>

#include <QObject>


/**
 * @brief The Utils class wraps around functions from CalamaresUtils to make them
 * available in the PythonQt interface.
 */
class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils( QObject* parent = nullptr );
    virtual ~Utils() {}

public slots:
    void debug( const QString& s ) const;

    int mount( const QString& device_path,
               const QString& mount_point,
               const QString& filesystem_name,
               const QString& options ) const;

    int target_env_call( const QString& command,
                         const QString& stdin = QString(),
                         int timeout = 0 ) const;

    int target_env_call( const QStringList& args,
                         const QString& stdin = QString(),
                         int timeout = 0 ) const;

    int check_target_env_call( const QString& command,
                               const QString& stdin = QString(),
                               int timeout = 0 ) const;

    int check_target_env_call( const QStringList& args,
                               const QString& stdin = QString(),
                               int timeout = 0 ) const;

    QString check_target_env_output( const QString& command,
                                     const QString& stdin = QString(),
                                     int timeout = 0 ) const;

    QString check_target_env_output( const QStringList& args,
                                     const QString& stdin = QString(),
                                     int timeout = 0 ) const;

    QString obscure( const QString& string ) const;

private:
    inline int _handle_check_target_env_call_error( int ec, const QString& cmd ) const;

    PythonQtObjectPtr m_exceptionCxt;
};

#endif // PYTHONQTUTILSWRAPPER_H
