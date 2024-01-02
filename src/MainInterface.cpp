#include "MainInterface.h"
#include "Tool.hpp"

MainInterface::MainInterface(QWidget* parent)
    :QMainWindow(parent)
    ,ui(new Ui_MainInterface)
{
    ui->setupUi(this);
    //数据
    ui_qcom=nullptr;
    ui_qhsl=nullptr;
    ui_qct=nullptr;
    ui_qtext=nullptr;
    bt_comfirm=nullptr;
    bt_cancel=nullptr;
    bt_show=nullptr;
    slider=nullptr;
    lineedit=nullptr;
    TGI.setShowQRect(ui->label_show->geometry());

    //连接槽
    connect(ui->pb_open,SIGNAL(clicked()),this,SLOT(OpenImage()));
    connect(ui->open,SIGNAL(triggered()),this,SLOT(OpenImage()));
    connect(ui->pb_save,SIGNAL(clicked()),this,SLOT(SaveImage()));
    connect(ui->save,SIGNAL(triggered()),this,SLOT(SaveImage()));
    connect(ui->ac_crop,SIGNAL(triggered()),this,SLOT(CreateQCOM()));
    connect(ui->ac_hsl,SIGNAL(triggered()),this,SLOT(CreateQHSL()));
    connect(ui->ac_curtone,SIGNAL(triggered()),this,SLOT(CreateQCT()));
    connect(ui->ac_curadj,SIGNAL(triggered()),this,SLOT(CreateQCT()));
    connect(ui->ac_text,SIGNAL(triggered()),this,SLOT(CreateQT()));
    connect(ui->ac_spin,SIGNAL(triggered()),this,SLOT(MakeSpin()));
    connect(ui->ac_exp,SIGNAL(triggered()),this,SLOT(MakeExposure()));
    connect(ui->ac_bri,SIGNAL(triggered()),this,SLOT(MakeBrightness()));
    connect(ui->ac_conra,SIGNAL(triggered()),this,SLOT(MakeContrastRatio()));
    connect(ui->ac_hisequ,SIGNAL(triggered()),this,SLOT(MakeHistogramEqualization()));
    connect(ui->ac_sha,SIGNAL(triggered()),this,SLOT(MakeSharpen()));
    connect(ui->ac_smo,SIGNAL(triggered()),this,SLOT(MakeSmooth()));
    connect(ui->ac_coltem,SIGNAL(triggered()),this,SLOT(MakeColorTemperature()));
    connect(ui->ac_tone,SIGNAL(triggered()),this,SLOT(MakeTone()));
    connect(ui->ac_lis,SIGNAL(triggered()),this,SLOT(MakeLightSense()));
    connect(ui->ac_satadj,SIGNAL(triggered()),this,SLOT(MakeSaturation()));
    connect(ui->ac_beauty,SIGNAL(triggered()),this,SLOT(MakeBeauty()));
}

MainInterface::~MainInterface()
{
    delete ui;
}

void MainInterface::OpenImage()
{
    QString filename=QFileDialog::getOpenFileName(this,"选择一个图片","./res","(All Imags(*.jpg *.png))");
    if(filename.isEmpty()){
        #ifdef DEBUG
            qDebug()<<"filename Empty";
        #endif
        return ;
    }
    //先前的按钮
    DeleteButton();
    //读取
    TGI.ReadCurMat(filename);
    //展示
    MatToShow();
}

void MainInterface::SaveImage()
{
    QString filename=QFileDialog::getSaveFileName(this,"选择一个路径",QCoreApplication::applicationFilePath());
    if(filename.isEmpty()){
        #ifdef DEBUG
            qDebug()<<"filename Empty";
        #endif 
        return ;
    }
    //确认
    TGI.Comfirm();
    //删除按钮
    DeleteButton();
    //展示
    MatToShow();
    //保存OriginMat;
    TGI.WriteCurMat(filename);
}

void MainInterface::CreateQCOM()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建界面
    MatToShow();
    if(ui_qcom!=nullptr){
        delete ui_qcom;
        ui_qcom=nullptr;
    }
    ui_qcom=new QComposition();
    ui_qcom->show();

    //确定和取消
    CreateComAndCan(false);

    connect(ui_qcom,SIGNAL(ChangeCurMat()),this,SLOT(MatToShow()));
    connect(bt_comfirm,&QPushButton::clicked,[this]()->void{
        ui_qcom->CropCurMat();
        DeleteButton();
    });
    connect(bt_cancel,&QPushButton::clicked,[this]()->void{
        DeleteButton();
    });
}

