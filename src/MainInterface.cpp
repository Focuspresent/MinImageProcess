#include "MainInterface.h"
#include "Tool.hpp"

MainInterface::MainInterface(QWidget* parent)
    :QMainWindow(parent)
    ,ui(new Ui_MainInterface)
{
    ui->setupUi(this);
    //数据
    ui_qcom=nullptr;
    bt_comfirm=nullptr;
    bt_cancel=nullptr;
    TGI.setShowQRect(ui->label_show->geometry());

    //连接槽
    connect(ui->pb_open,SIGNAL(clicked()),this,SLOT(OpenImage()));
    connect(ui->open,SIGNAL(triggered()),this,SLOT(OpenImage()));
    connect(ui->ac_crop,SIGNAL(triggered()),this,SLOT(CreateQCOM()));
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

void MainInterface::CreateQCOM()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    if(ui_qcom!=nullptr){
        delete ui_qcom;
        ui_qcom=nullptr;
    }
    ui_qcom=new QComposition();
    ui_qcom->show();

    if(bt_comfirm!=nullptr){
        delete bt_comfirm;
        bt_comfirm=nullptr;
    }
    bt_comfirm=new QPushButton(this);
    bt_comfirm->setWindowFlags(Qt::FramelessWindowHint);
    bt_comfirm->show();
    bt_comfirm->setGeometry(0,ui->menubar->height(),30,30);

    if(bt_cancel!=nullptr){
        delete bt_cancel;
        bt_cancel=nullptr;
    }
    bt_cancel=new QPushButton(this);
    bt_cancel->setWindowFlags(Qt::FramelessWindowHint);
    bt_cancel->show();
    bt_cancel->setGeometry(bt_comfirm->geometry().width(),ui->menubar->height(),30,30);

    connect(ui_qcom,SIGNAL(ChangeCurMat()),this,SLOT(MatToShow()));
    connect(bt_comfirm,SIGNAL(clicked()),ui_qcom,SLOT(CropCurMat()));
    connect(bt_comfirm,SIGNAL(clicked()),this,SLOT(DeleteButton()));
    connect(bt_cancel,&QPushButton::clicked,this,&MainInterface::DeleteButton);
}

void MainInterface::MatToShow()
{   
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //转成QImage
    QImage display;
    if(TGMAT.channels()==3){
        display=QImage(TGMAT.data,TGMAT.cols,TGMAT.rows,static_cast<int>(TGMAT.step),QImage::Format_RGB888);
    }else if(TGMAT.channels()==4){
        display=QImage(TGMAT.data,TGMAT.cols,TGMAT.rows,static_cast<int>(TGMAT.step),QImage::Format_RGBA8888);
    }
    //放到组件中
    ui->label_show->setPixmap(QPixmap::fromImage(display));
    //适应
    ui->label_show->setFixedSize(display.size());
    //更新显示窗口数据
    TGI.setX(this->geometry().x()+ui->widget_2->pos().x()+ui->label_show->geometry().x());
    TGI.setY(this->geometry().y()+ui->widget_2->pos().y()+ui->label_show->geometry().y()+ui->menubar->geometry().height());
    TGI.setWidth(ui->label_show->geometry().width());
    TGI.setHeight(ui->label_show->geometry().height());
}

void MainInterface::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    MatToShow();
#ifdef DEBUG 
    qDebug()<<"event->pos(): "<<event->pos();
    qDebug()<<"event->globalPos(): "<<event->globalPos();
    qDebug()<<"ui->widget_2->pos(): "<<ui->widget_2->pos();
    qDebug()<<"ui->label_show->pos(): "<<ui->label_show->pos();
    qDebug()<<"ui->label_show->geometry(): "<<ui->label_show->geometry();
    qDebug()<<"calc pos() x "<<ui->widget_2->pos().x()+ui->label_show->geometry().x();
    qDebug()<<"calc pos() y "<<ui->widget_2->pos().y()+ui->label_show->geometry().y()+ui->menubar->geometry().height();
    qDebug()<<"frameGeometry() "<<this->frameGeometry();
    qDebug()<<"geometry() "<<this->geometry();
    qDebug()<<"calc globalpos() x "<<this->geometry().x()+ui->widget_2->pos().x()+ui->label_show->geometry().x();
    qDebug()<<"calc globalpos() y"<<this->geometry().y()+ui->widget_2->pos().y()+ui->label_show->geometry().y()+ui->menubar->geometry().height();
    qDebug()<<"TGI.ShowQRect() "<<TGI.ShowQRect();
    qDebug()<<"";
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

void MainInterface::DeleteButton()
{
    if(bt_comfirm) delete bt_comfirm;
    if(bt_cancel) delete bt_cancel;
    if(ui_qcom) delete ui_qcom;
    ui_qcom=nullptr;
    bt_comfirm=bt_cancel=nullptr;
}