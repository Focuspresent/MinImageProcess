#include "MainInterface.h"

MainInterface::MainInterface(QWidget* parent)
    :QMainWindow(parent)
    ,ui(new Ui_MainInterface)
{
    ui->setupUi(this);
}

MainInterface::~MainInterface()
{
    delete ui;
}