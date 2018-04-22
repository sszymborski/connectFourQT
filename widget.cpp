#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    level = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_spinBox_valueChanged(int arg1)
{
    level = arg1;
}

void Widget::on_startButton_clicked()
{
    if(level>0)
    {
        Dialog *dialog = new Dialog(level);
        dialog->exec();
    }
    else
    {
        QMessageBox::information(this, tr("Connect4"), tr("Choose level bigger than 0") );
    }
}
