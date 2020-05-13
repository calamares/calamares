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

#include "Slideshow.h"

#include "Branding.h"
#include "utils/Dirs.h"
#include "utils/Logger.h"
#include "utils/Qml.h"
#include "utils/Retranslator.h"

#include <QMutexLocker>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickWidget>

namespace Calamares
{

Slideshow::~Slideshow() {}

SlideshowQML::SlideshowQML( QWidget* parent )
    : Slideshow( parent )
    , m_qmlShow( new QQuickWidget )
    , m_qmlComponent( nullptr )
    , m_qmlObject( nullptr )
{
    m_qmlShow->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    m_qmlShow->setResizeMode( QQuickWidget::SizeRootObjectToView );
    m_qmlShow->engine()->addImportPath( CalamaresUtils::qmlModulesDir().absolutePath() );

    cDebug() << "QML import paths:" << Logger::DebugList( m_qmlShow->engine()->importPathList() );
#if QT_VERSION >= QT_VERSION_CHECK( 5, 10, 0 )
    CALAMARES_RETRANSLATE( if ( m_qmlShow ) { m_qmlShow->engine()->retranslate(); } )
#endif

    if ( Branding::instance()->slideshowAPI() == 2 )
    {
        cDebug() << "QML load on startup, API 2.";
        loadQmlV2();
    }
}

SlideshowQML::~SlideshowQML()
{
}

QWidget * SlideshowQML::widget()
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
                // passed onActivate already.
                changeSlideShowState( Slideshow::Start );
            }
        }
    }
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
        CalamaresUtils::callQMLFunction( m_qmlObject, activate ? "onActivate" : "onLeave" );
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

}  // namespace
