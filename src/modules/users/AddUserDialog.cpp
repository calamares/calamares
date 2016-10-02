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
#include <QRegExpValidator>

//#include "avatardialog.h"
#include "AddUserDialog.h"
#include "utils/CalamaresUtilsGui.h"
#include <pwquality.h>

UsernameValidator::UsernameValidator(QRegExp exp): QRegExpValidator(exp),  m_badNames()
{
  m_badNames 
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
}


void UsernameValidator::fixup(QString& input) const
{
    input = input.trimmed();
    input = input.toLower();
}

QValidator::State UsernameValidator::validate(QString& input, int& pos) const
{
    QValidator::State state = QRegExpValidator::validate(input, pos);
    if (state == QRegExpValidator::Invalid) {
        QChar lastchar = input.at(pos-1);
        if (lastchar.isUpper()) {
            emit invalidSymbolEntered(tr("Usernames can not contain uppercase letters."));
        } else if (lastchar.isSpace()) {
            emit invalidSymbolEntered(tr("Usernames can not contain spaces."));
        } else {
            //emit invalidSymbolEntered(tr("%1 is not a valid character", lastchar));
        }
        fixup(input);
        state = QRegExpValidator::validate(input, pos);
    }
    if (m_badNames.contains(input)) {
      //emit invalidSymbolEntered(tr("%1 is already used by a system user. Please choose another name.", input));
      return QValidator::Intermediate;
    }
    if (state == QValidator::Acceptable) {
      emit textIsValidAgain();
    }
    return state;
}



AddUserDialog::AddUserDialog(QWidget* parent): QDialog(parent)
{
    ui.setupUi(this);

    ui.passLine->setEchoMode(QLineEdit::Password);
    ui.confirmPassLine->setEchoMode(QLineEdit::Password);
    ui.labelUsernameError->setFont( QFont("Arial", 10) );

    //don't use character classes, Qt is unicode aware, but useradd is not
    QRegExp validUsername("[a-z_][a-z0-9\\-_]{0,31}");  //this is the regular expression which is accepted by the useradd command
    UsernameValidator *m_validator = new UsernameValidator(validUsername);
    ui.userNameLine->setValidator(m_validator);

    connect(ui.userNameLine, &QLineEdit::textEdited, this,
            &AddUserDialog::validateUsername);

    //ui.userDetails->setIcon(KIcon("view-list-details"));

//    ui.avatar->setIconSize(QSize(48, 48));
//    ui.avatar->setIcon(QPixmap(":/Images/images/own.png"));

//    m_avatarDialog = new AvatarDialog(parent->parentWidget());
//    m_avatarDialog->hide();

//    if (number == 0) {
//        autoLogin = true;
//        useRootPw = true; // set this to true for the first user, so that he can manually set a password for root
//        ui.autoLoginCheckBox->setChecked(true);
//        ui.rootUsesUserPwCheckBox->setChecked(false);
//        ui.removeUser->setVisible(false);
//    } else {
//        autoLogin = false;
//        ui.rootUsesUserPwCheckBox->setVisible(false);
//        ui.extWidget->hide();
//        ui.rootPwWidget->hide();
//    }


    //m_messageWidget = new KMessageWidget(this);
    //m_messageWidget->hide();
    //m_messageWidget->setMessageType(KMessageWidget::Warning);
    //m_messageWidget->setWordWrap(true);
    //ui.userNameLayout->insertWidget(0, m_messageWidget);

    passwordsMatch = passwordsEmpty = true;
    connect(ui.passLine, &QLineEdit::textChanged, this, &AddUserDialog::passwordChanged);
    connect(ui.confirmPassLine, &QLineEdit::textChanged, this, &AddUserDialog::passwordChanged);
//    connect(ui.passLine, SIGNAL(textChanged(QString)), this, SLOT(updatePasswordStrengthBar(QString)));

    connect(ui.userDetails, &QPushButton::clicked, this, &AddUserDialog::showDetails);

//    connect(ui.nameLine, SIGNAL(textChanged(QString)), this, SLOT(testFields()));

//    connect(ui.avatar, SIGNAL(clicked(bool)), this, SLOT(avatarClicked()));
//    connect(ui.autoLoginCheckBox, SIGNAL(toggled(bool)), this, SLOT(autoLoginToggled()));

    ui.dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(ui.dialogButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui.dialogButtonBox, SIGNAL(rejected()), this, SLOT(reject()));

    //connect(m_avatarDialog, SIGNAL(setAvatar(QString)), this, SLOT(setAvatar(QString)));
}

