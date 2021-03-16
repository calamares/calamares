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

#include "Slideshow.h"

#include "Branding.h"
#include "utils/Dirs.h"
#include "utils/Logger.h"
#ifdef WITH_QML
#include "utils/Qml.h"
#endif
#include "utils/Retranslator.h"

#include <QLabel>
#include <QMutexLocker>
#ifdef WITH_QML
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickWidget>
#endif
#include <QTimer>

#include <chrono>

namespace Calamares
{

Slideshow::~Slideshow() {}

#ifdef WITH_QML
SlideshowQML::SlideshowQML( QWidget* parent )
    : Slideshow( parent )
    , m_qmlShow( new QQuickWidget )
    , m_qmlComponent( nullptr )
    , m_qmlObject( nullptr )
{
    m_qmlShow->setObjectName( "qml" );

    CalamaresUtils::registerQmlModels();

    m_qmlShow->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    m_qmlShow->setResizeMode( QQuickWidget::SizeRootObjectToView );
    m_qmlShow->engine()->addImportPath( CalamaresUtils::qmlModulesDir().absolutePath() );

    cDebug() << "QML import paths:" << Logger::DebugList( m_qmlShow->engine()->importPathList() );
#if QT_VERSION >= QT_VERSION_CHECK( 5, 10, 0 )
    CALAMARES_RETRANSLATE( if ( m_qmlShow ) { m_qmlShow->engine()->retranslate(); } );
#endif

    if ( Branding::instance()->slideshowAPI() == 2 )
    {
        cDebug() << "QML load on startup, API 2.";
        loadQmlV2();
    }
}

SlideshowQML::~SlideshowQML()
{
    delete m_qmlObject;
    delete m_qmlComponent;
    delete m_qmlShow;
}

QWidget*
SlideshowQML::widget()
{
    return m_qmlShow;
}

void
SlideshowQML::loadQmlV2()
{
    QMutexLocker l( &m_mutex );
    if ( !m_qmlComponent && !Calamares::Branding::instance()->slideshowPath().isEmpty() )
    {
        m_qmlComponent = new QQmlComponent( m_qmlShow->engine(),
                                            QUrl::fromLocalFile( Calamares::Branding::instance()->slideshowPath() ),
                                            QQmlComponent::CompilationMode::Asynchronous );
        connect( m_qmlComponent, &QQmlComponent::statusChanged, this, &SlideshowQML::loadQmlV2Complete );
    }
}

void
SlideshowQML::loadQmlV2Complete()
{
    QMutexLocker l( &m_mutex );
    if ( m_qmlComponent && m_qmlComponent->isReady() && !m_qmlObject )
    {
        cDebug() << "QML component complete, API 2";
        // Don't do this again
        disconnect( m_qmlComponent, &QQmlComponent::statusChanged, this, &SlideshowQML::loadQmlV2Complete );

        QObject* o = m_qmlComponent->create();
        m_qmlObject = qobject_cast< QQuickItem* >( o );
        if ( !m_qmlObject )
        {
            delete o;
        }
        else
        {
            cDebug() << Logger::SubEntry << "Loading" << Calamares::Branding::instance()->slideshowPath();

            // setContent() is public API, but not documented publicly.
            // It is marked \internal in the Qt sources, but does exactly
            // what is needed: sets up visual parent by replacing the root
            // item, and handling resizes.
            m_qmlShow->setContent(
                QUrl::fromLocalFile( Calamares::Branding::instance()->slideshowPath() ), m_qmlComponent, m_qmlObject );
            if ( isActive() )
            {
                // We're alreay visible! Must have been slow QML loading, and we
                // passed onActivate already. changeSlideShowState() locks
                // the same mutex: call changeSlideShowState() after l is dead.
                QTimer::singleShot( 0, this, &SlideshowQML::startSlideShow );
            }
        }
    }
    else
    {
        if ( m_qmlObject )
        {
            cWarning() << "QML object already created";
        }
        else if ( !m_qmlComponent )
        {
            cWarning() << "QML component does not exist";
        }
        else if ( m_qmlComponent && !m_qmlComponent->isReady() )
        {
            cWarning() << "QML component not ready:" << m_qmlComponent->errors();
        }
    }
}

void
SlideshowQML::startSlideShow()
{
    changeSlideShowState( Slideshow::Start );
}


/*
 * Applies V1 and V2 QML activation / deactivation:
 *  - V1 loads the QML in @p widget on activation. Sets root object property
 *    *activatedInCalamares* as appropriate.
 *  - V2 calls onActivate() or onLeave() in the QML as appropriate. Also
 *    sets the *activatedInCalamares* property.
 */
void
SlideshowQML::changeSlideShowState( Action state )
{
    QMutexLocker l( &m_mutex );
    bool activate = state == Slideshow::Start;

    if ( Branding::instance()->slideshowAPI() == 2 )
    {
        // The QML was already loaded in the constructor, need to start it
        CalamaresUtils::callQmlFunction( m_qmlObject, activate ? "onActivate" : "onLeave" );
    }
    else if ( !Calamares::Branding::instance()->slideshowPath().isEmpty() )
    {
        // API version 1 assumes onCompleted is the trigger
        if ( activate )
        {
            m_qmlShow->setSource( QUrl::fromLocalFile( Calamares::Branding::instance()->slideshowPath() ) );
        }
        // needs the root object for property setting, below
        m_qmlObject = m_qmlShow->rootObject();
    }

    // V1 API has picked up the root object for use, V2 passed it in.
    if ( m_qmlObject )
    {
        static const char propertyName[] = "activatedInCalamares";
        auto property = m_qmlObject->property( propertyName );
        if ( property.isValid() && ( property.type() == QVariant::Bool ) && ( property.toBool() != activate ) )
        {
            m_qmlObject->setProperty( propertyName, activate );
        }
    }

    if ( ( Branding::instance()->slideshowAPI() == 2 ) && ( state == Slideshow::Stop ) )
    {
        delete m_qmlObject;
        m_qmlObject = nullptr;
    }

    m_state = state;
}
#endif

SlideshowPictures::SlideshowPictures( QWidget* parent )
    : Slideshow( parent )
    , m_label( new QLabel( parent ) )
    , m_timer( new QTimer( this ) )
    , m_imageIndex( 0 )
    , m_images( Branding::instance()->slideshowImages() )
{
    m_label->setObjectName( "image" );

    m_label->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    m_label->setAlignment( Qt::AlignCenter );
    m_timer->setInterval( std::chrono::milliseconds( 2000 ) );
    connect( m_timer, &QTimer::timeout, this, &SlideshowPictures::next );
}

SlideshowPictures::~SlideshowPictures()
{
    delete m_timer;
    delete m_label;
}

QWidget*
SlideshowPictures::widget()
{
    return m_label;
}

void
SlideshowPictures::changeSlideShowState( Calamares::Slideshow::Action a )
{
    QMutexLocker l( &m_mutex );
    m_state = a;
    if ( a == Slideshow::Start )
    {
        m_imageIndex = -1;
        if ( m_images.count() < 1 )
        {
            m_label->setPixmap( QPixmap( ":/data/images/squid.svg" ) );
        }
        else
        {

            m_timer->start();
            QTimer::singleShot( 0, this, &SlideshowPictures::next );
        }
    }
    else
    {
        m_timer->stop();
    }
}

void
SlideshowPictures::next()
{
    QMutexLocker l( &m_mutex );

    if ( m_imageIndex < 0 )
    {
        // Initialization, don't do the advance-by-one
        m_imageIndex = 0;
    }
    else
    {
        m_imageIndex++;
        if ( m_imageIndex >= m_images.count() )
        {
            m_imageIndex = 0;
        }
    }

    if ( m_imageIndex >= m_images.count() )
    {
        // Unusual case: timer is running, but we have 0 images to display.
        // .. this would have been caught in changeSlideShowState(), which
        // .. special-cases 0 images.
        return;
    }

    m_label->setPixmap( QPixmap( m_images.at( m_imageIndex ) ) );
}


}  // namespace Calamares
