#include "dialog.h"
#include "ui_dialog.h"

#include <QPointF>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    lastEclipse = 0;
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setSceneRect(0, 0, 350, 300);
    ui->graphicsView->setScene(scene);

    for(int i = 0; i < LENGHT; ++i)
    {
        for(int j = 0; j < WIDTH; ++j)
        {
            react[i*j] = scene->addRect(SIZE*j, SIZE*i, SIZE, SIZE);
        }
    }
    game = new Game();
}

void Dialog::mousePressEvent(QMouseEvent * e)
{
    // double rad = 1;
    QPointF pt = ui->graphicsView->mapToScene(e->pos());
    // scene->addEllipse(pt.x()-rad-12, pt.y()-rad-12, rad*2.0, rad*2.0, QPen(), QBrush(Qt::SolidPattern));
    int x = (int)pt.x() - 12;
    int offset = x%50;
    int finalX = (x-offset)/50;
    if(finalX < 7 && finalX >= 0)
    {
        if(game->board[finalX][0]==0)
        {
            drawEclipse(finalX,game->start(finalX),true);
            if(game->testSituation()==0)
            {
                int oponentX = game->oponent();
                drawEclipse(oponentX, game->oponent2(oponentX), false);
                if(game->testSituation()==0)
                {
                    ;
                }
                else if(game->testSituation()==1)
                {
                    QMessageBox::information(this, tr("Connect4"), tr("You lose!") );
                    this->on_resetButton_clicked();
                }
                else
                {
                    QMessageBox::information(this, tr("Connect4"), tr("Draw") );
                    this->on_resetButton_clicked();
                }
            }
            else if(game->testSituation()==1)
            {
                    QMessageBox::information(this, tr("Connect4"), tr("You win!") );
                    this->on_resetButton_clicked();
            }
            else
            {
                    QMessageBox::information(this, tr("Connect4"), tr("Draw") );
                    this->on_resetButton_clicked();
            }
        }

    }

}


void Dialog::drawEclipse(int column, int row, bool player)
{
    QBrush redBrush(Qt::red);
    QBrush yellowBrush(Qt::yellow);
    QPen outlinePen(Qt::black);
    ellipse[lastEclipse++] = scene->addEllipse(SIZE*column, SIZE*row, SIZE, SIZE, outlinePen, player?redBrush:yellowBrush);
}

Dialog::~Dialog()
{
    delete ui;
    delete game;
}

void Dialog::on_resetButton_clicked()
{
    delete game;
    game = new Game();
    for(int i =0; i < lastEclipse; ++i)
        scene->removeItem(ellipse[i]);
    lastEclipse = 0;
}
