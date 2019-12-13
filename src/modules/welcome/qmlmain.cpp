/* Example executable showing a QML page and using the
 * models from libcalamares for displaying a welcome.
 */

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

#include "locale/LabelModel.h"
#include "utils/Logger.h"
#include "Branding.h"
#include "WelcomeViewStep.h"

#include "Config.h"

static Config* theConfig()
{
    static Config* cnf = new Config();
    return cnf;
}

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

    Config cnf;
    if ( argc > 1 )
    {
        cnf.setHelpUrl( QUrl( argv[1] ) );
    }

    // TODO: this should put the one config object in the context, rather than adding a factory function to share it everywhere
    qmlRegisterSingletonType< Config >( "io.calamares.modules.welcome", 1, 0, "PotatoConfig", [](QQmlEngine*, QJSEngine*) -> QObject* { return theConfig(); });

    qmlRegisterSingletonType< CalamaresUtils::Locale::LabelModel >( "io.calamares.locale", 1, 0, "LocaleModel", [](QQmlEngine*, QJSEngine*) -> QObject* { return CalamaresUtils::Locale::availableTranslations(); } );

    qmlRegisterSingletonType< Calamares::Branding >( "io.calamares.ui", 1, 0, "Branding", [](QQmlEngine*, QJSEngine*) -> QObject* { return Calamares::Branding::instance(); } );

    qqw.setSource( QUrl::fromLocalFile("../src/modules/welcome/welcome.qml") );

    return a.exec();
}
