/*
 * Copyright (c) 2008 - 2009  Dario Freddi <drf@chakra-project.org>
 *               2010 - 2012  Drake Justice <djustice@chakra-project.com>
 *                      2013  Manuel Tortosa <manutortosa@chakra-project.org>     
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#include <functional>

#include <QDebug>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QRegExpValidator>

//#include "avatardialog.h"
#include "AddUserDialog.h"
#include "utils/CalamaresUtilsGui.h"
#include <pwquality.h>

AddUserDialog::AddUserDialog(const QStringList& existingUsers, const QStringList& shells, bool haveRootPassword, QWidget* parent)
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

    //don't use character classes, Qt is unicode aware, but useradd is not
    connect(ui.userNameLine, &QLineEdit::textEdited, this,
            &AddUserDialog::validateUsername);

    m_passwordsMatch = m_passwordsEmpty = true;
    connect(ui.passLine, &QLineEdit::textChanged, this, &AddUserDialog::passwordChanged);
    connect(ui.confirmPassLine, &QLineEdit::textChanged, this, &AddUserDialog::passwordChanged);

    if (!haveRootPassword) {
        ui.rootUsesUserPwCheckBox->setEnabled(false);
    }

    connect(ui.selectImageButton, &QPushButton::clicked, this, &AddUserDialog::avatarClicked);

    ui.dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(ui.dialogButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui.dialogButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

AddUserDialog::~AddUserDialog() {}

void AddUserDialog::accept() {
    login = ui.userNameLine->text();
    password = ui.passLine->text();
    shell = ui.loginShellSelection->currentText();

    autoLogin = ui.autoLoginCheckBox->isEnabled();
    useUserPw = ui.rootUsesUserPwCheckBox->isEnabled();

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

void AddUserDialog::setAvatar(const QString& avatar_)
{
    //if (avatar_ != "z") {
    //    ui.avatar->setIcon(KIcon(avatar_));
    //    avatar = avatar_;
    //}
}

void AddUserDialog::updateValidityUi()
{
    if (m_validUsername && !m_passwordsEmpty && m_passwordsMatch) {
        ui.dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    } else {
        ui.dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void AddUserDialog::avatarClicked()
{
    QFileDialog dlg( this );
    dlg.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dlg.setViewMode(QFileDialog::Detail);
    dlg.setDirectory("/home");

    if ( dlg.exec() == QDialog::Accepted ) {
        avatarFile = dlg.selectedFiles().at(0);
        ui.avatarFileLine->setText(avatarFile);
    }
}

void AddUserDialog::setLogin(const QString& login_)
{
    ui.userNameLine->setText(login_);
    login = login_;
}

void AddUserDialog::setName(const QString& name_)
{
    ui.nameLine->setText(name_);
    name  = name_;
}

void AddUserDialog::setPassword(const QString& pass_)
{
    ui.passLine->setText(pass_);
    ui.confirmPassLine->setText(pass_);
    password = pass_;
}

void AddUserDialog::setAutoLogin(const QString& autologin_) {
    if (autologin_.toInt() > 0) {
        ui.autoLoginCheckBox->setCheckState(Qt::Checked);
        autoLogin = true;
    } else {
        ui.autoLoginCheckBox->setCheckState(Qt::Unchecked);
        autoLogin = false;
    }
}

#include "AddUserDialog.moc"
