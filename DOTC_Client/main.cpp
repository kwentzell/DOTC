#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("DOTC");
    QCoreApplication::setOrganizationName("DOTC");
    QCoreApplication::setOrganizationDomain("dotc.bit");

    MainWindow w;
    w.show();

    return a.exec();
}
