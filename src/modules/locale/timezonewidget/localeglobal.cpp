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

#include "localeglobal.h"


//###
//### Private variables
//###

QHash<QString, QHash<QString, QList<LocaleGlobal::Locale> > > LocaleGlobal::locales;
QHash<QString, QList<LocaleGlobal::Location> > LocaleGlobal::locations;


//###
//### Public methods
//###


void LocaleGlobal::init() {
    // TODO: Error handling
    initLocales();
    initLocations();
}



QHash<QString, QHash<QString, QList<LocaleGlobal::Locale> > > LocaleGlobal::getLocales() {
    return locales;
}



QHash<QString, QList<LocaleGlobal::Location> > LocaleGlobal::getLocations() {
    return locations;
}



QMap<QString, LocaleGlobal::KeyboardInfo> LocaleGlobal::getKeyboardLayouts() {
    return parseKeyboardLayouts(XKB_FILE);
}


QMap<QString, QString> LocaleGlobal::getKeyboardModels() {
    return parseKeyboardModels(XKB_FILE);
}



//###
//### Private methods
//###


void LocaleGlobal::initLocales() {
    locales.clear();

    QStringList files = QDir(LOCALESDIR).entryList(QDir::Files, QDir::Name);

    for (int i = 0; i < files.size(); ++i) {
        QString filename = files.at(i);
        QFile file(QString(LOCALESDIR) + "/" + filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            continue;

        QTextStream in(&file);
        QString commentChar = "%";
        Locale locale;
        QString lang, territory;

        locale.locale = filename;

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            QStringList split = line.split(commentChar, QString::KeepEmptyParts).first().split(QRegExp(" (?=[^\"]*(\"[^\"]*\"[^\"]*)*$)"), QString::SkipEmptyParts);

            if (split.size() < 2)
                continue;

            QString sub1 = QString(split.at(0)).remove("\"");
            QString sub2 = QString(split.at(1)).remove("\"");

            if (sub1 == "comment_char")
                commentChar = sub2;
            else if (sub1 == "title")
                locale.description = sub2;
            else if (sub1 == "territory")
                territory= sub2;
            else if (sub1 == "language")
                lang = sub2;
        }

        if (lang.isEmpty() || territory.isEmpty())
            continue;

        locales[lang][territory].append(locale);
    }
}



void LocaleGlobal::initLocations() {
    locations.clear();

    QFile file(TZ_DATA_FILE);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed().split('#', QString::KeepEmptyParts).first().trimmed();
        if (line.isEmpty())
            continue;

        QStringList list = line.split(QRegExp("[\t ]"), QString::SkipEmptyParts);
        if (list.size() < 3)
            continue;

        Location location;
        QStringList timezone = list.at(2).split('/', QString::SkipEmptyParts);
        int cooSplitPos = QString(list.at(1)).remove(0, 1).indexOf(QRegExp("[-+]")) + 1;

        if (timezone.size() < 2)
            continue;

        location.region = timezone.first();
        location.zone = timezone.last();
        location.latitude = getRightGeoLocation(list.at(1).mid(0, cooSplitPos));
        location.longitude = getRightGeoLocation(list.at(1).mid(cooSplitPos));

        locations[location.region].append(location);
    }
}



double LocaleGlobal::getRightGeoLocation(QString str) {
    double sign = 1, num = 0.00;

    // Determind sign
    if (str.startsWith('-')) {
        sign = -1;
        str.remove(0, 1);
    }
    else if (str.startsWith('+')) {
        str.remove(0, 1);
    }


    if (str.length() == 4 || str.length() == 6)
        num = str.mid(0, 2).toDouble() + str.mid(2, 2).toDouble() / 60;
    else if (str.length() == 5 || str.length() == 7)
        num = str.mid(0, 3).toDouble() + str.mid(3, 2).toDouble() / 60;

    return sign * num;
}



//### Source by Georg Grabler <ggrabler@gmail.com> ###//
QMap<QString, QString> LocaleGlobal::parseKeyboardModels(QString filepath)
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



QMap< QString, LocaleGlobal::KeyboardInfo > LocaleGlobal::parseKeyboardLayouts(QString filepath)
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
