/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include <InstallationViewStep.h>

#include "JobQueue.h"
#include "Branding.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "Settings.h"

#include <QDir>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QtQuickWidgets/QQuickWidget>
#include <QQmlEngine>

namespace Calamares
{

InstallationViewStep::InstallationViewStep( QObject* parent )
    : ViewStep( parent )
    , m_widget( new QWidget )
{
    m_progressBar = new QProgressBar;
    m_progressBar->setMaximum( 10000 );
    m_label = new QLabel;
    QVBoxLayout* layout = new QVBoxLayout( m_widget );
    QVBoxLayout* innerLayout = new QVBoxLayout;

    m_slideShow = new QQuickWidget;
    layout->addWidget( m_slideShow );
    CalamaresUtils::unmarginLayout( layout );

    layout->addLayout( innerLayout );
    m_slideShow->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    m_slideShow->setResizeMode( QQuickWidget::SizeRootObjectToView );

    QDir importPath;
    {
        QString subpath( "slideshow" );

        if ( CalamaresUtils::isAppDataDirOverridden() )
        {
            importPath = QDir( CalamaresUtils::appDataDir()
                               .absoluteFilePath( subpath ) );
            if ( !importPath.exists() || !importPath.isReadable() )
            {
                cLog() << "FATAL ERROR: explicitly configured application data directory"
                       << CalamaresUtils::appDataDir().absolutePath()
                       << "does not contain a valid slideshow directory at"
                       << importPath.absolutePath()
                       << "\nCowardly refusing to continue startup without slideshow.";
                ::exit( EXIT_FAILURE );
            }
        }
        else
        {
            QStringList slideshowDirCandidatesByPriority;
            if ( Calamares::Settings::instance()->debugMode() )
            {
                slideshowDirCandidatesByPriority.append(
                            QDir::current().absoluteFilePath(
                            QString( "src/libcalamaresui/%1" )
                                .arg( subpath ) ) );
            }
            slideshowDirCandidatesByPriority.append( CalamaresUtils::appDataDir()
                                .absoluteFilePath( subpath ) );

            foreach ( const QString& path, slideshowDirCandidatesByPriority )
            {
                QDir dir( path );
                if ( dir.exists() && dir.isReadable() )
                {
                    importPath = dir;
                    break;
                }
            }

            if ( !importPath.exists() || !importPath.isReadable() )
            {
                cLog() << "FATAL ERROR: none of the expected slideshow paths ("
                       << slideshowDirCandidatesByPriority.join( ", " )
                       << ") exist."
                       << "\nCowardly refusing to continue startup without slideshow.";
                ::exit( EXIT_FAILURE );
            }
        }
    }
    cDebug() << "importPath:" << importPath;
    importPath.cdUp();

    m_slideShow->engine()->addImportPath( importPath.absolutePath() );
    m_slideShow->setSource( QUrl::fromLocalFile( Calamares::Branding::instance()
                                                 ->slideshowPath() ) );

    innerLayout->addSpacing( CalamaresUtils::defaultFontHeight() / 2 );
    innerLayout->addWidget( m_progressBar );
    innerLayout->addWidget( m_label );

    connect( JobQueue::instance(), &JobQueue::progress,
             this, &InstallationViewStep::updateFromJobQueue );

    cDebug() << "importPathList:" << m_slideShow->engine()->importPathList();

}

QString
InstallationViewStep::prettyName() const
{
    return tr( "Install" );
}

QWidget*
InstallationViewStep::widget()
{
    return m_widget;
}


void
InstallationViewStep::next()
{
}

void
InstallationViewStep::back()
{
}

bool
InstallationViewStep::isNextEnabled() const
{
    return false;
}

bool
InstallationViewStep::isAtBeginning() const
{
    return false;
}

bool
InstallationViewStep::isAtEnd() const
{
    return false;
}

QList< Calamares::job_ptr >
InstallationViewStep::jobs() const
{
    return QList< Calamares::job_ptr >();
}

void
InstallationViewStep::updateFromJobQueue( qreal percent, const QString& message )
{
    m_progressBar->setValue( percent * m_progressBar->maximum() );
    m_label->setText( message );
}

} // namespace
