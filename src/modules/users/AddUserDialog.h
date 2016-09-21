/*
 * Copyright (c) 2008 - 2009  Dario Freddi <drf@chakra-project.org>
 *               2010 - 2011  Drake Justice <djustice@chakra-project.com>
 *                      2013  Manuel tortosa <manutortosa@chakra-project.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include "ui_adduserdialog.h"

#include <QLineEdit>
#include <QValidator>
#include <QRegExp>

class UsernameValidator: public QRegExpValidator
{
    Q_OBJECT
  
public:
    UsernameValidator(QRegExp exp);
    void fixup ( QString & input ) const ;
    QValidator::State validate ( QString & input, int & pos ) const;
    
signals:
    void invalidSymbolEntered(const QString &) const; // const is needed, because the signal is emitted in a const method
    void textIsValidAgain() const;

private:
    QStringList m_badNames;
};

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    AddUserDialog(QWidget *parent = 0);
    virtual ~AddUserDialog();

    QLineEdit *loginLine;
    QString login;
    QString password;
    QString avatar;
    QString name;

    bool autoLogin;
    bool useUserPw;
    bool passwordsMatch;
    bool passwordsEmpty;

    bool isUserNameValid();

public slots:
    void setLogin(const QString&);
    void setPassword(const QString&);
    void setAvatar(const QString&);
    void setName(const QString&);
    void setAutoLogin(const QString&);
    void showUsernameWarning(const QString&);
    void hideUsernameWarning();

signals:
    void addUserClicked();
    void autoLoginToggled(int);

private slots:
    void showDetails();

    void avatarClicked();
    void autoLoginToggled();

    void testFields();
    void updatePasswordStrengthBar(const QString&);

private:
    Ui::AddUserDialog ui;
    //AvatarDialog *m_avatarDialog;
    //KMessageWidget *m_messageWidget;
    UsernameValidator *m_validator;
};

#endif /* ADDUSERDIALOG_H */
