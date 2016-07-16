#include <QApplication>
#include "application.h"

int main(int argc, char* argv[])
{
    // This attribute needs to be set before the application object is created:
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    Application w;
    w.show();

    return a.exec();
}
