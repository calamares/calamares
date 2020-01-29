/* Example executable showing a QML page and using the
 * models from libcalamares for displaying a welcome.
 */

#include <memory>

#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QQmlEngine>
#include <QQuickWidget>
#include <QString>
#include <QTimer>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

#include <KAboutData>

#include "Branding.h"
#include "JobQueue.h"
#include "Settings.h"
#include "locale/LabelModel.h"
#include "utils/Logger.h"
#include "LocaleQmlViewStep.h"
#include "utils/Yaml.h"

#include "Config.h"

int main(int argc, char **argv)
{
    QApplication a( argc, argv );

    KAboutData aboutData( "calamares",
                          "Calamares",
                          "0.1",
                          "Calamares QML Test Application",
                          KAboutLicense::GPL_V3,
                          QString(),
                          QString(),
                          "https://calamares.io",
                          "https://github.com/calamares/calamares/issues" );
    KAboutData::setApplicationData( aboutData );
    a.setApplicationDisplayName( QString() );  // To avoid putting an extra "Calamares/" into the log-file

    Logger::setupLogLevel( Logger::LOGVERBOSE );

    std::unique_ptr< Calamares::Settings > settings_p( new Calamares::Settings( QString(), true ) );
    std::unique_ptr< Calamares::JobQueue > jobqueue_p( new Calamares::JobQueue( nullptr ) );

    Calamares::Branding defaultBrand( "src/branding/nxos/branding.desc" );

    QMainWindow mw;
    QWidget background;
    QVBoxLayout vl;
    QLabel l( "Hello, world", &mw );
    QQuickWidget qqw( &mw );
    vl.addWidget( &qqw );
//     vl.addWidget( &l );
    background.setLayout( &vl );
    mw.setCentralWidget( &background );
    mw.resize( QSize( 400, 400 ) );
    mw.show();

    // TODO: this should put the one config object in the context, rather than adding a factory function to share it everywhere
    LocaleQmlViewStep locale;

    cDebug() << "Loading qml file form @" << "../src/modules/localeq/locale.qml" ;
    qqw.setSource( QUrl::fromLocalFile("../src/modules/localeq/locale.qml") );

    return a.exec();
}
