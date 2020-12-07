/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LIBCALAMARESUI_SLIDESHOW_H
#define LIBCALAMARESUI_SLIDESHOW_H

#include "CalamaresConfig.h"

#include <QMutex>
#include <QStringList>
#include <QWidget>

class QLabel;
class QTimer;
#ifdef WITH_QML
class QQmlComponent;
class QQuickItem;
class QQuickWidget;
#endif

namespace Calamares
{

/** @brief API for Slideshow objects
 *
 * A Slideshow (subclass) object is created by the ExecutionViewStep
 * and needs to manage its own configuration (e.g. from Branding).
 * The slideshow is started and stopped when it becomes visible
 * and when installation is over, by calling changeSlideShowState()
 * as appropriate.
 */
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
    ~Slideshow() override;

    /// @brief Is the slideshow being shown **right now**?
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

#ifdef WITH_QML
/** @brief Slideshow using a QML file
 *
 * This is the "classic" slideshow in Calamares, which runs some QML
 * while the installation is in progress. It is configured through
 * Branding settings *slideshow* and *slideshowAPI*, showing the QML
 * file from *slideshow*. The API version influences when and how the
 * QML is loaded; version 1 does so only when the slideshow is activated,
 * while version 2 does so asynchronously.
 */
class SlideshowQML : public Slideshow
{
    Q_OBJECT
public:
    SlideshowQML( QWidget* parent );
    ~SlideshowQML() override;

    QWidget* widget() override;
    void changeSlideShowState( Action a ) override;

public slots:
    void loadQmlV2Complete();
    void loadQmlV2();  ///< Loads the slideshow QML (from branding) for API version 2

    /// Implementation detail
    void startSlideShow();

private:
    QQuickWidget* m_qmlShow;
    QQmlComponent* m_qmlComponent;
    QQuickItem* m_qmlObject;  ///< The actual show
};
#endif

/** @brief Slideshow using images
 *
 * This is an "oldschool" slideshow, but new in Calamares, which
 * displays static image files one-by-one. It is for systems that
 * do not use QML at all. It is configured through the Branding
 * setting *slideshow*. When using this widget, the setting must
 * be a list of filenames; the API is set to -1.
 */
class SlideshowPictures : public Slideshow
{
    Q_OBJECT
public:
    SlideshowPictures( QWidget* parent );
    ~SlideshowPictures() override;

    QWidget* widget() override;
    virtual void changeSlideShowState( Action a ) override;

public slots:
    void next();

private:
    QLabel* m_label;
    QTimer* m_timer;
    int m_imageIndex;
    QStringList m_images;
};

}  // namespace Calamares
#endif
