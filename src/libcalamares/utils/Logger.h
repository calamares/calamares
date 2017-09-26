/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2014,      Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CALAMARES_LOGGER_H
#define CALAMARES_LOGGER_H

#include <QDebug>

#include "DllMacro.h"

#define LOGDEBUG 1
#define LOGINFO 2
#define LOGEXTRA 5
#define LOGVERBOSE 8

namespace Logger
{
    class DLLEXPORT CLog : public QDebug
    {
    public:
        CLog( unsigned int debugLevel = 0 );
        virtual ~CLog();

    private:
        QString m_msg;
        unsigned int m_debugLevel;
    };

    class DLLEXPORT CDebug : public CLog
    {
    public:
        CDebug( unsigned int debugLevel = LOGDEBUG ) : CLog( debugLevel )
        {
        }
        virtual ~CDebug();
    };

    DLLEXPORT void CalamaresLogHandler( QtMsgType type, const QMessageLogContext& context, const QString& msg );
    DLLEXPORT void setupLogfile();
    DLLEXPORT QString logFile();
}

#define cLog Logger::CLog
#define cDebug Logger::CDebug

#endif // CALAMARES_LOGGER_H
