#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include "ui_MainInterface.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QPushButton>
#include <QImage>
#include <QDebug>
#include <QSlider>
#include "QComposition.h"
#include "ImageEdit.h"

class MainInterface : public QMainWindow {
    Q_OBJECT
    
public:
    MainInterface(QWidget* parent = nullptr);
    ~MainInterface();
    void CreateComAndCan();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
public slots:
    void OpenImage();
    void CreateQCOM();
    void MakeSpin();
    void MatToShow();
    void DeleteButton();
private:
    Ui_MainInterface* ui;
    QComposition* ui_qcom;
    QPushButton *bt_comfirm,*bt_cancel;
    QSlider* slider;
};

#endif // MAININTERFACE_H