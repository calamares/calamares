/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *
 *   Portions from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
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

#ifndef KEYBOARDPAGE_H
#define KEYBOARDPAGE_H

#include "keyboardwidget/keyboardglobal.h"

#include "Typedefs.h"

#include <QListWidgetItem>
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
    virtual ~KeyboardPage();

    void init();

    QString prettyStatus() const;

    QList< Calamares::job_ptr > createJobs( const QString& xOrgConfFileName,
                                            const QString& convertedKeymapPath );

    void onActivate();
    void finalize();

protected slots:
    void onListLayoutCurrentItemChanged( QListWidgetItem* current,
                                         QListWidgetItem* previous );
    void onListVariantCurrentItemChanged( QListWidgetItem* current,
                                          QListWidgetItem* previous );

private:
    class LayoutItem : public QListWidgetItem
    {
    public:
        QString data;
        KeyboardGlobal::KeyboardInfo info;
    };

    void updateVariants( LayoutItem* currentItem, QString currentVariant = QString() );

    Ui::Page_Keyboard* ui;
    KeyBoardPreview* m_keyboardPreview;
    int m_defaultIndex;
    QMap< QString, QString > m_models;

    QString m_selectedLayout;
    QString m_selectedVariant;
};

#endif // KEYBOARDPAGE_H
