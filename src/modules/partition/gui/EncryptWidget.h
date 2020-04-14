/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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


#ifndef ENCRYPTWIDGET_H
#define ENCRYPTWIDGET_H

#include <QWidget>

namespace Ui
{
    class EncryptWidget;
}

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

    void reset();

    Encryption state() const;
    void setText( const QString& text );

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
};

#endif  // ENCRYPTWIDGET_H
