#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "definitions.h"
#include "constants.h"
#include "utils.h"

void startGame(Game *game, string names[]);

void playRoundGame(Game *game);

bool gameIsOver(Game *game);

Player * finishGame(Game *game);

#endif // GAME_H_INCLUDED