void MainInterface::CreateQHSL()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建界面
    if(ui_qhsl!=nullptr){
        delete ui_qhsl;
        ui_qhsl=nullptr;
    }
    ui_qhsl=new QHSL();
    ui_qhsl->show();

    //确定和取消
    CreateComAndCan(false);

    //显示
    CreateShow();

    connect(ui_qhsl,SIGNAL(ChangeCurMat()),this,SLOT(MatToShow()));
    connect(bt_show,&QPushButton::clicked,[this]()->void{
        if(ui_qhsl->isVisible()){
            ui_qhsl->hide();
        }else{
            ui_qhsl->show();
        }
    });
    connect(bt_comfirm,&QPushButton::clicked,[this]()->void{
        TGI.Comfirm();
        DeleteButton();
    });
    connect(bt_cancel,&QPushButton::clicked,[this]()->void{
        TGI.Cancel();
        MatToShow();
        DeleteButton();
    });
}

void MainInterface::CreateQCT()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建界面
    if(ui_qct!=nullptr){
        delete ui_qct;
        ui_qct=nullptr;
    }
    ui_qct=new QCurveTone();
    ui_qct->show();

    //确定和取消
    CreateComAndCan();

    //显示
    CreateShow();

    connect(ui_qct,SIGNAL(ChangeCurMat()),this,SLOT(MatToShow()));
    connect(bt_show,&QPushButton::clicked,[this]()->void{
        if(ui_qct->isVisible()){
            ui_qct->hide();
        }else{
            ui_qct->show();
        }
    });
}

void MainInterface::CreateQT()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建文本框
    if(ui_qtext!=nullptr){
        delete ui_qtext;
        ui_qtext=nullptr;
    }   
    ui_qtext=new QText();
    ui_qtext->show();

    //确定和取消
    CreateComAndCan(false);

    connect(bt_comfirm,&QPushButton::clicked,[this]()->void{
        QRect geo = ui_qtext->geometry();
        int x=geo.topLeft().x();
        int y=geo.topLeft().y();
        Text(ui_qtext->text().toLocal8Bit(),x-TGI.X(),y-TGI.Y()+geo.height(),cv::FONT_HERSHEY_SIMPLEX,1.0,cv::Scalar(255,255,255));
        MatToShow();
        TGI.Comfirm();
        DeleteButton();
    });
    connect(bt_cancel,&QPushButton::clicked,[this]()->void{
        TGI.Cancel();
        MatToShow();
        DeleteButton();
    });
}

void MainInterface::MakeSpin()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建水平滑动条
    CreateSliAndLin(-45,45);

    //确定和取消
    CreateComAndCan();

    connect(slider,&QSlider::valueChanged,[this](int pos)->void{
        Spin(pos,true);
        MatToShow();
    });
}

void MainInterface::MakeExposure()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建水平滑动条
    CreateSliAndLin(-100,100);

    //确定和取消
    CreateComAndCan();

    //映射需要的值
    //?-mi/ma-mi=pos-tmi/tma-tmi
    double alphaMin=0.5,alphaMax=1.5;
    int betaMin=-50,betaMax=50;
    int tma=slider->maximum(),tmi=slider->minimum();

    connect(slider,&QSlider::valueChanged,[this,alphaMin,alphaMax,betaMin,betaMax,tmi,tma](int pos)->void{
        double alpha=(double)(alphaMax-alphaMin)*((double)(pos-tmi)/(tma-tmi))+alphaMin;
        int beta=(int)(betaMax-betaMin)*((double)(pos-tmi)/(tma-tmi))+betaMin;
        Exposure(alpha,beta);
        MatToShow();
    });
}

void MainInterface::MakeBrightness()
{   
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建水平滑动条
    CreateSliAndLin(-100,100);

    //创建确定和取消
    CreateComAndCan();

    connect(slider,&QSlider::valueChanged,[this](int pos)->void{
        Brightness(pos);
        MatToShow();
    });
}

void MainInterface::MakeContrastRatio()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建水平滑动条
    CreateSliAndLin(-100,100);

    //创建确定和取消
    CreateComAndCan();

    //映射
    double conraMin=0.0,conraMax=2.0;
    int tma=slider->maximum(),tmi=slider->minimum();

    connect(slider,&QSlider::valueChanged,[this,conraMax,conraMin,tma,tmi](int pos)->void{
        double conra=(double)(conraMax-conraMin)*((double)(pos-tmi)/(tma-tmi))+conraMin;
        ContrastRatio(conra);
        MatToShow();
    });
}