AddUserDialog::~AddUserDialog() {}

void AddUserDialog::validateUsername(const QString& username) {
    QRegExp rx( USERNAME_RX );
    QRegExpValidator val( rx );
    int pos = -1;

    if ( username.isEmpty() )
    {
        ui.labelUsernameError->clear();
        //ui->labelUsername->clear();
        validUsername = false;
    }
    else if ( username.length() > USERNAME_MAX_LENGTH )
    {
        ui.iconUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                     CalamaresUtils::Original,
                                                                     ui.iconUsername->size() ) );
        ui.labelUsernameError->setText(
            tr( "Your username is too long." ) );

        validUsername = false;
    }
    else if ( val.validate( (QString &)username, pos ) == QValidator::Invalid )
    {
        ui.iconUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                     CalamaresUtils::Original,
                                                                     ui.iconUsername->size() ) );
        ui.labelUsernameError->setText(
            tr( "Your username contains invalid characters. Only lowercase letters and numbers are allowed." ) );

        validUsername = false;
    }
    else {
        ui.iconUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
                                                                     CalamaresUtils::Original,
                                                                     ui.iconUsername->size() ) );
        ui.labelUsernameError->setText("Username valid.");
        validUsername = true;
    }

    login = username;
    updateValidityUi();
}

void AddUserDialog::passwordChanged() {
    password = ui.passLine->text();
    passwordsMatch = (password == ui.confirmPassLine->text());
    passwordsEmpty = (password.length() == 0);

    if (passwordsMatch && !passwordsEmpty) {
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

void AddUserDialog::showDetails()
{
    ui.extWidget->setVisible(!ui.extWidget->isVisible());
}

void AddUserDialog::updateValidityUi()
{
    if (validUsername && !passwordsEmpty && passwordsMatch) {
        ui.dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    } else {
        ui.dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

//    // user password
//    if ((ui.passLine->text().isEmpty()) && (ui.confirmPassLine->text().isEmpty())) {
//        passwordsEmpty = true;
//    } else {
//        if ((ui.passLine->text() == ui.confirmPassLine->text())) {
//            ui.confirmPwCheck->setPixmap(QPixmap(":Images/images/green-check.png"));
//            password = ui.passLine->text();
//            passwordsMatch = true;
//        } else {
//            ui.confirmPwCheck->setPixmap(QPixmap());
//            passwordsMatch = false;
//        }
//        passwordsEmpty = false;
//    }



//    login = ui.userNameLine->text();
//    name = ui.nameLine->text();
//    autoLogin = ui.autoLoginCheckBox->isChecked();
//}

void AddUserDialog::avatarClicked()
{
    //m_avatarDialog->show();
    //m_avatarDialog->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, m_avatarDialog->size(), qApp->desktop()->availableGeometry()));
}

void AddUserDialog::updatePasswordStrengthBar(const QString& newpass_)
{
    // This code uses libpwquality to check the password's strength each time it changes and uses a QProgressBar to indicate how strong it is
    // TODO: Maybe abstract libpwquality away, writing a wrapper with a Qtish API?
    QByteArray byteArray = newpass_.toUtf8();
    const char* cPassString = byteArray.constData();
    void* auxerror;
    //int pwstrength = pwquality_check(pwquality_default_settings(), cPassString, NULL, NULL, &auxerror);
    int pwstrength = 0;
    if (pwstrength < 0) {
        //const char* cAuxErrorInfo =  pwquality_strerror(NULL, 0, pwstrength, auxerror);
        ui.passStrengthProgBar->reset();
        ui.pwERRORLabel->setText(QString::fromUtf8("error"));  // cAuxErrorInfo.
        ui.pwERRORLabel->show();
    } else {
        ui.passStrengthProgBar->setValue(pwstrength);
        ui.pwERRORLabel->hide();
    }
}


void AddUserDialog::showUsernameWarning(const QString& warning_)
{
//    if (m_messageWidget->isVisible()) {
//        m_messageWidget->hide(); //else the GUI will look awkward when the text changes
//    }
//    m_messageWidget->setText(warning_);
//    m_messageWidget->animatedShow();
}

void AddUserDialog::hideUsernameWarning()
{
//    if(m_messageWidget->isVisible()) {
//        m_messageWidget->animatedHide();
//    }
}

void AddUserDialog::autoLoginToggled()
{
//    autoLogin = ui.autoLoginCheckBox->isChecked();
//    if (autoLogin)
//        emit autoLoginToggled(number);
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
