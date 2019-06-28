#pragma once
#include <QPainter>
#include "math.h"
#include <QtWidgets>

namespace Ui { class Widget; }

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    double cos_sin(qreal S);
private:
    Ui::Widget *ui;
    int x0, x1, y0, y1;
    QTimer *timer;
    int seconds;
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void time();
};
