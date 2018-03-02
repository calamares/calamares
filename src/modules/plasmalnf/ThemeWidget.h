/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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
} ;

#endif

