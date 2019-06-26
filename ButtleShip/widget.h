#pragma once
#include <QtWidgets>
#include <ctime>

namespace Ui { class Widget; }

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    void logic(int per);
    void draw(QPainter *painter);
    void colour_changed(QPainter *painter);

protected:
    void paintEvent(QPaintEvent *);
    void wheelEvent(QWheelEvent *event);

private:
    Ui::Widget *ui;
    QPolygonF matrix[10][10];
    QChar ship[10][10];
    QChar ch = '*';
    int x, y;
    enum DIR { UP, DOWN, LEFT, RIGHT };
    int temp_dir;
    bool setting_off;
    int inc_colour;
    bool draw_is_possible;

};

