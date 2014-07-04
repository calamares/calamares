/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *
 *   Originally from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
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

#include "keyboardglobal.h"

//###
//### Public methods
//###


QMap<QString, KeyboardGlobal::KeyboardInfo> KeyboardGlobal::getKeyboardLayouts() {
    return parseKeyboardLayouts(XKB_FILE);
}


QMap<QString, QString> KeyboardGlobal::getKeyboardModels() {
    return parseKeyboardModels(XKB_FILE);
}



//###
//### Private methods
//###


//### Source by Georg Grabler <ggrabler@gmail.com> ###//
QMap<QString, QString> KeyboardGlobal::parseKeyboardModels(QString filepath)
{
    QMap<QString, QString> models;

    QFile fh(filepath);
    fh.open(QIODevice::ReadOnly);

    if (!fh.isOpen()) {
        qDebug() << "X11 Keyboard model definitions not found!";
        return models;
    }

    bool modelsFound = false;
    // read the file until the end or until we break the loop
    while (!fh.atEnd()) {
        QByteArray line = fh.readLine();

        // check if we start with the model section in the file
        if (!modelsFound && line.startsWith("! model"))
            modelsFound = true;
        else if (modelsFound && line.startsWith ("!"))
            break;
        else if (!modelsFound)
            continue;

        // here we are in the model section, otherwhise we would continue or break
        QRegExp rx;
        rx.setPattern("^\\s+(\\S+)\\s+(\\w.*)\n$");

        // insert into the model map
        if (rx.indexIn(line) != -1) {
            QString modelDesc = rx.cap(2);
            QString model = rx.cap(1);

            if (model == "pc105")
                modelDesc += "  -  " + QObject::tr("Default Keyboard Model");

            models.insert(modelDesc, model);
        }
    }

    return models;
}



QMap< QString, KeyboardGlobal::KeyboardInfo > KeyboardGlobal::parseKeyboardLayouts(QString filepath)
{
    QMap< QString, KeyboardInfo >  layouts;

    //### Get Layouts ###//

    QFile fh(filepath);
    fh.open(QIODevice::ReadOnly);

    if (!fh.isOpen()) {
        qDebug() << "X11 Keyboard layout definitions not found!";
        return layouts;
    }

    bool layoutsFound = false;
    // read the file until the end or we break the loop
    while (!fh.atEnd()) {
        QByteArray line = fh.readLine();

        // find the layout section otherwhise continue. If the layout section is at it's end, break the loop
        if (!layoutsFound && line.startsWith("! layout"))
            layoutsFound = true;
        else if (layoutsFound && line.startsWith ("!"))
            break;
        else if (!layoutsFound)
            continue;

        QRegExp rx;
        rx.setPattern("^\\s+(\\S+)\\s+(\\w.*)\n$");

        // insert into the layout map
        if (rx.indexIn(line) != -1) {
            KeyboardInfo info;
            info.description = rx.cap(2);
            info.variants.insert(QObject::tr("Default"), "");
            layouts.insert(rx.cap(1), info);
        }
    }

    fh.reset();


    //### Get Variants ###//

    bool variantsFound = false;
    // read the file until the end or until we break
    while (!fh.atEnd()) {
        QByteArray line = fh.readLine();

        // continue until we found the variant section. If found, read until the next section is found
        if (!variantsFound && line.startsWith("! variant")) {
            variantsFound = true;
            continue;
        } else if (variantsFound && line.startsWith ("!"))
            break;
        else if (!variantsFound)
            continue;

        QRegExp rx;
        rx.setPattern("^\\s+(\\S+)\\s+(\\S+): (\\w.*)\n$");

        // insert into the variants multimap, if the pattern matches
        if (rx.indexIn(line) != -1) {
            if (layouts.find(rx.cap(2)) != layouts.end()) {
                // in this case we found an entry in the multimap, and add the values to the multimap
                layouts.find(rx.cap(2)).value().variants.insert(rx.cap(3), rx.cap(1));
            } else {
                // create a new map in the multimap - the value was not found.
                KeyboardInfo info;
                info.description = rx.cap(2);
                info.variants.insert(QObject::tr("Default"), "");
                info.variants.insert(rx.cap(3), rx.cap(1));
                layouts.insert(rx.cap(2), info);
            }
        }
    }

    return layouts;
}
