#include "QCurveTone.h"

QCurveTone::QCurveTone(QWidget* parent)
    :QWidget(parent)
{   
    setWindowFlags(Qt::FramelessWindowHint);
    resize(400,300);
    setMouseTracking(true);

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

void QCurveTone::ModfiyCurMat()
{
    uchar table[3][256];

    double z[256];
    //算红色通道
    red->calcCurve(z);
    for(int i=0;i<256;i++){
        table[0][i]=z[i];
    }
    //算绿色通道
    green->calcCurve(z);
    for(int i=0;i<256;i++){
        table[1][i]=z[i];
    }
    //算蓝色通道
    blue->calcCurve(z);
    for(int i=0;i<256;i++){
        table[2][i]=z[i];
    }
    //算综合通道
    rgb->calcCurve(z);
    for(int i=0;i<256;i++){
        for(int c=0;c<3;c++){
            uchar value = table[c][i];
			table[c][i] = z[value];
        }
    }
    //调整
    CurveTone(table,3);
    //发射信号
    emit ChangeCurMat();
}

void QCurveTone::mousePressEvent(QMouseEvent* event)
{
    int x=event->pos().x()-100,y=event->pos().y()-22;
    if(x>=0&&x<=255&&y>=0&&y<=255){
        current->mouseDown(x,y);    
        update();
    }
}

void QCurveTone::mouseMoveEvent(QMouseEvent* event)
{   
    int x=event->pos().x()-100,y=event->pos().y()-22;
    if(x>=0&&x<=255&&y>=0&&y<=255){
        if(current->mouseMove(x,y)){
            update();
            ModfiyCurMat();
        }
    }
}

void QCurveTone::mouseReleaseEvent(QMouseEvent* event)
{
    int x=event->pos().x()-100,y=event->pos().y()-22;
    if(x>=0&&x<=255&&y>=0&&y<=255){
        current->mouseUp(x,y);
        update();
    }
}