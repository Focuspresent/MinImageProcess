#include "QHSL.h"
#include "Tool.hpp"

QHSL::QHSL(QWidget* parent)
    :QWidget(parent)
    ,ui(new Ui_QHSL)
{
    ui->setupUi(this);
    ui->slider_hue->setRange(-100,100);
    ui->slider_hue->setValue(0);
    ui->slider_sat->setRange(-100,100);
    ui->slider_sat->setValue(0);
    ui->slider_lin->setRange(-100,100);
    ui->slider_lin->setValue(0);
    is_press=false;

    setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->slider_hue,&QSlider::valueChanged,[this](int pos)->void{
        Tone(pos);
        emit ChangeCurMat();
    });
    connect(ui->slider_sat,&QSlider::valueChanged,[this](int pos)->void{
        double saturationMin=0.0,saturationMax=2.0;
        int tma=ui->slider_sat->maximum(),tmi=ui->slider_sat->minimum();
        double factor=(double)(saturationMax-saturationMin)*((double)(pos-tmi)/(tma-tmi))+saturationMin;
        Saturation(factor);
        emit ChangeCurMat();
    });
    connect(ui->slider_lin,&QSlider::valueChanged,[this](int pos)->void{
        Brightness(pos);
        emit ChangeCurMat();
    });
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