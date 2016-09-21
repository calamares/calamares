/*
 * Copyright (c) 2008, 2009  Dario Freddi <drf@chakra-project.org>
 *               2009        Lukas Appelhans <l.appelhans@gmx.de>
 *               2010        Drake Justice <djustice.kde@gmail.com>
 *               2013        Manuel Tortosa <manutorotsa@chalra-project.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#include <QTimer>
#include <QSet>
#include <QDebug>

#include <KIcon>
#include <KMessageBox>
#include <KDialog>

#include <config-tribe.h>

#include "../installationhandler.h"
#include "usercreationpage.h"


UserCreationPage::UserCreationPage(QWidget *parent)
        : AbstractPage(parent),
        m_handler(InstallationHandler::instance())
{
    ui.setupUi(this);
    ui.addUser->setIcon(KIcon("list-add"));

    ui.hostname->setText("chakra-pc");

    connect(ui.addUser, SIGNAL(clicked(bool)), this, SLOT(addUserClicked()));

    ui.scrollArea->setWidgetResizable(true);

    UserWidget *f = new UserWidget(0, this);
    m_userList.append(f);
    ui.verticalLayout->insertWidget(0, f);
    connect(f, SIGNAL(removeUserClicked(int)), this, SLOT(removeUserClicked(int)));
    connect(f, SIGNAL(autoLoginToggled(int)), this, SLOT(updateAutoLogin(int)));

    if (!m_handler->userLoginList().isEmpty()) {
      // TODO: refactor this; check if it is really necessary at all
      foreach (QString login, m_handler->userLoginList()) {
	  int i = m_userList.count() - 1;
	  QString password = m_handler->userPasswordList().at(i);
	  QString rootpassword = m_handler->userPasswordList().last();
	  QString autologin = m_handler->userAutoLoginList().at(i);
	  QString name = m_handler->userNameList().at(i);
	  QString avatar = m_handler->userAvatarList().at(i);

	  QString userootpw = "0";
	  if (password == rootpassword)
	      userootpw = "1";

	  m_userList.at(i)->setLogin(login);
	  m_userList.at(i)->setPassword(password);
	  m_userList.at(i)->setUseRootPassword(userootpw);
	  m_userList.at(i)->setRootPassword(rootpassword);
	  m_userList.at(i)->setAutoLogin(autologin);
	  m_userList.at(i)->setName(name);
	  m_userList.at(i)->setAvatar(avatar);

	  if (m_handler->userLoginList().count() > m_userList.count())
	      addUserClicked();
      }

        ui.hostname->setText(m_handler->hostname());
    }

    /*
     * The loginLine widget needs to have its focus set here instead of in UserWidget() (which is where the widget resides)
     * because widgets get focus when they are placed on screen. Therefore if you want to manually set a widget's focus,
     * you must set it after all the widgets are placed on screen.
     *
     * There *might* be a race condition here and in UserWidget() where UserWidget()->loginLine might not get set in time,
     * so check if the pointer is valid (ie. not NULL) before setting the widget's focus!
     */
    if(f->loginLine) {
        f->loginLine->setFocus();
    }
}

UserCreationPage::~UserCreationPage()
{
}

void UserCreationPage::createWidget()
{

}

void UserCreationPage::addUserClicked()
{
    UserWidget *f = new UserWidget(m_userList.count(), this);
    m_userList.append(f);
    ui.verticalLayout->insertWidget(ui.verticalLayout->count() - 1, f);
    connect(f, SIGNAL(removeUserClicked(int)), this, SLOT(removeUserClicked(int)));
    connect(f, SIGNAL(autoLoginToggled(int)), this, SLOT(updateAutoLogin(int)));

    QTimer::singleShot(300, this, SLOT(updateScrollView()));
}

void UserCreationPage::removeUserClicked(int number)
{
    m_userList.at(number)->deleteLater();
    m_userList.removeAt(number);
    updateUserNumbers();
}

void UserCreationPage::updateAutoLogin(int i)
{
    if (m_userList.at(i)->autoLogin) {
        foreach (UserWidget *user, m_userList) {
            if (user->number != i) {
                user->setAutoLogin("0");
            }
        }
    }
}

