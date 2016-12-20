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

#ifndef LOCALECONFIGURATION_H
#define LOCALECONFIGURATION_H

#include <QString>
#include <QMap>

class LocaleConfiguration
{
public:
    explicit LocaleConfiguration();

    static LocaleConfiguration createDefault();
    static LocaleConfiguration fromLanguageAndLocation( const QString& language,
                                                        const QStringList& availableLocales,
                                                        const QString& countryCode );

    bool isEmpty();

    // These become all uppercase in locale.conf, but we keep them lowercase here to
    // avoid confusion with locale.h.
    QString lang, lc_numeric, lc_time, lc_monetary, lc_paper, lc_name, lc_address,
            lc_telephone, lc_measurement, lc_identification;
    QString myLanguageLocaleBcp47;
    QMap< QString, QString > toMap();
};

#endif // LOCALECONFIGURATION_H
