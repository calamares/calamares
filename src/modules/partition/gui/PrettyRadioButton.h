/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifndef PRETTYRADIOBUTTON_H
#define PRETTYRADIOBUTTON_H

#include <QRadioButton>

class ClickableLabel;

class PrettyRadioButton : public QWidget
{
    Q_OBJECT
public:
    explicit PrettyRadioButton( QWidget* parent = nullptr );
    virtual ~PrettyRadioButton() {}

    virtual void setText( const QString& text );

    virtual void setIconSize( const QSize& size );

    virtual void setIcon( const QIcon& icon );

    virtual QSize iconSize() const;

    virtual QRadioButton* buttonWidget() const;

protected:
    ClickableLabel* m_label;
    QRadioButton* m_radio;
};

#endif // PRETTYRADIOBUTTON_H
