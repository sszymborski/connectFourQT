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
#include <QPropertyAnimation>
#include <QTimer>

#include"Game.h"

namespace Ui
{
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(int level, QWidget *parent = 0);
    void drawEclipse(int, int, bool);
    ~Dialog();

signals:

public slots:
    void mousePressEvent(QMouseEvent * e);

private slots:
    void on_resetButton_clicked();

protected:
    void advance(int phase);

private:
    Ui::Dialog *ui;

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse[WIDTH*LENGHT];
    QGraphicsRectItem *react[WIDTH*LENGHT];

    QPushButton *quitButton;
    QPushButton *resetButton;
    QTimer *timer;
    Game *game;

    int lastEclipse;
    int gravity;
    int hardLevel;


    // QGraphicsTextItem *text;
};
#endif // DIALOG_H
