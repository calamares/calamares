#include <PartitionPage.h>

#include <QApplication>

int
main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    PartitionPage page;
    page.show();
    return app.exec();
}
