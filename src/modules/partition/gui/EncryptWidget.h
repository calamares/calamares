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


#ifndef ENCRYPTWIDGET_H
#define ENCRYPTWIDGET_H

#include "ui_EncryptWidget.h"

class EncryptWidget : public QWidget, private Ui::EncryptWidget
{
    Q_OBJECT

public:
    enum State : unsigned short
    {
        EncryptionDisabled = 0,
        EncryptionUnconfirmed,
        EncryptionConfirmed
    };

    explicit EncryptWidget( QWidget* parent = nullptr );

    void reset();

    State state() const;
    void setText( const QString& text );

    QString passphrase() const;

signals:
    void stateChanged( State );

protected:
    void changeEvent( QEvent* e );

private:
    void updateState();
    void onPassphraseEdited();
    void onCheckBoxStateChanged( int state );

    State m_state;
};

#endif // ENCRYPTWIDGET_H
