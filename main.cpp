#pragma warning(disable:26495)
#pragma warning(disable:26813)
#pragma warning(disable:26498)
#pragma warning(disable:6031)
#pragma warning(disable:6386)
#pragma warning(disable:26498)
#pragma warning(disable:6262)
#include "Mainwindow.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mainwindow w;
    w.show();
    return a.exec();
}
