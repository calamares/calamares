/*******************************************************************************
 * Copyright (c) 2016-2017, Kyle Robbertze (AIMS, South Africa)
 *
 * This project is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * It is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this project. If not, see <http://www.gnu.org/licenses/>.
 *
 *    Description:  Module for installing select packages in the installed
 *                  system
 *
 *        Created:  06/12/2016 07:17:14
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), kyle@aims.ac.za
 *******************************************************************************/

#ifndef EXTRAPACKAGESPAGE_H
#define EXTRAPACKAGESPAGE_H

#include "Typedefs.h"
#include <QWidget>

namespace Ui
{
class ExtraPackagesPage;
}

class ExtraPackagesPage : public QWidget
{
    Q_OBJECT

public:
    explicit ExtraPackagesPage( QWidget* parent = nullptr );

    void setUpLink( bool showHelpCentre, QString url );
    void setUpPackages( QVariantList packages );
    QString prettyStatus();
    QList<Calamares::job_ptr> createJobs( QVariantList sources );
    void checkInternet();
protected:
    void focusInEvent( QFocusEvent* e ) override;

private:
    Ui::ExtraPackagesPage* ui;
    bool stateChanging;
};

#endif // EXTRAPACKAGESPAGE_H
