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
#include "utils/Logger.h"
#include "UsersQmlViewStep.h"


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

    std::unique_ptr< Calamares::Settings > settings_p( Calamares::Settings::init( QString() ) );
    std::unique_ptr< Calamares::JobQueue > jobqueue_p( new Calamares::JobQueue( nullptr ) );

    Calamares::Branding defaultBrand( "src/branding/nxos/branding.desc" );

    QMainWindow mw;
    QQuickWidget qqw( &mw );
    qqw.setResizeMode(QQuickWidget::SizeRootObjectToView);
    qqw.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mw.setCentralWidget( &qqw );
    mw.resize( QSize( 800, 1000 ) );
    mw.show();

    qmlRegisterType(QUrl::fromLocalFile("../src/qml/calamares/ResponsiveBase.qml"), "io.calamares.ui", 1, 0, "ResponsiveBase");
    qmlRegisterType(QUrl::fromLocalFile("../src/qml/calamares/ListViewTemplate.qml"), "io.calamares.ui", 1, 0, "ListViewTemplate");
    qmlRegisterType(QUrl::fromLocalFile("../src/qml/calamares/ListItemDelegate.qml"), "io.calamares.ui", 1, 0, "ListItemDelegate");

    // TODO: this should put the one config object in the context, rather than adding a factory function to share it everywhere
    qmlRegisterType< UsersQmlViewStep >( "io.calamares.modules", 1, 0, "Users" );
    qmlRegisterSingletonType< Calamares::Branding >( "io.calamares.ui", 1, 0, "Branding", [](QQmlEngine*, QJSEngine*) -> QObject* { return Calamares::Branding::instance(); } );

    const auto url =  QUrl::fromLocalFile("../src/modules/usersq/users.qml");

    cDebug() << "Loading qml file form @" << url ;

    qqw.setSource( url );

    return a.exec();
}
