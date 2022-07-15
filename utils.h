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

int getColSize(int colQuantity);

void printStringCol(string phrase, int size);

int askMenu();

#endif // UTILS_H_INCLUDED
