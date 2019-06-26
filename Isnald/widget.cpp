#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(1000, 1000);
    srand(time(NULL));
}

void Widget::wheelEvent(QWheelEvent *ev)
{
    if(ev->delta() != 0) update();
}

void Widget::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::green));
    painter.setBrush(Qt::green);


    QPolygon polygon;
    int x0 = width()/5 + 100;
    int y0 = height()/5 + 100;
    int x = x0;
    int y = y0;


    int n = rand() % 75 + 25;
    int inc = rand() % 9 + 3;

    for(int i = 0; i < n; i++)
    {
        int dir = rand() % 2 + 1;
        x += rand() % inc + 1;

        switch(dir)
        {
            case 1: y += rand() % inc + 1; break;
            case 2: y -= rand() % inc + 1; break;
        }

        if(x >= width() || y >= height() || x < 0 || y < 0) continue;

        polygon << QPoint(x, y);
    }


    n = rand() % 75 + 25;
    inc = rand() % 10 + 1;


    for(int i = 0; i < n; i++)
    {
        int dir = rand() % 2 + 1;
        y += rand() % inc + 1;

        switch(dir)
        {
            case 1: x += rand() % inc + 1; break;
            case 2: x -= rand() % inc + 1; break;
        }

        if(x >= width() || y >= height() || x < 0 || y < 0) continue;

        polygon << QPoint(x, y);
    }

    n = rand() % 75 + 25;
    inc = rand() % 10 + 1;




    for(int i = 0; i < n; i++)
    {
        int dir = rand() % 2 + 1;
        x -= rand() % inc + 1;

        switch(dir)
        {
            case 1: y += rand() % inc + 1; break;
            case 2: y -= rand() % inc + 1; break;
        }

        if(x >= width() || y >= height() || x < 0 || y < 0) continue;

        polygon << QPoint(x, y);
    }


    n = rand() % 75 + 25;
    inc = rand() % 8 + 4;


    for(int i = 0; i < n; i++)
    {
        int dir = rand() % 2 + 1;
        y -= rand() % inc + 1;

        switch(dir)
        {
            case 1: x += rand() % inc + 1; break;
            case 2: x -= rand() % inc + 1; break;
        }

        if(x >= width() || y >= height() || x < 0 || y < 0) continue;

        polygon << QPoint(x, y);
    }



    while(true)
    {
        x = rand() % 250 + 1;
        y = rand() % 250 + 1;
        int znak = rand() % 4 + 1;

        painter.save();

        switch(znak)
        {
            case 1: polygon.translate(x, y); break;
            case 2: polygon.translate(-x, -y); break;
            case 3: polygon.translate(-x, y); break;
            case 4: polygon.translate(x, -y); break;
        }

        bool flag = true;

        for(int i = 0; i < polygon.size(); i++)
        {
            if(
            polygon.point(i).x() >= width()  ||
            polygon.point(i).y() >= height() ||
            polygon.point(i).x() <= 0        ||
            polygon.point(i).y() <= 0
            ) flag = false;
        }

        if(flag) break;
        else painter.restore();

    }

    painter.drawPolygon(polygon);


}
