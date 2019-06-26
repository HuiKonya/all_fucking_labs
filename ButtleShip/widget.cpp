#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setFixedSize(900, 900);
    setWindowTitle("Battleship");
    inc_colour = 0;
    draw_is_possible = true;

}

void Widget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::white);
    painter.setPen(QPen(Qt::black, 2));

    double inc = (700) / 10;
    double x0 = 100;
    double y0 = 100;
    double inc_x = x0;
    double inc_y = y0;

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            QPointF p_11(inc_x, inc_y);
            inc_y += inc;
            QPointF p_21(inc_x, inc_y);
            inc_x += inc;
            QPointF p_22(inc_x, inc_y);
            inc_y -= inc;
            QPointF p_12(inc_x, inc_y);

            matrix[i][j] << p_11 << p_21 << p_22 << p_12;

        }
        inc_y += inc;
        inc_x = x0;
    }

    if(draw_is_possible)
        for (int i = 0; i < 10; i++) { for (int j = 0; j < 10; j++) ship[i][j] = 0; }

    if(draw_is_possible)
        for(int i = 1; i <= 4; i++) logic(i);


    draw(&painter);

    painter.setPen(QPen(Qt::black, 3));
    painter.drawLine(QPointF(100, 100), QPointF(100, 800));
    painter.drawLine(QPointF(100, 100), QPointF(800, 100));
    painter.drawLine(QPointF(800, 100), QPointF(800, 800));
    painter.drawLine(QPointF(100, 800), QPointF(800, 800));

    for(int i = 0; i < 10; i ++)
    {
        for(int j = 0; j < 10; j++)
            matrix[i][j].clear();
    }

}

void Widget::logic(int per)
{
    DIR dir;
    int count_for_FOR = 0;

        switch (per)
        {
        case 1: count_for_FOR = 4; break;
        case 2: count_for_FOR = 3; break;
        case 3: count_for_FOR = 2; break;
        case 4: count_for_FOR = 1; break;
        }

        while (per)
        {
            int temp_x;
            int temp_y;

            do
            {
                x = rand() % 10;
                y = rand() % 10;
                temp_dir = 1 + rand() % 4;
                temp_x = x;
                temp_y = y;
                setting_off = false;

                switch (temp_dir)
                {
                case 1: dir = UP; break;
                case 2: dir = DOWN; break;
                case 3: dir = LEFT; break;
                case 4: dir = RIGHT; break;
                }

                for (int i = 0; i < count_for_FOR; i++)
                {
                    if (x < 0 || y < 0 || x >= 10 || y >= 10)
                    {
                        setting_off = true;
                        break;
                    }

                    if (
                        ship[x][y] == ch ||
                        ship[x][y + 1] == ch ||
                        ship[x][y - 1] == ch ||
                        ship[x + 1][y] == ch ||
                        ship[x + 1][y + 1] == ch ||
                        ship[x + 1][y - 1] == ch ||
                        ship[x - 1][y] == ch ||
                        ship[x - 1][y + 1] == ch ||
                        ship[x - 1][y - 1] == ch
                        )
                    {
                        setting_off = true;
                        break;
                    }

                    switch (dir)
                    {
                    case UP: y--; break;
                    case DOWN: y++; break;
                    case LEFT: x--; break;
                    case RIGHT: x++; break;
                    }

                }

            } while (setting_off);

            if (!setting_off)
            {
                x = temp_x;
                y = temp_y;

                for (int i = 0; i < count_for_FOR; i++)
                {
                    ship[x][y] = ch;
                    switch (dir)
                    {
                    case UP: y--; break;
                    case DOWN: y++; break;
                    case LEFT: x--; break;
                    case RIGHT: x++; break;
                    }
                }
            }
            per--;
        }
}

void Widget::draw(QPainter *painter)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
                if (ship[i][j] == ch)
                {
                    colour_changed(painter);
                    painter->drawPolygon(matrix[i][j]);

                }

                else
                {
                    painter->setBrush(Qt::white);
                    painter->drawPolygon(matrix[i][j]);
                }
        }

    }
}

void Widget::wheelEvent(QWheelEvent *event)
{
     if(event->delta() > 0)
     {
         draw_is_possible = true;
         repaint();
     }

     else if(event->delta() < 0)
     {
         draw_is_possible = false;
         inc_colour++;
         if(inc_colour == 16) inc_colour = 0;
         repaint();
     }

     update();
}

void Widget::colour_changed(QPainter *painter)
{
    switch (inc_colour)
    {
        case 0: painter->setBrush(Qt::black); break;
        case 1: painter->setBrush(Qt::darkGray); break;
        case 2: painter->setBrush(Qt::gray); break;
        case 3: painter->setBrush(Qt::lightGray); break;
        case 4: painter->setBrush(Qt::red); break;
        case 5: painter->setBrush(Qt::green); break;
        case 6: painter->setBrush(Qt::blue); break;
        case 7: painter->setBrush(Qt::cyan); break;
        case 8: painter->setBrush(Qt::magenta); break;
        case 9: painter->setBrush(Qt::yellow); break;
        case 10: painter->setBrush(Qt::darkRed); break;
        case 11: painter->setBrush(Qt::darkGreen); break;
        case 12: painter->setBrush(Qt::darkBlue); break;
        case 13: painter->setBrush(Qt::darkCyan); break;
        case 14: painter->setBrush(Qt::darkMagenta); break;
        case 15: painter->setBrush(Qt::darkYellow); break;
    }
}
