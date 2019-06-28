#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Saw");
    setFixedSize(900, 900);
    timer = new QTimer;
    ui->button->setCheckable(1);
    ui->button->setChecked(0);

    brush_is_possible = true;
    speed = 0;
    light = 150;
    index_colour = 6;
    speed_inc = 0.01; // 0.001 - 0.05
    count_of_cogs = 36; // 100 - 10
    height_of_cogs = 50;  // 100 - 10
    radius = 250; // 50 - 300


    settings.temp_radius = radius;
    settings.temp_count_of_cogs = count_of_cogs;
    settings.temp_height_of_cogs = height_of_cogs;
    settings.temp_speed_inc = speed_inc;


    connect(timer, SIGNAL(timeout()), SLOT(inc()));
    connect(ui->button, SIGNAL(clicked()), SLOT(start()));
    connect(timer, SIGNAL(timeout()), SLOT(update()));


    connect(ui->button_settings, SIGNAL(clicked()), &settings, SLOT(show()));
    connect(ui->button_settings, SIGNAL(clicked()), this, SLOT(set_settings()));

    connect(settings.ui->sb_1, SIGNAL(valueChanged(int)), this, SLOT(setting_values(int)));
    connect(settings.ui->sb_2, SIGNAL(valueChanged(int)), this, SLOT(setting_values(int)));
    connect(settings.ui->sb_3, SIGNAL(valueChanged(int)), this, SLOT(setting_values(int)));
    connect(settings.ui->sb_4, SIGNAL(valueChanged(int)), this, SLOT(setting_values(int)));

    connect(settings.ui->button_save, SIGNAL(clicked()), this, SLOT(values_save()));
    connect(settings.ui->button_cancel, SIGNAL(clicked()), &settings, SLOT(reject()));
    connect(settings.ui->button_cancel, SIGNAL(clicked()), this, SLOT(restore_brush()));

    connect(settings.ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(set_index_colour(int)));
    connect(settings.ui->sb_5, SIGNAL(valueChanged(int)), this, SLOT(set_light(int)));
}


void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);


    if(brush_is_possible) setting_brush(painter);
    if(!brush_is_possible)
    {
        painter.setBrush(temp_br);
        index_colour = temp_index_colour;
        light = temp_light;
        brush_is_possible = true;
    }

    painter.setPen(QPen(Qt::black, 3, Qt::NoPen));
    painter.drawEllipse(QPointF(width() / 2, height() / 2), radius, radius);
    painter.setPen(QPen(Qt::black, 3));

    drawSaw(painter, width() / 2, height() / 2);
}


void Widget::drawSaw(QPainter &painter, double x0, double y0)
{

    for(int i = 0; i < count_of_cogs; i++)
    {
        double angle = 3.1416 * 2 * i / count_of_cogs;

        double x1 = x0 + cos(angle + speed) * radius;
        double y1 = y0 + sin(angle + speed) * radius;


        double x2 = x0 + cos(angle + speed) * (radius + height_of_cogs);
        double y2 = y0 + sin(angle + speed) * (radius + height_of_cogs);

        i++;
        angle = 3.1416 * 2 * i / count_of_cogs;
        double next_x1 = x0 + cos(angle + speed) * radius;
        double next_y1 = y0 + sin(angle + speed) * radius;
        i--;

        painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
        painter.drawLine(QPointF(x2, y2), QPointF(next_x1, next_y1));

        painter.setPen(QPen(Qt::black, 3, Qt::NoPen));

        QPolygonF polygon;
        polygon << QPointF(x1, y1) << QPointF(x2, y2) << QPointF(next_x1, next_y1);
        painter.drawPolygon(polygon);

        painter.setPen(QPen(Qt::black, 3));
    }
}


void Widget::start()
{
    if(ui->button->isChecked())
    {
        timer->start(1);
        ui->button->setText("Остановить");
    }
    else if(!ui->button->isChecked())
    {
        timer->stop();
        ui->button->setText("Запустить");
    }
}


void Widget::inc()
{
    speed += speed_inc;
}

void Widget::set_settings()
{
    settings.ui->sb_1->setValue(radius);
    settings.ui->sb_2->setValue(count_of_cogs);
    settings.ui->sb_3->setValue(height_of_cogs);
    settings.ui->sb_4->setValue((int)(speed_inc * 1000));
    settings.ui->sb_5->setValue(light);
    settings.ui->comboBox->setCurrentIndex(index_colour);

}


void Widget::setting_values(int value)
{
    QString obj_name = sender()->objectName();

    if(obj_name == "sb_1") settings.temp_radius = value;
    else if(obj_name == "sb_2") settings.temp_count_of_cogs = value;
    else if(obj_name == "sb_3") settings.temp_height_of_cogs = value;
    else if(obj_name == "sb_4") settings.temp_speed_inc = 0.001 * (double)value;
}


void Widget::values_save()
{
    radius = settings.temp_radius;
    count_of_cogs = settings.temp_count_of_cogs;
    height_of_cogs = settings.temp_height_of_cogs;
    speed_inc = settings.temp_speed_inc;
    settings.reject();  
}



void Widget::set_index_colour(int index)
{
    index_colour = index;
}

void Widget::set_light(int light)
{
    this->light = light;
}

void Widget::setting_brush(QPainter &painter)
{
   switch(index_colour)
   {
       case 0: painter.setBrush(QColor(Qt::red).light(light)); break;
       case 1: painter.setBrush(QColor(Qt::green).light(light)); break;
       case 2: painter.setBrush(QColor(Qt::blue).light(light)); break;
       case 3: painter.setBrush(QColor(Qt::cyan).light(light)); break;
       case 4: painter.setBrush(QColor(Qt::magenta).light(light)); break;
       case 5: painter.setBrush(QColor(Qt::yellow).light(light)); break;

       case 6: QLinearGradient gradient(width()/4, height()/4, width()/4 * 3, height()/4 * 3);
               gradient.setColorAt(0, Qt::red);
               gradient.setColorAt(0.2, Qt::yellow);
               gradient.setColorAt(0.4, Qt::green);
               gradient.setColorAt(0.6, Qt::cyan);
               gradient.setColorAt(0.8, Qt::blue);
               gradient.setColorAt(1, Qt::magenta);
               painter.setBrush(gradient);
               break;
   }

   temp_br = painter.brush();
   temp_index_colour = index_colour;
   temp_light = light;
}

void Widget::restore_brush()
{
    brush_is_possible = false;
}

