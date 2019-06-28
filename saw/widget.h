#pragma once
#include <QtWidgets>
#include "settings.h"
#include "ui_settings.h"
namespace Ui { class Widget; }

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    void drawSaw(QPainter &painter, double x0, double y0);

private:
    Ui::Widget *ui;
    QTimer *timer;
    Settings settings;
    double speed; // скорость вращения
    double speed_inc; // коэффициент увеличения скорости вращения
    int count_of_cogs; // количество зубцов
    int height_of_cogs; // высота зубцов
    int radius; // радиус
    int index_colour;
    int light;
    bool brush_is_possible;
    QBrush temp_br;
    int temp_index_colour;
    int temp_light;
private slots:
    void start();
    void inc();

public slots:
    void setting_values(int value);
    void values_save();
    void set_index_colour(int index);
    void set_light(int light);
    void restore_brush();
    void set_settings();

protected:
    void paintEvent(QPaintEvent *);
    void setting_brush(QPainter &painter);

 signals:
    void modal_close();
};

