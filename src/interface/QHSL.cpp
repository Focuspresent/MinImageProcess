#include "QHSL.h"
#include "Tool.hpp"

QHSL::QHSL(QWidget* parent)
    :QWidget(parent)
    ,ui(new Ui_QHSL)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
}

QHSL::~QHSL()
{
    delete ui;
}

void QHSL::HSLCurMat()
{
    
}