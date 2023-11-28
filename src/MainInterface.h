#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include "ui_MainInterface.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include "Tool.hpp"

class MainInterface : public QMainWindow {
    Q_OBJECT
    
public:
    MainInterface(QWidget* parent = nullptr);
    ~MainInterface();
public slots:
    void OpenImage();
    void MatToShow();
private:
    Ui_MainInterface* ui;
};

#endif // MAININTERFACE_H