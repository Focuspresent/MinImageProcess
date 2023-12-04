#include "QHSL.h"
#include "Tool.hpp"

QHSL::QHSL(QWidget* parent)
    :QWidget(parent)
    ,ui(new Ui_QHSL)
{
    ui->setupUi(this);
    is_press=false;

    setWindowFlags(Qt::FramelessWindowHint);
}

QHSL::~QHSL()
{
    delete ui;
}

void QHSL::mousePressEvent(QMouseEvent* event)
{
    if(event->buttons()==Qt::LeftButton){
        is_press=true;
        pos=event->pos();
    }
}

void QHSL::mouseMoveEvent(QMouseEvent* event)
{
    if(is_press){
        QPoint newPos=event->globalPos()-pos;
        move(newPos);
    }
}

void QHSL::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->buttons()==Qt::LeftButton){
        is_press=false;
    }
}