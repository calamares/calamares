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

#ifndef BRANDING_H
#define BRANDING_H

#include "UiDllMacro.h"
#include "Typedefs.h"

#include <QObject>


namespace Calamares
{

class UIDLLEXPORT Branding : public QObject
{
    Q_OBJECT
public:
    static Branding* instance();

    explicit Branding( const QString& brandingFilePath,
                       QObject *parent = nullptr );

    QString descriptorPath() const;
    QString componentName() const;
    QString componentDirectory() const;


private:
    static Branding* s_instance;

    QString m_descriptorPath;
    QString m_componentName;
};

}

#endif // BRANDING_H
