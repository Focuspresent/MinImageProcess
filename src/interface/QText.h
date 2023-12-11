#ifndef QTEXT_H
#define QTEXT_H

#include <QWidget>
#include <QLineEdit>
#include <QPoint>
#include <QMouseEvent>

class QText:public QLineEdit{
public:
    QText(QWidget* parent=nullptr);
    ~QText();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
private:
    QPoint pos;
};

#endif //QTEXT_H