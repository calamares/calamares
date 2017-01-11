/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Lisa Vitolo <shainer@chakralinux.org>
 *
 *   Portions from Tribe (Chakra Linux)
 *   by Dario Freddi, Drake Justice and Manuel Tortosa
 *   Copyright (C) 2013 Free Software Foundation, Inc.
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

#include <functional>

#include <QDialogButtonBox>
#include <QDebug>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QRegExpValidator>

#include "AddUserDialog.h"
#include "utils/CalamaresUtilsGui.h"

AddUserDialog::AddUserDialog(const QStringList& existingUsers, bool avatar, bool allowAutologin, bool checkAutologin, const QStringList& shells, bool haveRootPassword, QWidget* parent)
    : QDialog(parent),
      m_existingUsers(existingUsers)
{
      m_badUsernames
        << "root"
        << "bin"
        << "daemon"
        << "mail"
        << "ftp"
        << "http"
        << "nobody"
        << "dbus"
        << "avahi"
        << "usbmux"
        << "postgres"
        << "quassel"
        << "rtkit"
        << "git"
        << "polkitd"
        << "nm-openconnect"
        << "kdm"
        << "uuidd"
        << "ntp"
        << "mysql"
        << "clamav"
        << "postfix"
        << "lightdm";

    ui.setupUi(this);

    ui.passLine->setEchoMode(QLineEdit::Password);
    ui.confirmPassLine->setEchoMode(QLineEdit::Password);
    ui.labelUsernameError->setFont( QFont("Arial", 10) );

    ui.loginShellSelection->setAutoCompletion(true);
    ui.loginShellSelection->addItems(shells);

    connect(ui.userNameLine, &QLineEdit::textEdited, this,
            &AddUserDialog::validateUsername);

    m_passwordsMatch = m_passwordsEmpty = true;
    connect(ui.passLine, &QLineEdit::textChanged, this, &AddUserDialog::passwordChanged);
    connect(ui.confirmPassLine, &QLineEdit::textChanged, this, &AddUserDialog::passwordChanged);

    if (!haveRootPassword) {
        ui.rootUsesUserPwCheckBox->setEnabled(false);
    }

    if (!allowAutologin) {
        ui.autoLoginCheckBox->setEnabled(false);
    } else {
        ui.autoLoginCheckBox->setChecked(checkAutologin);
    }

    if (!avatar) {
        ui.avatarFileLine->setEnabled(false);
        ui.selectImageButton->setEnabled(false);
    }

    connect(ui.selectImageButton, &QPushButton::clicked, this, &AddUserDialog::avatarClicked);

    // Do not enable until valid information have been entered.
    ui.dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(ui.dialogButtonBox, &QDialogButtonBox::accepted, this, &AddUserDialog::accept);
    connect(ui.dialogButtonBox, &QDialogButtonBox::rejected, this, &AddUserDialog::reject);
}

AddUserDialog::~AddUserDialog() {}

void AddUserDialog::accept() {
    // Store all the information from the dialog in member variables.
    login = ui.userNameLine->text();
    password = ui.passLine->text();
    shell = ui.loginShellSelection->currentText();
    fullName = ui.nameLine->text();

    autoLogin = ui.autoLoginCheckBox->isChecked();
    useUserPw = ui.rootUsesUserPwCheckBox->isChecked();

    QDialog::accept();
}

void AddUserDialog::validateUsername(const QString& username) {
    QRegExp rx( USERNAME_RX );
    QRegExpValidator val( rx );
    int pos = -1;

    if ( username.isEmpty() )
    {
        ui.labelUsernameError->clear();
        ui.iconUsername->clear();
        m_validUsername = false;
    }
    else if ( username.length() > USERNAME_MAX_LENGTH )
    {
        ui.iconUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                     CalamaresUtils::Original,
                                                                     ui.iconUsername->size() ) );
        ui.labelUsernameError->setText(
            tr( "Your username is too long." ) );

        m_validUsername = false;
    }
    else if ( val.validate( (QString &)username, pos ) == QValidator::Invalid )
    {
        ui.iconUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                     CalamaresUtils::Original,
                                                                     ui.iconUsername->size() ) );
        ui.labelUsernameError->setText(
            tr( "Only lowercase letters and numbers are allowed." ) );

        m_validUsername = false;
    }
    else if ( m_existingUsers.contains(username) ) {
        ui.iconUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                     CalamaresUtils::Original,
                                                                     ui.iconUsername->size() ) );
        ui.labelUsernameError->setText(
            tr( "This username was already created." ) );

        m_validUsername = false;
    }
    else if ( m_badUsernames.contains(username) ) {
        ui.iconUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                     CalamaresUtils::Original,
                                                                     ui.iconUsername->size() ) );
        ui.labelUsernameError->setText(
            tr( "Username is already in use in the system." ) );

        m_validUsername = false;
    }
    else {
        ui.iconUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
                                                                     CalamaresUtils::Original,
                                                                     ui.iconUsername->size() ) );
        ui.labelUsernameError->setText("Username valid.");
        m_validUsername = true;
    }

    updateValidityUi();
}

void AddUserDialog::passwordChanged() {
    m_passwordsMatch = (ui.passLine->text() == ui.confirmPassLine->text());
    m_passwordsEmpty = (ui.passLine->text().length() == 0);

    if (m_passwordsMatch && !m_passwordsEmpty) {
        ui.confirmPwCheck->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
                                                                     CalamaresUtils::Original,
                                                                     ui.confirmPwCheck->size()) );
    } else {
        ui.confirmPwCheck->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                     CalamaresUtils::Original,
                                                                     ui.confirmPwCheck->size()) );
    }

    updateValidityUi();
}

void AddUserDialog::updateValidityUi()
{
    if (m_validUsername && !m_passwordsEmpty && m_passwordsMatch) {
        ui.dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    } else {
        ui.dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

// TODO: support getting the avatar from a URL too.
void AddUserDialog::avatarClicked()
{
    // Open a file dialog restricted to images.
    QFileDialog dlg( this );
    dlg.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dlg.setViewMode(QFileDialog::Detail);

    // TODO: read this from configuration as we could have a
    // preferred directory to store avatars in the live installation.
    dlg.setDirectory("/home");

    if ( dlg.exec() == QDialog::Accepted ) {
        avatarFile = dlg.selectedFiles().at(0);
        ui.avatarFileLine->setText(avatarFile);
    }
}
