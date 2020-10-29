/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2014 Kevin Kofler <kevin.kofler@chello.at>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef SETKEYBOARDLAYOUTJOB_H
#define SETKEYBOARDLAYOUTJOB_H

#include "AdditionalLayoutInfo.h"
#include "Job.h"


class SetKeyboardLayoutJob : public Calamares::Job
{
    Q_OBJECT
public:
    SetKeyboardLayoutJob( const QString& model,
                          const QString& layout,
                          const QString& variant,
                          const AdditionalLayoutInfo& additionaLayoutInfo,
                          const QString& xOrgConfFileName,
                          const QString& convertedKeymapPath,
                          bool writeEtcDefaultKeyboard );

    QString prettyName() const override;
    Calamares::JobResult exec() override;

private:
    QString findConvertedKeymap( const QString& convertedKeymapPath ) const;
    QString findLegacyKeymap() const;
    bool writeVConsoleData( const QString& vconsoleConfPath, const QString& convertedKeymapPath ) const;
    bool writeX11Data( const QString& keyboardConfPath ) const;
    bool writeDefaultKeyboardData( const QString& defaultKeyboardPath ) const;

    QString m_model;
    QString m_layout;
    QString m_variant;
    AdditionalLayoutInfo m_additionalLayoutInfo;
    QString m_xOrgConfFileName;
    QString m_convertedKeymapPath;
    const bool m_writeEtcDefaultKeyboard;
};

#endif /* SETKEYBOARDLAYOUTJOB_H */
