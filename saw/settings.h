#pragma once
#include <QtWidgets>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    Ui::Settings *ui;
    double temp_speed_inc; // коэффициент увеличения скорости вращения
    int temp_count_of_cogs; // количество зубцов
    int temp_height_of_cogs; // высота зубцов
    int temp_radius; // радиус

};

