#ifndef DIALOG_H
#define DIALOG_H

#define SIZE 50
#define WIDTH 7
#define LENGHT 6

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QMessageBox>

#include"Game.h"

namespace Ui
{
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void drawEclipse(int, int, bool);
    ~Dialog();

signals:

public slots:
    void mousePressEvent(QMouseEvent * e);

private slots:
    void on_resetButton_clicked();

private:
    Ui::Dialog *ui;

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse[WIDTH*LENGHT];
    QGraphicsRectItem *react[WIDTH*LENGHT];

    QPushButton *quitButton;
    QPushButton *resetButton;

    Game *game;

    int lastEclipse;

    // QGraphicsTextItem *text;
};
#endif // DIALOG_H
