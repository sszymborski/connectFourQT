#ifndef GAME_H
#define GAME_H

//#include "Gui.h"
#include "AI.h"

#define WIDTH 7
#define HEIGHT 6
#define RED 1
#define YELLOW -1
#define PvsAI 1

using namespace std;

class Game
{
public:
    int mode; //rozroznia tryb P vs AI (1), AI vs P (2), AI vs AI (3)
    int **board;
    bool whoPlays;
    AI *ai1, *ai2;
    int freeBlocks;


    Game(int depth);
    ~Game();

    int start(int);
    int oponent();
    int oponent2(int);
    int testSituation();

private:
    bool checkWin();
};

#endif // GAME_H
