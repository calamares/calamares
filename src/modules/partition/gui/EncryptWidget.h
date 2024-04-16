/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2023 Evan James <dalto@fastmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */


#ifndef ENCRYPTWIDGET_H
#define ENCRYPTWIDGET_H

#include <QWidget>

#include <kpmcore/fs/filesystem.h>

namespace Ui
{
class EncryptWidget;
}  // namespace Ui

class EncryptWidget : public QWidget
{
    Q_OBJECT

public:
    enum class Encryption : unsigned short
    {
        Disabled = 0,
        Unconfirmed,
        Confirmed
    };

    explicit EncryptWidget( QWidget* parent = nullptr );

    void setEncryptionCheckbox( bool preCheckEncrypt = false);
    void reset( bool checkVisible = true );

    bool isEncryptionCheckboxChecked();
    Encryption state() const;
    void setText( const QString& text );

    /**
     * @brief setFilesystem sets the filesystem name used for password validation
     * @param fs A QString containing the name of the filesystem
     */
    void setFilesystem( const FileSystem::Type fs );

    QString passphrase() const;

    void retranslate();

signals:
    void stateChanged( Encryption );

private:
    void updateState( const bool notify = true );
    void onPassphraseEdited();
    void onCheckBoxStateChanged( int checked );

    Ui::EncryptWidget* m_ui;
    Encryption m_state;

    FileSystem::Type m_filesystem;
};

#endif  // ENCRYPTWIDGET_H
