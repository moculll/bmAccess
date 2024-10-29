#include "bmHelper.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bmHelper *w = new bmHelper;
    



    w->show();
    

    return a.exec();
}
