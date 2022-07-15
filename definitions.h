#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

#include "string.h"
#include "constants.h"

struct Player {
    string name;
    int truffles = 0;
    int maxTurnPlayed = 0;
    int oiks = 0;
    int falls = 0;
    int points = 0;
    bool porky = false;
};

struct Game {
    int rounds = 5;
    int playerQuantity = 2;
    Player *players;
    int currentTurn = PLAYER_1;
    int currentRound = 1;
};

struct Best {
    string name;
    int points = 0;
};

#endif // DEFINITIONS_H_INCLUDED
