#ifndef QHSL_H
#define QHSL_H

#include "ui_QHSL.h"
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

class QHSL:public QWidget{
    Q_OBJECT

public:
    QHSL(QWidget* parent=nullptr);
    ~QHSL();
signals:
    void ChangeCurMat();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
public slots:
private:
    Ui_QHSL* ui;
    QPoint pos;

    bool is_press;
};

#endif //QHSL_H