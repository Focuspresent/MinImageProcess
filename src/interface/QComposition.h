#ifndef QCOMPOSITION_H
#define QCOMPOSITION_H

#include "ui_QComposition.h"
#include <QWidget>

class QComposition:public QWidget{
    Q_OBJECT

public:
    QComposition(QWidget* parent=nullptr);
    ~QComposition();
signals:
    void ChangeCurMat();
protected:
public slots:
private:
    Ui_QComposition* ui;
};

#endif //QCOMPOSITION_H
