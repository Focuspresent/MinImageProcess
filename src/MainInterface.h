#pragma once
#include "ui_MainInterface.h"
#include <QMainWindow>
#include <QString>

class MainInterface : public QMainWindow {
    Q_OBJECT
    
public:
    MainInterface(QWidget* parent = nullptr);
    ~MainInterface();

private:
    Ui_MainInterface* ui;
};