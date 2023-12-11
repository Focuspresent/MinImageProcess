#include "QText.h"

QText::QText(QWidget* parent)
    :QLineEdit(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("QLineEdit { background-color: transparent; }");
    setStyleSheet("QLineEdit { border: 1px solid black; }");
}

QText::~QText()
{
}

void QText::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        pos = event->pos();
    }
    QLineEdit::mousePressEvent(event);
}

void QText::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        int dx = event->pos().x() - pos.x();
        int dy = event->pos().y() - pos.y();
        move(x() + dx, y() + dy);
    }
    QLineEdit::mouseMoveEvent(event);
}