/*
 * Copyright (c) 2008, 2009  Dario Freddi <drf@chakra-project.org>
 *               2010        Drake Justice <djustice@chakra-project.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#ifndef USERCREATIONPAGE_H
#define USERCREATIONPAGE_H

#include "../abstractpage.h"
#include "../widgets/userwidget.h"

#include "ui_usercreation.h"

class InstallationHandler;

class UserCreationPage : public AbstractPage
{
    Q_OBJECT

public:
    UserCreationPage(QWidget *parent = 0);
    virtual ~UserCreationPage();

private slots:
    virtual void createWidget();
    virtual void aboutToGoToNext();
    virtual void aboutToGoToPrevious();

    void addUserClicked();
    void removeUserClicked(int);

    void updateAutoLogin(int);

    bool validate();

    void validateNext();

    void updateScrollView();
    void updateUserNumbers();

private:
    Ui::UserCreation ui;
    InstallationHandler *m_handler;
    QList<UserWidget*> m_userList;
};

#endif /*USERCREATIONPAGE_H*/
