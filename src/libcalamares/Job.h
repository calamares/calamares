/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARES_JOB_H
#define CALAMARES_JOB_H

#include "DllMacro.h"
#include "Typedefs.h"

#include <QObject>

namespace Calamares {

class DLLEXPORT JobResult
{
public:
    JobResult( const JobResult& rhs ) = delete;
    JobResult( JobResult&& rhs );

    virtual ~JobResult() {}

    virtual operator bool() const;

    virtual QString message() const;
    virtual void setMessage( const QString& message );

    virtual QString details() const;
    virtual void setDetails( const QString& details );

    static JobResult ok();

    static JobResult error( const QString& message, const QString& details = QString() );

protected:
    explicit JobResult( bool ok, const QString& message, const QString& details );

private:
    bool m_ok;
    QString m_message;
    QString m_details;
};

class DLLEXPORT Job : public QObject
{
    Q_OBJECT
public:
    explicit Job( QObject* parent = nullptr );
    virtual ~Job();

    virtual QString prettyName() const = 0;
    virtual QString prettyDescription() const;
    virtual QString prettyStatusMessage() const;
    virtual JobResult exec() = 0;
signals:
    void progress( qreal percent );
};

} // namespace Calamares

#endif // CALAMARES_JOB_H
