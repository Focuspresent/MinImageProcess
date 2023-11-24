#include "MainInterface.h"
#include <QApplication>

int main(int argc,char* argv[])
{
    QApplication a(argc,argv);
    MainInterface m;
    m.show();
    return a.exec();
}