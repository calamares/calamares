/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#ifndef LIBCALAMARESUI_SLIDESHOW_H
#define LIBCALAMARESUI_SLIDESHOW_H

#include <QWidget>

class QQmlComponent;
class QQuickItem;
class QQuickWidget;

namespace Calamares
{

class Slideshow
{
public:
    Slideshow( QWidget* parent ) {};
    virtual ~Slideshow();

    virtual QWidget* widget() = 0;
};

class SlideshowQML : public Slideshow
{
public:
    SlideshowQML( QWidget* parent );
    virtual ~SlideshowQML();

    QWidget* widget() override;

private:
    QQuickWidget* m_qmlShow;
    QQmlComponent* m_qmlComponent;
    QQuickItem* m_qmlObject;  ///< The actual show
};

class SlideshowPictures : public Slideshow
{
public:
    SlideshowPictures( QWidget* parent );
    virtual ~SlideshowPictures();

    QWidget* widget() override;
};

}
#endif
