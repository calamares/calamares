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

class KeyBoardPreview;

class KeyboardPage : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardPage( QWidget* parent = nullptr );
    ~KeyboardPage() override;

    void init();

    QString prettyStatus() const;

    Calamares::JobList
    createJobs( const QString& xOrgConfFileName, const QString& convertedKeymapPath, bool writeEtcDefaultKeyboard );

    void onActivate();
    void finalize();

protected slots:
    void onListLayoutCurrentItemChanged( const QModelIndex& current, const QModelIndex& previous );
    void onListVariantCurrentItemChanged( QListWidgetItem* current, QListWidgetItem* previous );

private:
    /// Guess a layout based on the split-apart locale
    void guessLayout( const QStringList& langParts );
    void updateVariants( const QPersistentModelIndex& currentItem, QString currentVariant = QString() );

    Ui::Page_Keyboard* ui;
    KeyBoardPreview* m_keyboardPreview;
    int m_defaultIndex;
    QMap< QString, QString > m_models;

    QString m_selectedLayout;
    QString m_selectedVariant;
    QTimer m_setxkbmapTimer;
};

#endif  // KEYBOARDPAGE_H
