#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QCoreApplication::setOrganizationName("Petr 'Ventus' Vanek");
    QCoreApplication::setOrganizationDomain("fotoventus.cz");
    QCoreApplication::setApplicationName("nc100");
    
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
