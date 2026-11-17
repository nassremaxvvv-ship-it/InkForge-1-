
#include <QApplication>
#include <QCoreApplication>
#include "ui/inkforgewindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("InkForge");
    QCoreApplication::setApplicationVersion("0.1.0");
    QCoreApplication::setOrganizationName("InkForge");

    InkForgeWindow window;
    window.show();

    return app.exec();
}
