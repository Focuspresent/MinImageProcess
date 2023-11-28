#include "QComposition.h"
#include "Tool.hpp"

QComposition::QComposition(QWidget* parent)
    :QWidget(parent)
    ,ui(new Ui_QComposition)
{
    ui->setupUi(this);
}

QComposition::~QComposition()
{
    delete ui;
}