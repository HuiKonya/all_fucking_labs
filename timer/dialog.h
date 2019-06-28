#pragma once
#include <QtWidgets>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);

    void drawSeconds(int sec, int min, int hours);

private:
    Ui::Dialog *ui;
    QTimer *timer;

    int Ox, Oy;
    int h;
    int m;
    int s;

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void start();
    void time();

};

