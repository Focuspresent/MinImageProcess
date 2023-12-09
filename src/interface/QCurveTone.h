#ifndef QCURVETONE_H
#define QCURVETONE_H

#include "QCurve.h"
#include <QPushButton>

class QCurveTone:public QWidget{
    Q_OBJECT

public:
    QCurveTone(QWidget* parent=nullptr);
    ~QCurveTone();
    void setCurrent(QCurve* qcurve);
signals:
    void ChangeCurMat();
protected:
    /* void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override; */
public slots:
private:
    QCurve *rgb,*red,*green,*blue;
    QPushButton *bt_rgb,*bt_red,*bt_green,*bt_blue;
    QCurve *current;
};

#endif //QCURVETONE_H