#include <PartitionCoreModule.h>
#include <PartitionPage.h>

#include <QApplication>

int
main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    PartitionCoreModule core;
    PartitionPage page( &core );
    page.show();
    return app.exec();
}
