/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

    int target_env_call( const QString& command, const QString& stdin = QString(), int timeout = 0 ) const;

    int target_env_call( const QStringList& args, const QString& stdin = QString(), int timeout = 0 ) const;

    int check_target_env_call( const QString& command, const QString& stdin = QString(), int timeout = 0 ) const;

    int check_target_env_call( const QStringList& args, const QString& stdin = QString(), int timeout = 0 ) const;

    QString check_target_env_output( const QString& command, const QString& stdin = QString(), int timeout = 0 ) const;

    QString check_target_env_output( const QStringList& args, const QString& stdin = QString(), int timeout = 0 ) const;

    QString obscure( const QString& string ) const;

private:
    inline int _handle_check_target_env_call_error( int ec, const QString& cmd ) const;

    PythonQtObjectPtr m_exceptionCxt;
};

#endif  // PYTHONQTUTILSWRAPPER_H
