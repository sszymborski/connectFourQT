#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "dialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_startButton_clicked();

private:
    Ui::Widget *ui;
    int level;
};

#endif // WIDGET_H
