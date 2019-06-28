#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    timer = new QTimer;
    h = m = s = 0;
    Ox = 250;
    Oy = 187;
    ui->lbl->setText("00:00:00");

    ui->button->setText("Запустить!");
    ui->button->setCheckable(true);
    ui->button->setChecked(false);

    connect(timer, SIGNAL(timeout()), SLOT(time()));
    connect(ui->button, SIGNAL(clicked()), SLOT(start()));
    connect(timer, SIGNAL(timeout()), SLOT(update()));
}

void Dialog::time()
{
    s++;
    if(s > 60)
    {
        s = 0;
        m++;
    }

    if(m > 60)
    {
        m = 0;
        h++;
    }

    QString temp_s, temp_m, temp_h;

    if(s < 10) temp_s = "0" + QString::number(s);
    else temp_s = QString::number(s);

    if(m < 10) temp_m = "0" + QString::number(m);
    else temp_m = QString::number(m);

    if(h < 10) temp_h = "0" + QString::number(h);
    else temp_h = QString::number(h);

     ui->lbl->setText(temp_h + ":" + temp_m + ":" + temp_s);

}

void Dialog::start()
{
    if(ui->button->isChecked())
    {
        ui->button->setText("Остановить!");
        timer->start(1000);
    }

    else if(!ui->button->isChecked())
    {
        ui->button->setText("Запустить!");
        timer->stop();
        s = m = h = 0;
        ui->lbl->setText("00:00:00");
    }
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QConicalGradient gradient(250, 187, 100);
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(0.2, Qt::yellow);
    gradient.setColorAt(0.4, Qt::green);
    gradient.setColorAt(0.6, Qt::cyan);
    gradient.setColorAt(0.8, Qt::blue);
    gradient.setColorAt(1, Qt::red);
    painter.setBrush(gradient);

    painter.setRenderHint(QPainter::Antialiasing, true);
    QPoint center(Ox,Oy);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawEllipse(center, 150, 150);

    int n = 60;
    for(int i = 0; i < n; i++)
    {
        double angle = 3.1416 * 2 * i / n;
        double x1;
        double y1;

        if(i%5)
        {
            x1 = Ox + cos(angle) * 140;
            y1 = Oy + sin(angle) * 140;
        }
        else
        {
            x1 = Ox + cos(angle) * 130;
            y1 = Oy + sin(angle) * 130;
        }

        double x2 = Ox + cos(angle) * 149;
        double y2 = Oy + sin(angle) * 149;

        painter.drawLine(QPointF(x1, y1), QPoint(x2, y2));
    }

    drawSeconds(s, m, h);
}

void Dialog::drawSeconds(int sec, int min, int hours)
{
    QPainter paint(this);
    paint.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));

    double angle = 3.1416 * 2 * (sec - 15) / 60;
    double x = Ox + cos(angle) * 125;
    double y = Oy + sin(angle) * 125;
    paint.drawLine(QPoint(Ox, Oy), QPoint(x, y));

    paint.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));

    angle = 3.1416 * 2 * (min - 15) / 60;
    x = Ox + cos(angle) * 100;
    y = Oy + sin(angle) * 100;
    paint.drawLine(QPoint(Ox,Oy), QPoint(x, y));

    paint.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));
    angle = 3.1416 * 2 * (hours - 15) / 60;
    x = Ox + cos(angle) * 60;
    y = Oy + sin(angle) * 60;
    paint.drawLine(QPoint(Ox,Oy), QPoint(x, y));
}

