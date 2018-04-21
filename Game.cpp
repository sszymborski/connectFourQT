#include "Game.h"

#include <iostream>

Game::Game(int depth1)
{
    whoPlays = 1;
    ai1 = new AI(depth1);
    board = new int* [WIDTH];
    for(int i = 0; i < WIDTH; ++i)
        board[i] = new int[HEIGHT];
    for(int i = 0; i < WIDTH; ++i)
        for(int j = 0; j < HEIGHT; ++j)
            board[i][j] = 0;
    freeBlocks = WIDTH*HEIGHT;
}

Game::~Game()
{
    delete ai1;
    for(int i = 0; i < WIDTH; ++i)
        delete board[i];
    delete board;
}

int Game::start(int colNumber)
{
    int j = HEIGHT-1;
    for(; j >= 0; --j)
        if(board[colNumber][j] == 0)
        {
            cout << "Red on " << "\t" << "\t" << colNumber << " " << j << endl;
            board[colNumber][j] = RED;
            --freeBlocks;
            break;
        }
    return j;
}

int Game::testSituation()
{
    bool isWon = checkWin();
    if(isWon || freeBlocks == 0) // jesli wygrana lub remis
    {
        if(freeBlocks == 0 && !isWon)
            return 2;
        return 1;
    }
    return 0;
}

int Game::oponent()
{
    int colNumber = ai1 -> makeMove(board, YELLOW);
    return colNumber;
}

int Game::oponent2(int colNumber)
{
    int j = HEIGHT-1;
    for(; j >= 0; --j)
        if(board[colNumber][j] == 0)
        {
            cout << "Yellow on " << "\t" << colNumber << " " << j << endl;
            board[colNumber][j] = YELLOW;
            --freeBlocks;
            break;
        }
    return j;
}


bool Game::checkWin()
{
    int actual;
    for(int i = 0; i < WIDTH; ++i)   //4s vertically
        for(int j = HEIGHT-1; j > HEIGHT-4; --j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i][j-1] && actual == board[i][j-2] && actual == board[i][j-3])
                {
                    cout << "Win by "
                         << i << "x" << j << ", "
                         << i << "x" << j-1 <<", "
                         << i << "x" << j-2 <<", "
                         << i << "x" << j-3 << "."
                         << endl;
                    return true;
                }
            }
    for(int i = 0; i < WIDTH-3; ++i)   //4s horizontally
        for(int j = 0; j < HEIGHT; ++j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j] && actual == board[i+2][j] && actual == board[i+3][j])
                {
                    cout << "Win by "
                         << i << "x" << j << ", "
                         << i+1 << "x" << j <<", "
                         << i+2 << "x" << j <<", "
                         << i+3 << "x" << j << "."
                         << endl;
                    return true;
                }
            }
    for(int i = 0; i < WIDTH-3; ++i)   //4s diagonally up-right
        for(int j = HEIGHT-1; j >  HEIGHT-4; --j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j-1] && actual == board[i+2][j-2] && actual == board[i+3][j-3])
                {
                    cout << "Win by "
                         << i << "x" << j << ", "
                         << i+1 << "x" << j-1 <<", "
                         << i+2 << "x" << j-2 <<", "
                         << i+3 << "x" << j-3 << "."
                         << endl;
                    return true;
                }
            }
    for(int i = 0; i < WIDTH-3; ++i)   // 4s diagonally down-right
        for(int j = 0; j < HEIGHT-3; ++j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j+1] && actual == board[i+2][j+2] && actual == board[i+3][j+3])
                {
                    cout << "Win by "
                         << i << "x" << j << ", "
                         << i+1 << "x" << j+1 <<", "
                         << i+2 << "x" << j+2 <<", "
                         << i+3 << "x" << j+3 << "."
                         << endl;
                    return true;
                }
            }
    return false;
}
