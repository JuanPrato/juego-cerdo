#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <string>

using namespace std;

const int playerQuantity = 2;
const string DICE_VERTICAL_FACE = "+-------+";
const string DICE_LATERAL = "|";
const string NL = "\n";
const string DICE_SEPARATION = "  ";
const string ZERO_X = "       ";
const string LEFT_X = " x     ";
const string CENTER_X = "   x   ";
const string RIGHT_X = "     x ";
const string TWO_X = " x   x ";
const string DICES[6][3] = {
        {ZERO_X, CENTER_X, ZERO_X},
        {LEFT_X, ZERO_X, RIGHT_X},
        {LEFT_X, CENTER_X, RIGHT_X},
        {TWO_X, ZERO_X, TWO_X},
        {TWO_X, CENTER_X, TWO_X},
        {TWO_X, TWO_X, TWO_X}
};
const char SEPARATOR = '-';
const string TITLE = "GRAN CERDO\n";
const string MENU = "1 - JUGAR\n2 - ESTADÍSTICAS\n3 - CERDITOS\n0 - SALIR\n";
const int CategoriesQuantity = 5;
const int PLAYER_1 = 0;
const int PLAYER_2 = 1;
enum diceFaces {
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX
};

#endif // CONSTANTS_H_INCLUDED
