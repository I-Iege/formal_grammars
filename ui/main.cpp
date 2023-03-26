
#ifdef WIN32

#include <QtPlugin>
Q_IMPORT_PLUGIN (QWindowsIntegrationPlugin)

#endif

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
