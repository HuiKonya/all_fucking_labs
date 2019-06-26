#pragma once
#include <QtWidgets>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    void draw(QPainter &painter, QVector<QPoint> points);
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Widget *ui;
    int COUNT;

private slots:
    void set_Count(int count);
};

