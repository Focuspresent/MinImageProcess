#include "QComposition.h"
#include "Tool.hpp"

QComposition::QComposition(QWidget* parent)
    :QWidget(parent)
    ,ui(new Ui_QComposition)
{   
    is_near=false;

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setGeometry(TGI.ShowQRect());
}

QComposition::~QComposition()
{
    delete ui;
}

void QComposition::mousePressEvent(QMouseEvent* event)
{
    if(event->button()!=Qt::LeftButton){
        return ;
    }
}

void QComposition::mouseMoveEvent(QMouseEvent* event)
{
    if(is_near){
        QPoint delta = event->globalPos()-global;
        // 计算新的窗口大小
        int newWidth = qsize.width() + delta.x();
        int newHeight = qsize.height() + delta.y();
        // 缩放窗口
        resize(newWidth, newHeight);
    }
}

void QComposition::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button()!=Qt::LeftButton){
        return ;
    }
    is_near=false;
}

void QComposition::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 绘制窗口边框
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

QPoint QComposition::TopLeft()
{
    return std::move(QPoint(geometry().x(),geometry().y()));
}

QPoint QComposition::TopRight()
{
    return std::move(QPoint(geometry().x()+geometry().width(),geometry().y()));
}

QPoint QComposition::BottomLeft()
{
    return std::move(QPoint(geometry().x(),geometry().y()+geometry().height()));
}

QPoint QComposition::BottomRight()
{
    return std::move(QPoint(geometry().x()+geometry().width(),geometry().y()+geometry().height()));
}

void QComposition::CropCurMat()
{
    
    emit ChangeCurMat();
    delete this;
}