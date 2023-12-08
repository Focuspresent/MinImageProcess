#include "QCurve.h"
#include <QApplication>

int main(int argc,char* argv[])
{
    QApplication a(argc,argv);
    QCurve qcurve(nullptr,cv::Scalar(255,0,0));
    qcurve.setWindowTitle("QCurve test");
    qcurve.addQPoint(QPoint(45,45));
    qcurve.addQPoint(QPoint(90,90));
    qcurve.show();
    return a.exec();
}