#include "QCurve.h"
#include <QApplication>

int main(int argc,char* argv[])
{
    QApplication a(argc,argv);
    QCurve qcurve;
    qcurve.setWindowTitle("QCurve test");
    qcurve.show();
    return a.exec();
}