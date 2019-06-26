#pragma once
#include <QtWidgets>
#include <QVector>
#include <QtGui>
namespace Ui { class Widget; }

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *);
    void points(double &old_left_x, double &new_left_x, double &main_left_x,
                           double &old_right_x, double &new_right_x, double &main_right_x,
                           double &old_y, double &new_y, double koef, QVector<QPointF> &points_array, QVector<double> &already_there);

private:
    Ui::Widget *ui;
    int count_of_lines;
    int count;


private slots:
    void Change_Count_of_lines(int count);
};
