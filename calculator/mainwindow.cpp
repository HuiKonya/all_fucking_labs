#include "mainwindow.h"
#include "ui_mainwindow.h"

double first;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->result_show->setAlignment(Qt::AlignRight);
    connect(ui->pushButton_0, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_PLUS_MIN, SIGNAL(clicked()), SLOT(operations()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), SLOT(operations()));
    connect(ui->pushButton_devide, SIGNAL(clicked()), SLOT(math_operations()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()), SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), SLOT(math_operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), SLOT(math_operations()));

    ui->pushButton_devide->setCheckable(1);
    ui->pushButton_multiply->setCheckable(1);
    ui->pushButton_minus->setCheckable(1);
    ui->pushButton_plus->setCheckable(1);
}

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton*)sender();
    QString new_label;
    double numbers;


    if((ui->result_show->text().contains(".")) && button->text() == 0)
    {
        new_label = ui->result_show->text() + button->text();
    }

    else
    {
        numbers = (ui->result_show->text() + button->text()).toDouble();
        new_label = QString::number(numbers, 'g', 15);
        ui->result_show->setText(new_label);
    }
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->result_show->text().contains('.')))
    ui->result_show->setText(ui->result_show->text() + ".");
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton*)sender();
    QString new_label;
    double numbers;

    if(button->text() == "+/-")
    {
        numbers = (ui->result_show->text()).toDouble();
        numbers = numbers * -1;
        new_label = QString::number(numbers, 'g', 15);
        ui->result_show->setText(new_label);
    }

    else if(button->text() == "%")
    {
        numbers = (ui->result_show->text()).toDouble();
        numbers = numbers * 0.01;
        new_label = QString::number(numbers, 'g', 15);
        ui->result_show->setText(new_label);
    }
}

void MainWindow::on_pushButton_AC_clicked()
{
     ui->pushButton_devide->setChecked(0);
     ui->pushButton_multiply->setChecked(0);
     ui->pushButton_minus->setChecked(0);
     ui->pushButton_plus->setChecked(0);

     ui->result_show->setText("0");
}

void MainWindow::on_pushButton_result_clicked()
{
    double label_num, second;
    QString new_label;
    second = ui->result_show->text().toDouble();

    if(ui->pushButton_plus->isChecked())
    {
        label_num = first + second;
        new_label = QString::number(label_num, 'g', 15);
        ui->result_show->setText(new_label);
        ui->pushButton_plus->setChecked(0);
    }

    else if(ui->pushButton_minus->isChecked())
    {
        label_num = first - second;
        new_label = QString::number(label_num, 'g', 15);
        ui->result_show->setText(new_label);
        ui->pushButton_plus->setChecked(0);
    }

    else if(ui->pushButton_multiply->isChecked())
    {
        label_num = first * second;
        new_label = QString::number(label_num, 'g', 15);
        ui->result_show->setText(new_label);
        ui->pushButton_plus->setChecked(0);
    }

    else if(ui->pushButton_devide->isChecked())
    {
        if(second == 0) ui->result_show->setText("На 0 делить нельзя!");
        label_num = first / second;
        new_label = QString::number(label_num, 'g', 15);
        ui->result_show->setText(new_label);
        ui->pushButton_plus->setChecked(0);
    }
}

void MainWindow::math_operations()
{
    QPushButton *button = (QPushButton*)sender();
    first = ui->result_show->text().toDouble();
    ui->result_show->setText("0");
    button->setChecked(1);
}
