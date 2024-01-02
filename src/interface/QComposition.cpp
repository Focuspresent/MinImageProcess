#include "QComposition.h"
#include "Tool.hpp"

QComposition::QComposition(QWidget* parent)
    :QWidget(parent)
    ,ui(new Ui_QComposition)
{   
    setMouseTracking(true);
    m_mousePressed = false;
    m_resizeStarted = false;
    is_neartl=is_neartr=is_nearbl=is_nearbr=false;

    setWindowFlags(Qt::FramelessWindowHint);
    setMinimumSize(5,5);
    setWindowOpacity(0.5);
    setGeometry(TGI.ShowQRect());
}

QComposition::~QComposition()
{
    delete ui;
}

void QComposition::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePressed = true;
        m_resizeStartPosition = event->pos();
        m_resizeStartGeometry = geometry();
        if(TGI.Is_Near(event->globalPos(),TopLeft())){
            is_neartl=true;
        }else if(TGI.Is_Near(event->globalPos(),TopRight())){
            is_neartr=true;
        }else if(TGI.Is_Near(event->globalPos(),BottomLeft())){
            is_nearbl=true;
        }else if(TGI.Is_Near(event->globalPos(),BottomRight())){
            is_nearbr=true;
        }
    }
}

void QComposition::mouseMoveEvent(QMouseEvent* event)
{   
    if (m_mousePressed) {
        QPoint delta = event->pos() - m_resizeStartPosition;
        QRect newGeometry = m_resizeStartGeometry;
        if (is_nearbr) {
            newGeometry.setWidth(m_resizeStartGeometry.width() + delta.x());
            newGeometry.setHeight(m_resizeStartGeometry.height() + delta.y());
        } else if (is_neartl) {
            if(TGI.CompareQPoint(TGQTL,event->globalPos())!=TGI.BR) return ;
            newGeometry.setTopLeft(m_resizeStartGeometry.topLeft() + delta);
            newGeometry.setWidth(m_resizeStartGeometry.width() - delta.x());
            newGeometry.setHeight(m_resizeStartGeometry.height() - delta.y());
        } else if (is_neartr) {
            if(TGI.CompareQPoint(TGQTR,event->globalPos())!=TGI.BL) return ;
            newGeometry.setTopRight(m_resizeStartGeometry.topRight() + delta);
            newGeometry.setHeight(m_resizeStartGeometry.height() - delta.y());
        } else if (is_nearbl) {
            if(TGI.CompareQPoint(TGQBL,event->globalPos())!=TGI.TR) return ;
            newGeometry.setBottomLeft(m_resizeStartGeometry.bottomLeft() + delta);
            newGeometry.setWidth(m_resizeStartGeometry.width() - delta.x());
            newGeometry.setHeight(m_resizeStartGeometry.height() + delta.y());
        }
        setGeometry(newGeometry);
        setMaximumSize(MaxQSize(TopLeft(),TGQBR));
    }
}

void QComposition::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_mousePressed = false;
        m_resizeStarted = false;
        is_neartl=is_neartr=is_nearbl=is_nearbr=false;
    }
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
    double scalewidth=TGI.getScaleWidth(),scaleheight=TGI.getScaleHeight();
    double x=geometry().x()-TGI.X(),y=geometry().y()-TGI.Y(),width=geometry().width(),height=geometry().height();
    x/=scalewidth;width/=scalewidth;
    y/=scaleheight;height/=scaleheight;
#ifdef DEBUG
    std::cout<<x<<" "<<y<<" "<<width<<" "<<height<<std::endl;
    std::cout<<TGOMAT.cols<<" "<<TGOMAT.rows<<std::endl;
    std::cout<<x+width<<" "<<y+height<<std::endl;
#endif
    Composition((int)x,(int)y,(int)width,(int)height);
    emit ChangeCurMat();
}

//p1<p2
QSize QComposition::MaxQSize(QPoint p1,QPoint p2)
{
    return std::move(QSize(p2.x()-p1.x(),p2.y()-p1.y()));
}