void MainInterface::MakeHistogramEqualization()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //确定和取消
    CreateComAndCan();

    //直方图均衡化
    HistogramEqualization();
    //显示
    MatToShow();
}

void MainInterface::MakeSharpen()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建水平滑动条
    CreateSliAndLin(0,100);

    //确定和取消
    CreateComAndCan();
   
    connect(slider,&QSlider::valueChanged,[this](int pos)->void{
        Sharpen(pos);
        MatToShow();
    });
}

void MainInterface::MakeSmooth()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建水平滑动条
    CreateSliAndLin(0,1000);

    //确定和取消
    CreateComAndCan();

    connect(slider,&QSlider::valueChanged,[this](double value)->void{
        Smooth(value);
        MatToShow();
    });
}

void MainInterface::MakeColorTemperature()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建水平滑动条
    CreateSliAndLin(-100,100);

    //确定和取消
    CreateComAndCan();

    connect(slider,&QSlider::valueChanged,[this](int pos)->void{
        ColorTemperature(pos);
        MatToShow();
    });
}

void MainInterface::MakeTone()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建水平滑动条
    CreateSliAndLin(-100,100);

    //确定和取消
    CreateComAndCan();

    connect(slider,&QSlider::valueChanged,[this](int pos)->void{
        Tone(pos);
        MatToShow();
    });
}

void MainInterface::MakeLightSense()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建水平滑动条
    CreateSliAndLin(-100,100);

    //确定和取消
    CreateComAndCan();

    //映射需要的值
    //?-mi/ma-mi=pos-tmi/tma-tmi
    double alphaMin=0.5,alphaMax=1.0;
    int betaMin=-50,betaMax=50;
    int tma=slider->maximum(),tmi=slider->minimum();

    connect(slider,&QSlider::valueChanged,[this,alphaMin,alphaMax,betaMin,betaMax,tmi,tma](int pos)->void{
        double alpha=(double)(alphaMax-alphaMin)*((double)(pos-tmi)/(tma-tmi))+alphaMin;
        int beta=(int)(betaMax-betaMin)*((double)(pos-tmi)/(tma-tmi))+betaMin;
        LightSense(alpha,beta);
        MatToShow();
    });
}

void MainInterface::MakeSaturation()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建水平滑动条
    CreateSliAndLin(-100,100);

    //确定和取消
    CreateComAndCan();

    //映射
    double saturationMin=0.0,saturationMax=2.0;
    int tma=slider->maximum(),tmi=slider->minimum();

    connect(slider,&QSlider::valueChanged,[this,saturationMax,saturationMin,tmi,tma](int pos)->void{
        double factor=(double)(saturationMax-saturationMin)*((double)(pos-tmi)/(tma-tmi))+saturationMin;
        Saturation(factor);
        MatToShow();
    });
}

void MainInterface::MakeBeauty()
{
    if(TGMAT.empty()){
        #ifdef DEBUG
            qDebug()<<"CurMat Empty";
        #endif 
        return ;
    }
    //创建水平滑动条
    CreateSliAndLin(0,100);

    //确定和取消
    CreateComAndCan();

    connect(slider,&QSlider::valueChanged,[this](int pos)->void{
        Beauty(pos);
        MatToShow();
    });
}

//更新显示窗口数据
void MainInterface::UpdateShow()
{
    /*TGI.setX(this->geometry().x()+ui->widget_2->pos().x()+ui->label_show->geometry().x());
    TGI.setY(this->geometry().y()+ui->widget_2->pos().y()+ui->label_show->geometry().y()+ui->menubar->geometry().height());*/
    auto p=ui->widget_2->mapToGlobal(ui->label_show->pos());
    TGI.setX(p.x());
    TGI.setY(p.y());
    TGI.setWidth(ui->label_show->geometry().width());
    TGI.setHeight(ui->label_show->geometry().height());
}

