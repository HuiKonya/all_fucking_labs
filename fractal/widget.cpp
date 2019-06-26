#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->button, SIGNAL(clicked()), SLOT(update()));
    connect(ui->sb, SIGNAL(valueChanged(int)), SLOT(Change_Count_of_lines(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Change_Count_of_lines(int n)
{
    this->count_of_lines = n;
}

void Widget::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setPen(QPen(Qt::red));
   painter.setBrush(QBrush(Qt::red));

   double old_left_x = 395;
   double old_right_x = 395;
   double new_left_x = 0;
   double new_right_x = 0;
   double main_left_x = 0;
   double main_right_x = 0;
   double old_y = 900 * 0.8;
   double new_y;
   double k = 1.0;
   QVector<double> already_there;
   QVector<QPointF> points_array;
   QVector<QPointF> temp_points_array;
   count = 1;



   painter.drawEllipse(QPointF(375, 900 * 0.8), 3.0, 3.0);




   for(int i = 0; i < count_of_lines - 1; i++)
   {
       k -= 0.05;

       points(old_left_x, new_left_x, main_left_x, old_right_x, new_right_x, main_right_x, old_y, new_y, k, points_array, already_there);

       for(int i = 0; i < points_array.size(); i++)
       {
           painter.drawEllipse(points_array[i], 3.0, 3.0);
       }

       painter.drawLine(QPointF(375, 900 * 0.8), QPointF(375, 720 - 70 * k));

       for(int i = 0, j = 0; i < temp_points_array.size(); i++)
       {
           painter.drawLine(temp_points_array[i], points_array[j]);
           j++;
           painter.drawLine(temp_points_array[i], points_array[j]);
       }


       temp_points_array = points_array;
       points_array.clear();

       count+=1;
   }
}

void Widget::points(double &old_left_x, double &new_left_x, double &main_left_x,
                              double &old_right_x, double &new_right_x, double &main_right_x,
                              double &old_y, double &new_y, double koef, QVector<QPointF> &points_array ,QVector<double> &already_there)
{
    already_there.push_back(old_left_x);
    already_there.push_back(old_right_x);

    main_left_x = old_left_x - 20;
    main_right_x = old_right_x + 20;

    new_left_x = old_left_x;
    old_left_x = main_left_x;

    new_right_x = old_right_x;
    old_right_x = main_right_x;

    new_y = old_y - 70 * koef;
    old_y = new_y;

    for(int i = 0, k = 0; i < count; i++, k+=20)
    {
        if(already_there.contains(main_left_x + k)) k+= 20;

        points_array.push_back(QPointF(main_left_x + k, new_y));
    }

}


