#ifndef QCURVE_H
#define QCURVE_H

#include "Tool.hpp"
#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>

class QCurve:public QWidget{
    Q_OBJECT

public:
    QCurve(QWidget* parent=nullptr);
    ~QCurve();

    std::vector<QPoint>::iterator find(int x);
    std::vector<QPoint>::iterator find(int x,int y);
    std::vector<QPoint>::iterator add(int x,int y);

    int calcCurve(double* output_y);

    void clearQPoints();
    int addQPoint(const QPoint& p);
    int deleteQPoint(const QPoint& p);
    int moveQPoint(const QPoint& p,int x,int y);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
private:
    cv::Scalar color;
    cv::Scalar back_color;
    std::vector<QPoint> qpoints;
    std::vector<QPoint>::iterator current;
    bool is_press;
};

#endif //QCURVE_H