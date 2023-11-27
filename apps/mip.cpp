#include "MainInterface.h"
#include <QApplication>

int main(int argc,char* argv[])
{
    QApplication a(argc,argv);
    MainInterface m;
    m.setWindowTitle("MIP");
    m.show();
    return a.exec();
}