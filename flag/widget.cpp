#include "widget.h"
#include "ui_widget.h"
#include <QtCore>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer;
    seconds = 0;
    connect(timer, SIGNAL(timeout()),this, SLOT(time()));
}


void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    qreal S=0;
    int length = 25;
    //int amplitude = (y1 - y0) / 25;
    int amplitude = 15;
    double period = (x1 - x0) / 7.9;
    int height = (y1 - y0) / 3;
    QPolygonF polygon;

    for(int i=0;i < length; i++)
    {
        int remove = 0;

        QPointF p_one_1(x0 + S * period, y0 + remove - amplitude * cos_sin(S)); remove += height;
        QPointF p_one_2(x0 + S * period, y0 + remove - amplitude * cos_sin(S)); remove += height;
        QPointF p_one_3(x0 + S * period, y0 + remove - amplitude * cos_sin(S)); remove += height;
        QPointF p_one_4(x0 + S * period, y0 + remove - amplitude * cos_sin(S)); remove = 0;

        S += 3.14/10;

        QPointF p_two_1(x0 + S * period, y0 + remove - amplitude * cos_sin(S)); remove += height;
        QPointF p_two_2(x0 + S * period, y0 + remove - amplitude * cos_sin(S)); remove += height;
        QPointF p_two_3(x0 + S * period, y0 + remove - amplitude * cos_sin(S)); remove += height;
        QPointF p_two_4(x0 + S * period, y0 + remove - amplitude * cos_sin(S)); remove = 0;

        painter.setPen(QPen(Qt::black, 1, Qt::NoPen));

        painter.setBrush(QBrush(Qt::white));
        polygon << p_one_1 << p_one_2 << p_two_2 << p_two_1;
        painter.drawPolygon(polygon);
        polygon.clear();

        painter.setBrush(QBrush(Qt::blue));
        polygon << p_one_2 << p_one_3 << p_two_3 << p_two_2;
        painter.drawPolygon(polygon);
        polygon.clear();

        painter.setBrush(QBrush(Qt::red));
        polygon << p_one_3 << p_one_4 << p_two_4 << p_two_3;
        painter.drawPolygon(polygon);
        polygon.clear();

        painter.setPen(QPen(Qt::black, 1));

        painter.drawLine(p_one_1, p_two_1);
        painter.drawLine(p_one_2, p_two_2);
        painter.drawLine(p_one_3, p_two_3);
        painter.drawLine(p_one_4, p_two_4);

        if( i == length - 1)
        {
            if(seconds % 2) painter.drawLine(x0, y0 - 15, x0, y0 - 15 + height * 3);
            else painter.drawLine(x0, y0, x0, y0 + height * 3);

            painter.drawLine(p_two_1, p_two_4);
        }

    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    x0 = event->x();
    y0 = event->y();
    update();
    timer->stop();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    x1 = event->x();
    y1 = event->y();
    update();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    x1 = event->x();
    y1 = event->y();
    repaint();
    timer->start(1000);
}

void Widget::time()
{
    seconds++;
    repaint();
}

double Widget::cos_sin(qreal S)
{
    if(seconds %2) return cos(S);
     else return sin(S);
}
