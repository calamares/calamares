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

#include <QMutex>
#include <QWidget>

class QQmlComponent;
class QQuickItem;
class QQuickWidget;

namespace Calamares
{

class Slideshow : public QObject
{
    Q_OBJECT
public:
    /// @brief State-change of the slideshow, for changeSlideShowState()
    enum Action
    {
        Start,
        Stop
    };

    Slideshow( QWidget* parent = nullptr )
        : QObject( parent )
    {
    }
    virtual ~Slideshow();

    ///@brief Is the slideshow being shown **right now**?
    bool isActive() const { return m_state == Start; }

    /** @brief The actual widget to show the user.
     *
     * Depending on the style of slideshow, this might be a QQuickWidget,
     * or a QLabel, or something else entirely.
     */
    virtual QWidget* widget() = 0;

    /** @brief Tells the slideshow we activated or left the show.
     *
     * If @p state is @c Slideshow::Start, calls suitable activation procedures.
     * If @p state is @c Slideshow::Stop, calls deactivation procedures.
     */
    virtual void changeSlideShowState( Action a ) = 0;

protected:
    QMutex m_mutex;
    Action m_state = Stop;
};

class SlideshowQML : public Slideshow
{
    Q_OBJECT
public:
    SlideshowQML( QWidget* parent );
    virtual ~SlideshowQML() override;

    QWidget* widget() override;
    void changeSlideShowState( Action a ) override;

public slots:
    void loadQmlV2Complete();
    void loadQmlV2();  ///< Loads the slideshow QML (from branding) for API version 2

private:
    QQuickWidget* m_qmlShow;
    QQmlComponent* m_qmlComponent;
    QQuickItem* m_qmlObject;  ///< The actual show
};

class SlideshowPictures : public Slideshow
{
public:
    SlideshowPictures( QWidget* parent );
    virtual ~SlideshowPictures() override;

    QWidget* widget() override;
};

}  // namespace Calamares
#endif
