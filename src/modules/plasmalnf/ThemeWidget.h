/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PLASMALNF_THEMEWIDGET_H
#define PLASMALNF_THEMEWIDGET_H

#include <QWidget>

class QAbstractButton;
class QLabel;
class QRadioButton;

struct ThemeInfo;

class ThemeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThemeWidget( const ThemeInfo& info, QWidget* parent = nullptr );

    QAbstractButton* button() const;

    void updateThemeName( const ThemeInfo& info );

signals:
    void themeSelected( const QString& id );

public slots:
    void clicked( bool );

private:
    QString m_id;
    QRadioButton* m_check;
    QLabel* m_description;
};

#endif
