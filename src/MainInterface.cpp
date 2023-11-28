#include "MainInterface.h"

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

void MainInterface::MatToShow(){
    //转成QImage
    QImage display=QImage(TGMAT.data,TGMAT.cols,TGMAT.rows,TGMAT.cols*TGMAT.channels(),QImage::Format_RGB888);
    //放到组件中
    ui->label_show->setPixmap(QPixmap::fromImage(display));
    //适应
    ui->label_show->setScaledContents(true);
}