#include "dialog.h"
#include "ui_dialog.h"

#include "myItem.h"

#include <QPointF>
#include <QTimeLine>

Dialog::Dialog(int level, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    scene->setSceneRect(0, 0, 350, 300);
    QLineF topLine(scene->sceneRect().topLeft(),
                   scene->sceneRect().topRight());
    QLineF leftLine(scene->sceneRect().topLeft(),
                    scene->sceneRect().bottomLeft());
    QLineF rightLine(scene->sceneRect().topRight(),
                     scene->sceneRect().bottomRight());
    QLineF bottomLine(scene->sceneRect().bottomLeft(),
                      scene->sceneRect().bottomRight());
    QPen myPen = QPen(Qt::black);
    QBrush myBrush = QBrush();
    for(int i = 0; i < 6; ++i)
    {
        scene->addLine(0,50*i,350,50*i,myPen);
    }
    for(int i = 0; i < 7; ++i)
    {
        scene->addLine(50*i,0,50*i,300,myPen);
    }
    scene->addLine(topLine, myPen);
    scene->addLine(leftLine, myPen);
    scene->addLine(rightLine, myPen);
    scene->addLine(bottomLine, myPen);
    lastEclipse = 0;
    hardLevel = level;
    game = new Game(hardLevel);

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
                    QMessageBox::information(this, tr("Connect4"), tr("Draw by AI") );
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
                QMessageBox::information(this, tr("Connect4"), tr("Draw by U") );
                this->on_resetButton_clicked();
            }
        }
    }
    scene->update(0,0,350,300);
}


void Dialog::drawEclipse(int column, int row, bool player)
{
    MyItem *item = new MyItem(column,row,player);
    scene->addItem(item);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),scene, SLOT(advance()));
    timer->start(10);
}


Dialog::~Dialog()
{
    delete ui;
    delete game;
}

void Dialog::on_resetButton_clicked()
{
    delete game;
    game = new Game(hardLevel);
    for(int i =0; i < lastEclipse; ++i)
        scene->removeItem(ellipse[i]);
    lastEclipse = 0;
    qDeleteAll(scene->items());
    QLineF topLine(scene->sceneRect().topLeft(),
                   scene->sceneRect().topRight());
    QLineF leftLine(scene->sceneRect().topLeft(),
                    scene->sceneRect().bottomLeft());
    QLineF rightLine(scene->sceneRect().topRight(),
                     scene->sceneRect().bottomRight());
    QLineF bottomLine(scene->sceneRect().bottomLeft(),
                      scene->sceneRect().bottomRight());
    QPen myPen = QPen(Qt::black);
    QBrush myBrush = QBrush();
    for(int i = 0; i < 6; ++i)
    {
        scene->addLine(0,50*i,350,50*i,myPen);
    }
    for(int i = 0; i < 7; ++i)
    {
        scene->addLine(50*i,0,50*i,300,myPen);
    }
    scene->addLine(topLine, myPen);
    scene->addLine(leftLine, myPen);
    scene->addLine(rightLine, myPen);
    scene->addLine(bottomLine, myPen);
    scene->update(0,0,350,300);
}


