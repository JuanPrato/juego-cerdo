#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <string>
#include "definitions.h"
#include "constants.h"
#include "game.h"

void newScreen();

string getDices(int diceQuantity, int *results);

void keyForContinue(string text = "");

void Separator();

void printCurrentRoundStats(Player player, Player notPlayer, int currentRound, int playersQuantity, int trufflesRoundQuantity, int throwsRoundQuantity);

int getColSize(int colQuantity);

void printStringCol(string phrase, int size);

#endif // UTILS_H_INCLUDED
