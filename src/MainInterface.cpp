#include "MainInterface.h"
#include "Tool.hpp"

MainInterface::MainInterface(QWidget* parent)
    :QMainWindow(parent)
    ,ui(new Ui_MainInterface)
{
    ui->setupUi(this);
    //数据
    TGI.setShowQRct(ui->label_show->geometry());

    //连接槽
    connect(ui->pb_open,SIGNAL(clicked()),this,SLOT(OpenImage()));
    connect(ui->open,SIGNAL(triggered()),this,SLOT(OpenImage()));
}

MainInterface::~MainInterface()
{
    delete ui;
}

void MainInterface::OpenImage()
{
    QString filename=QFileDialog::getOpenFileName(this,"选择一个图片","E:/图片/二次元","(All Imags(*.jpg *.png))");
    if(filename.isEmpty()){
        return ;
    }
    //读取
    TGI.ReadCurMat(filename);
    //展示
    MatToShow();
}

void MainInterface::MatToShow()
{   
    if(TGMAT.empty()){
        return ;
    }
    //转成QImage
    QImage display;
    if(TGMAT.channels()==3){
        display=QImage(TGMAT.data,TGMAT.cols,TGMAT.rows,TGMAT.cols*TGMAT.channels(),QImage::Format_RGB888);
    }else if(TGMAT.channels()==4){
        display=QImage(TGMAT.data,TGMAT.cols,TGMAT.rows,TGMAT.cols*TGMAT.channels(),QImage::Format_RGBA8888);
    }
    //放到组件中
    ui->label_show->setPixmap(QPixmap::fromImage(display));
    //适应
    ui->label_show->setFixedSize(display.size());
    //更新显示窗口数据
    TGI.setShowQRct(ui->label_show->geometry());
    TGI.setX(this->x()+ui->widget_2->pos().x()+ui->label_show->geometry().x());
    TGI.setY(this->y()+ui->widget_2->pos().y()+ui->label_show->geometry().y()+ui->menubar->geometry().height());
}

void MainInterface::mousePressEvent(QMouseEvent* event)
{
#ifdef DEBUG 
    qDebug()<<"event->pos(): "<<event->pos();
    qDebug()<<"event->globalPos(): "<<event->globalPos();
    qDebug()<<"ui->widget_2->pos(): "<<ui->widget_2->pos();
    qDebug()<<"ui->label_show->pos(): "<<ui->label_show->pos();
    qDebug()<<"ui->label_show->geometry(): "<<ui->label_show->geometry();
    qDebug()<<"calc x "<<ui->widget_2->pos().x()+ui->label_show->geometry().x();
    qDebug()<<"calc y "<<ui->widget_2->pos().y()+ui->label_show->geometry().y()+ui->menubar->geometry().height();
#endif
}

void MainInterface::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    MatToShow();
}

void MainInterface::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event);
    MatToShow();
}