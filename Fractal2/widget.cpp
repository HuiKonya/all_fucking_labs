#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(900, 900);
    COUNT = 0;
    connect(ui->sb, SIGNAL(valueChanged(int)), this, SLOT(set_Count(int)));
    connect(ui->button, SIGNAL(clicked()), this, SLOT(repaint()));
}

void Widget::set_Count(int count) { this->COUNT = count; }

void Widget::draw(QPainter &painter, QVector<QPoint> points)
{
    QPoint points_arr[points.size()];
    for(size_t i = 0; i < points.size(); i++) points_arr[i] = points[i];
    painter.drawPolyline(points_arr, points.size());
}


void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1));

    QVector<QPoint> points;
    QVector<QPoint> prev_points;
    QPoint first_point(width() / 3, height() / 3 * 2 - 100);
    QPoint last_point(width() / 3 * 2, height() / 3 * 2 - 100);
    int length = last_point.x() - first_point.x();

    for(size_t n = 1, k = 1; n <= COUNT; n++, k*= 2)
    {
        if(n == 1)
        {
            if(COUNT == 1) painter.drawLine(first_point, last_point);
            continue;
        }


        if(n == 2)
        {
            points.push_back(first_point);
            points.push_back(QPoint(first_point.x() + length/2, first_point.y() - length/2));
            points.push_back(last_point);
            if(COUNT == 2) draw(painter, points);
            prev_points = points;
            points.clear();
            k = 1;
            continue;
        }


        if(!(n % 2))
        {
            if(n == 4 || n == 8 || n == 12 || n == 16 || n == 20 || n == 24) length = abs(prev_points[1].y() - prev_points[0].y());
            if(n == 6 || n == 10 || n == 14 || n == 18 || n == 22 || n == 26) length = abs(prev_points[1].x() - prev_points[0].x());

            for(int i = 0; i < k; i++)
            {
                points.push_back(prev_points[i]);
                if(prev_points[i + 1].x() > prev_points[i].x() && prev_points[i + 1].y() == prev_points[i].y())
                    points.push_back(QPoint(prev_points[i].x() + length/2, prev_points[i].y() - length/2));

                if(prev_points[i + 1].y() < prev_points[i].y() && prev_points[i + 1].x() == prev_points[i].x())
                    points.push_back(QPoint(prev_points[i].x() - length/2, prev_points[i].y() - length/2));

                if(prev_points[i + 1].x() < prev_points[i].x() && prev_points[i + 1].y() == prev_points[i].y())
                    points.push_back(QPoint(prev_points[i].x() - length/2, prev_points[i].y() + length/2));

                if(prev_points[i + 1].y() > prev_points[i].y() && prev_points[i + 1].x() == prev_points[i].x())
                    points.push_back(QPoint(prev_points[i].x() + length/2, prev_points[i].y() + length/2));
            }
        }


        if((n % 2))
        {
            for(int i = 0; i < k; i++)
            {
                points.push_back(prev_points[i]);
                if(prev_points[i].x() < prev_points[i + 1].x() && prev_points[i].y() > prev_points[i + 1].y())
                    points.push_back(QPoint(prev_points[i].x(), prev_points[i + 1].y()));

                if(prev_points[i].x() > prev_points[i + 1].x() && prev_points[i].y() > prev_points[i + 1].y())
                    points.push_back(QPoint(prev_points[i + 1].x(), prev_points[i].y()));

                if(prev_points[i].x() > prev_points[i + 1].x() && prev_points[i].y() < prev_points[i + 1].y())
                    points.push_back(QPoint(prev_points[i].x(), prev_points[i + 1].y()));

                if(prev_points[i].x() < prev_points[i + 1].x() && prev_points[i].y() < prev_points[i + 1].y())
                    points.push_back(QPoint(prev_points[i + 1].x(), prev_points[i].y()));

            }
        }

        points.push_back(prev_points.last());
        if(n == COUNT) draw(painter, points);
        prev_points = points;
        points.clear();
    }

}
