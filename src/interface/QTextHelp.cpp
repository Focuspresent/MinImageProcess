#include "QTextHelp.h"

QTextHelp::QTextHelp(QWidget* parent)
    :QWidget(parent)
    ,ui(new Ui_QTextHelp)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->inputfs->setText("1.0");
    ui->inputthick->setText("1");

    connect(ui->color,&QPushButton::clicked,[this](){
        color = QColorDialog::getColor(Qt::white, nullptr, "选择颜色");
        #ifdef DEBUG
            qDebug() << "color:" << color;
        #endif
        emit ChangeText();
    });
    connect(ui->inputfs,&QLineEdit::returnPressed,[this](){
        double t=ui->inputfs->text().toDouble();
        if(t<0) t=1.0;
        if(t>2) t=2.0;
        fontScale=t;
        #ifdef DEBUG
            qDebug()<<"fontScale: "<<fontScale;
        #endif
        ui->inputfs->setText(QString::number(fontScale));
        emit ChangeText();
    });
    connect(ui->inputthick,&QLineEdit::returnPressed,[this](){
        int t=ui->inputthick->text().toInt();
        if(t<0) t=1;
        if(t>5) t=5;
        thickness=t;
        #ifdef DEBUG
            qDebug()<<"thickness: "<<thickness;
        #endif
        ui->inputthick->setText(QString::number(thickness));
        emit ChangeText();
    });
    connect(ui->ff, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        fontFace = index;
        #ifdef DEBUG
            qDebug() << "fontFace: " << fontFace;
        #endif
        emit ChangeText();
    });
}

QTextHelp::~QTextHelp()
{
    delete ui;
}

cv::Scalar QTextHelp::QColorToScalar(){
    return std::move(cv::Scalar(color.blue(), color.green(), color.red(), color.alpha()));
}

void QTextHelp::mousePressEvent(QMouseEvent* event)
{
    if(event->buttons()==Qt::LeftButton){
        is_press=true;
        pos=event->pos();
    }
}

void QTextHelp::mouseMoveEvent(QMouseEvent* event)
{
    if(is_press){
        QPoint newPos=event->globalPos()-pos;
        move(newPos);
    }
}

void QTextHelp::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->buttons()==Qt::LeftButton){
        is_press=false;
    }
}