void MainInterface::MatToShow()
{   
    UpdateShow();
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
    QPixmap pixmap=QPixmap::fromImage(display);
    //如果小于显示窗口的长宽
    if(pixmap.width()<=ui->label_show->geometry().width()&&pixmap.height()<=ui->label_show->geometry().height()){
        ui->label_show->setFixedSize(pixmap.size());
        ui->label_show->setPixmap(pixmap);
        UpdateShow();
        TGI.setScaleWidth(1.0);
        TGI.setScaleHeight(1.0);
        return ;
    }
    pixmap.scaled(ui->label_show->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->label_show->setPixmap(pixmap);
    ui->label_show->setScaledContents(true);
    TGI.setScaleWidth(1.0*ui->label_show->geometry().width()/TGOMAT.cols);
    TGI.setScaleHeight(1.0*ui->label_show->geometry().height()/TGOMAT.rows);
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
    if(bt_show) delete bt_show;
    if(ui_qcom) delete ui_qcom;
    if(ui_qhsl) delete ui_qhsl;
    if(ui_qct) delete ui_qct;
    if(ui_qtext) delete ui_qtext;
    if(slider) delete slider;
    if(lineedit) delete lineedit;
    lineedit=nullptr;
    slider=nullptr;
    ui_qcom=nullptr;
    ui_qhsl=nullptr;
    ui_qct=nullptr;
    ui_qtext=nullptr;
    bt_comfirm=bt_cancel=bt_show=nullptr;
}

void MainInterface::CreateComAndCan(bool flag)
{
    if(bt_comfirm!=nullptr){
        delete bt_comfirm;
        bt_comfirm=nullptr;
    }
    bt_comfirm=new QPushButton(this);
    bt_comfirm->setWindowFlags(Qt::FramelessWindowHint);
    bt_comfirm->show();
    bt_comfirm->setText("确定");
    bt_comfirm->setGeometry(0,ui->menubar->height(),60,30);

    if(bt_cancel!=nullptr){
        delete bt_cancel;
        bt_cancel=nullptr;
    }
    bt_cancel=new QPushButton(this);
    bt_cancel->setWindowFlags(Qt::FramelessWindowHint);
    bt_cancel->show();
    bt_cancel->setText("取消");
    bt_cancel->setGeometry(bt_comfirm->geometry().width(),ui->menubar->height(),60,30);

    if(flag){
        connect(bt_comfirm,&QPushButton::clicked,[this]()->void{
            TGI.Comfirm();
            MatToShow();
            DeleteButton();
        });
        connect(bt_cancel,&QPushButton::clicked,[this]()->void{
            TGI.Cancel();
            MatToShow();
            DeleteButton();
        });
    }
}

void MainInterface::CreateShow()
{
    if(bt_show!=nullptr){
        delete bt_show;
        bt_show=nullptr;
    }
    bt_show=new QPushButton(this);
    bt_show->setWindowFlags(Qt::FramelessWindowHint);
    bt_show->show();
    bt_show->setText("显示");
    bt_show->setGeometry(bt_comfirm->geometry().width()+bt_cancel->geometry().width(),ui->menubar->height(),60,30);
}

void MainInterface::CreateSliAndLin(int MinValue,int MaxValue)
{
   if(slider!=nullptr){
        delete slider;
        slider=nullptr;
    }
    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(MinValue,MaxValue);
    slider->setValue(0);
    slider->show();
    slider->setGeometry(50,height()-30,160,22);

    if(lineedit!=nullptr){
        delete lineedit;
        lineedit=nullptr;
    }

    lineedit=new QLineEdit(this);
    lineedit->setWindowFlags(Qt::FramelessWindowHint);
    lineedit->setText("0");
    lineedit->setStyleSheet("border: none;");
    lineedit->show();

    QStyle* style = slider->style();
    int sliderWidth = style->pixelMetric(QStyle::PM_SliderLength, nullptr, slider);
    int mi=slider->minimum(),ma=slider->maximum();

    int x=(int)slider->geometry().width()*((double)abs(0-mi)/abs(ma-mi));
    lineedit->setGeometry(slider->geometry().x()-sliderWidth/2+x,slider->geometry().y()-slider->geometry().height(),slider->geometry().height(),slider->geometry().height());

    connect(slider,&QSlider::valueChanged,[this,sliderWidth,mi,ma](int pos)->void{
        lineedit->setText(QString(std::to_string(pos).c_str()));
        int x=(int)slider->geometry().width()*((double)abs(pos-mi)/abs(ma-mi));
        lineedit->setGeometry(slider->geometry().x()-sliderWidth/2+x,slider->geometry().y()-slider->geometry().height(),slider->geometry().height(),slider->geometry().height());
    });
    connect(lineedit,&QLineEdit::textChanged,[this,MinValue,MaxValue](const QString& text)->void{
        int value=text.toInt();
        if(value>MaxValue) value=MaxValue;
        else if(value<MinValue) value=MinValue;
        slider->setValue(value);
        slider->triggerAction(QAbstractSlider::SliderMove);
    });
}