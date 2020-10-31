/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2007 Free Software Foundation, Inc.
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Portions from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef KEYBOARDPAGE_H
#define KEYBOARDPAGE_H

#include "Job.h"

#include <QListWidgetItem>
#include <QTimer>
#include <QWidget>

namespace Ui
{
class Page_Keyboard;
}

class Config;
class KeyBoardPreview;

class KeyboardPage : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardPage( Config* config, QWidget* parent = nullptr );
    ~KeyboardPage() override;

    void retranslate();

private:
    Ui::Page_Keyboard* ui;
    KeyBoardPreview* m_keyboardPreview;
    Config* m_config;
};

#endif  // KEYBOARDPAGE_H
