/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */


#ifndef ENCRYPTWIDGET_H
#define ENCRYPTWIDGET_H

#include <QWidget>

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

    void reset( bool checkVisible = true );

    Encryption state() const;
    void setText( const QString& text );

    /**
     * @brief setFilesystem sets the filesystem name used for password validation
     * @param fs A QString containing the name of the filesystem
     */
    void setFilesystem( const QString& fs );

    QString passphrase() const;

    void retranslate();

signals:
    void stateChanged( Encryption );

private:
    void updateState();
    void onPassphraseEdited();
    void onCheckBoxStateChanged( int checked );

    Ui::EncryptWidget* m_ui;
    Encryption m_state;

    QString m_filesystem;
};

#endif  // ENCRYPTWIDGET_H
