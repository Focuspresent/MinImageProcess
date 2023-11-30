#ifndef QCOMPOSITION_H
#define QCOMPOSITION_H

#include "ui_QComposition.h"
#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QSize>
#include <QPaintEvent>
#include "ImageEdit.h"

class QComposition:public QWidget{
    Q_OBJECT

public:
    QComposition(QWidget* parent=nullptr);
    ~QComposition();
    QPoint TopLeft();
    QPoint TopRight();
    QPoint BottomLeft();
    QPoint BottomRight();
    QSize MaxQSize(QPoint p1,QPoint p2);
signals:
    void ChangeCurMat();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent *event) override;
public slots:
    void CropCurMat();
private:
    Ui_QComposition* ui;
    bool is_neartl,is_neartr,is_nearbl,is_nearbr;

    QPoint m_resizeStartPosition;
    QRect m_resizeStartGeometry;
    bool m_mousePressed;
    bool m_resizeStarted;
    int m_resizeHandleSize;
};

#endif //QCOMPOSITION_H
