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

#ifndef PAGEPLUGIN_H
#define PAGEPLUGIN_H

#include <QObject>

#include "../UiDllMacro.h"

namespace Calamares
{

class UIDLLEXPORT ViewStep : public QObject
{
    Q_OBJECT
public:
    explicit ViewStep( QObject *parent = nullptr );
    virtual ~ViewStep();

    virtual QString prettyName() = 0;

    //TODO: we might want to make this a QSharedPointer
    virtual QWidget* widget() = 0;

    virtual void next() = 0;
    virtual void back() = 0;

    virtual bool isNextEnabled() = 0;

    virtual bool isAtBeginning() = 0;
    virtual bool isAtEnd() = 0;

signals:
    void nextStatusChanged( bool status );
    void done();

};

}

Q_DECLARE_INTERFACE( Calamares::ViewStep, "calamares.ViewModule/1.0" )

#endif // PAGEPLUGIN_H
