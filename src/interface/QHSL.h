#ifndef QHSL_H
#define QHSL_H

#include "ui_QHSL.h"
#include <QWidget>

class QHSL:public QWidget{
    Q_OBJECT

public:
    QHSL(QWidget* parent=nullptr);
    ~QHSL();
signals:
    void ChangeCurMat();
protected:
public slots:
    void HSLCurMat();
private:
    Ui_QHSL* ui;
};

#endif //QHSL_H