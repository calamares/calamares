/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2014, Kevin Kofler <kevin.kofler@chello.at>
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

#ifndef SETKEYBOARDLAYOUTJOB_H
#define SETKEYBOARDLAYOUTJOB_H

#include <Job.h>


class SetKeyboardLayoutJob : public Calamares::Job
{
    Q_OBJECT
public:
    SetKeyboardLayoutJob( const QString& model,
                          const QString& layout,
                          const QString& variant,
                          const QString& xOrgConfFileName,
                          const QString& convertedKeymapPath,
                          bool writeEtcDefaultKeyboard );

    QString prettyName() const override;
    Calamares::JobResult exec() override;

private:
    QString findConvertedKeymap( const QString& convertedKeymapPath ) const;
    QString findLegacyKeymap() const;
    bool writeVConsoleData( const QString& vconsoleConfPath,
                            const QString& convertedKeymapPath ) const;
    bool writeX11Data( const QString& keyboardConfPath ) const;
    bool writeDefaultKeyboardData( const QString& defaultKeyboardPath ) const;

    QString m_model;
    QString m_layout;
    QString m_variant;
    QString m_xOrgConfFileName;
    QString m_convertedKeymapPath;
    const bool m_writeEtcDefaultKeyboard;
};

#endif /* SETKEYBOARDLAYOUTJOB_H */
