/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

    bool isEmpty() const;

    QMap< QString, QString > toMap() const;
    // Note that the documentation how this works is in packages.conf
    QString toBcp47() const;

    // These become all uppercase in locale.conf, but we keep them lowercase here to
    // avoid confusion with locale.h.
    QString lang, lc_numeric, lc_time, lc_monetary, lc_paper, lc_name, lc_address,
            lc_telephone, lc_measurement, lc_identification;

    // If the user has explicitly selected language (from the dialog)
    // or numbers format, set these to avoid implicit changes to them.
    bool explicit_lang, explicit_lc;

private:
    QString myLanguageLocaleBcp47;
};

#endif // LOCALECONFIGURATION_H
