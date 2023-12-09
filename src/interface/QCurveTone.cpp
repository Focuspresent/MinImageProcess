#include "QCurveTone.h"

QCurveTone::QCurveTone(QWidget* parent)
    :QWidget(parent)
{   
    setWindowFlags(Qt::FramelessWindowHint);
    resize(400,300);

    rgb=new QCurve(this,cv::Scalar(0,0,0));
    rgb->hide();
    red=new QCurve(this,cv::Scalar(0,0,255));
    red->hide();
    green=new QCurve(this,cv::Scalar(0,255,0));
    green->hide();
    blue=new QCurve(this,cv::Scalar(255,0,0));
    blue->hide();

    bt_rgb=new QPushButton(this);
    bt_rgb->setGeometry(20,22,60,40);
    bt_rgb->setText("RGB");
    bt_rgb->show();
    bt_red=new QPushButton(this);
    bt_red->setGeometry(20,22+60*1,60,40);
    bt_red->setText("RED");
    bt_red->show();
    bt_green=new QPushButton(this);
    bt_green->setGeometry(20,22+60*2,60,40);
    bt_green->setText("GREEN");
    bt_green->show();
    bt_blue=new QPushButton(this);
    bt_blue->setGeometry(20,22+60*3,60,40);
    bt_blue->setText("BLUE");
    bt_blue->show();

    setCurrent(rgb);

    connect(bt_rgb,&QPushButton::clicked,[this]()->void{
        setCurrent(rgb);
    });
    connect(bt_red,&QPushButton::clicked,[this]()->void{
        setCurrent(red);
    });
    connect(bt_green,&QPushButton::clicked,[this]()->void{
        setCurrent(green);
    });
    connect(bt_blue,&QPushButton::clicked,[this]()->void{
        setCurrent(blue);
    });
}

QCurveTone::~QCurveTone()
{
}

void QCurveTone::setCurrent(QCurve* qcurve)
{
    current=qcurve;
    current->setParent(this);
    current->show();
    current->setGeometry(100,22,256,256);

    if(current!=rgb){
        rgb->hide();
    }
    if(current!=red){
        red->hide();
    }
    if(current!=green){
        green->hide();
    }
    if(current!=blue){
        blue->hide();
    }
}