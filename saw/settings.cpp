#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{

    ui->setupUi(this);
    setModal(true);
    setFixedSize(700, 500);
    setWindowTitle("Settings");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint);

    QStringList lst;
    lst << "красный" << "зелёный" << "синий" << "голубой" << "пурпурный" << "жёлтый" << "градиент";


    for(int i = 0; i < lst.size(); i++) ui->comboBox->addItem(lst[i]);


    connect(ui->sb_1, SIGNAL(valueChanged(int)), ui->sl_1, SLOT(setValue(int)));
    connect(ui->sl_1, SIGNAL(valueChanged(int)), ui->sb_1, SLOT(setValue(int)));
    connect(ui->sb_2, SIGNAL(valueChanged(int)), ui->sl_2, SLOT(setValue(int)));
    connect(ui->sl_2, SIGNAL(valueChanged(int)), ui->sb_2, SLOT(setValue(int)));
    connect(ui->sb_3, SIGNAL(valueChanged(int)), ui->sl_3, SLOT(setValue(int)));
    connect(ui->sl_3, SIGNAL(valueChanged(int)), ui->sb_3, SLOT(setValue(int)));
    connect(ui->sb_4, SIGNAL(valueChanged(int)), ui->sl_4, SLOT(setValue(int)));
    connect(ui->sl_4, SIGNAL(valueChanged(int)), ui->sb_4, SLOT(setValue(int)));
    connect(ui->sb_5, SIGNAL(valueChanged(int)), ui->sl_5, SLOT(setValue(int)));
    connect(ui->sl_5, SIGNAL(valueChanged(int)), ui->sb_5, SLOT(setValue(int)));

}

