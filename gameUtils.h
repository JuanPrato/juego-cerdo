#ifndef GAMEUTILS_H_INCLUDED
#define GAMEUTILS_H_INCLUDED

#include <iostream>
#include "definitions.h"
#include "constants.h"
#include "utils.h"

using namespace std;

int getDiceQuantity(Game *game);

Player* getCurrentPlayer(Game *game);

Player* getNotCurrentPlayer(Game *game);

int getAseQuantity(const int *dices, int q);

bool getIsOink(const int* dices, int diceQuantity);

void printWinner(const Player& winner);

bool askKeepPlaying();

void printTotal(Player* players, int playersQuantity);

int getScore(const int* dices, int diceQuantity, bool isOink);

int nextTurn(int current);

void calcAndPrintCategory(Player* players, int playerQuantity, int category);

#endif // GAMEUTILS_H_INCLUDED