void UserCreationPage::updateUserNumbers()
{
    int n = 0;
    foreach (UserWidget *user, m_userList) {
        user->setNumber(n);
        n++;
    }
}

void UserCreationPage::updateScrollView()
{
    ui.scrollArea->ensureWidgetVisible(ui.addUser);
}

bool UserCreationPage::validate()
{
    QVector<UserAccountData> accountDataList;
    QSet<QString> userLoginNames; // used to check whether the login name is unique

    QString rootPw;

    int n = 0;
    foreach(UserWidget* user, m_userList) {
        n++;

        KDialog *dialog = new KDialog(this, Qt::FramelessWindowHint);
        dialog->setButtons(KDialog::Ok);
        dialog->setModal(true);
        bool retbool;

        if (n == 1) {
            if (user->login.isEmpty()) {
                KMessageBox::createKMessageBox(dialog, QMessageBox::Warning, i18n("You must give at least one login name."),
                                               QStringList(), QString(), &retbool, KMessageBox::Notify);
                return false;
            } else if (user->useRootPw && user->rootPasswordsEmpty) {
                KMessageBox::createKMessageBox(dialog, QMessageBox::Warning, i18n("Root Passwords cannot be empty."),
                                               QStringList(), QString(), &retbool, KMessageBox::Notify);
                return false;
            } else if (!user->rootPasswordsMatch) {
                KMessageBox::createKMessageBox(dialog, QMessageBox::Warning, i18n("Root Passwords do not match..."),
                                               QStringList(), QString(), &retbool, KMessageBox::Notify);
                return false;
            }

            if (user->useRootPw) {
                rootPw = user->rootPassword;
            } else {
                qDebug() << "using user password for root";
                rootPw = user->password;
            }
        }

        if (user->login.isEmpty()) {
            KMessageBox::createKMessageBox(dialog, QMessageBox::Warning, i18n("Login names cannot be empty."),
                                           QStringList(), QString(), &retbool, KMessageBox::Notify);
            return false;
	} else if (!user->isUserNameValid()) {
            KMessageBox::createKMessageBox(dialog, QMessageBox::Warning, i18n("Please check your username.."),
                                           QStringList(), QString(), &retbool, KMessageBox::Notify);
	  user->loginLine->setFocus();
	  return false;
	} else if (userLoginNames.contains(user->login)) {
            KMessageBox::createKMessageBox(dialog, QMessageBox::Warning, i18n("Login names must be unique."),
                                           QStringList(), QString(), &retbool, KMessageBox::Notify);
	  user->loginLine->setFocus();
	  return false;
	} else if (user->passwordsEmpty) {
            KMessageBox::createKMessageBox(dialog, QMessageBox::Warning, i18n("Passwords cannot be empty."),
                                           QStringList(), QString(), &retbool, KMessageBox::Notify);
            return false;
        } else if (!user->passwordsMatch) {
            KMessageBox::createKMessageBox(dialog, QMessageBox::Warning, i18n("Passwords do not match..."),
                                           QStringList(), QString(), &retbool, KMessageBox::Notify);
            return false;
        }

        userLoginNames.insert(user->login);
        UserAccountData data { user->login, user->password, user->avatar, user->name, QString::number(user->autoLogin) };
	accountDataList.push_back(data);
    }

    m_handler->setRootPassword(rootPw);

    m_userList.clear();

    m_handler->setUserAccountDataList(accountDataList);

    if (ui.hostname->text().isEmpty())
        ui.hostname->setText("chakra-pc");

    m_handler->setHostname(ui.hostname->text());

    return true;
}

void UserCreationPage::aboutToGoToNext()
{
    if (validate())
        emit goToNextStep();
}

void UserCreationPage::aboutToGoToPrevious()
{
    emit goToPreviousStep();
}

void UserCreationPage::validateNext()
{
    bool enable = true;
    
    emit enableNextButton(enable);
}

#include "usercreationpage.moc"
