#ifndef QTEXTHELP_H
#define QTEXTHELP_H

#include "ui_QTextHelp.h"
#include <QWidget>
#include <QMouseEvent>
#include <QColor>
#include <QColorDialog>
#include <QPoint>
#include <QLineEdit>
#include <QString>
#include <QDebug>
#include <QComboBox>
#include "Tool.hpp"

class QTextHelp:public QWidget{
    Q_OBJECT

public:
    QTextHelp(QWidget* parent=nullptr);
    ~QTextHelp();
    cv::Scalar QColorToScalar();

    QColor color=Qt::white;
    int fontFace=cv::FONT_HERSHEY_SIMPLEX;
    double fontScale=1.0;
    int thickness=1;
signals:
    void ChangeText();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
public slots:
private:
    Ui_QTextHelp* ui;
    QPoint pos;

    bool is_press;
};

#endif //QTEXTHELP_H