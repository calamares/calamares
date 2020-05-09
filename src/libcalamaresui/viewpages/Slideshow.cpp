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

#include "utils/Dirs.h"
#include "utils/Logger.h"

#include <QQuickWidget>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>

namespace Calamares
{

Slideshow::~Slideshow()
{
}

SlideshowQML::SlideshowQML(QWidget* parent)
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
    CALAMARES_RETRANSLATE( m_qmlShow->engine()->retranslate(); )
#endif

}

}
