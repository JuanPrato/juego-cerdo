#ifndef CONSTANTAS_H_INCLUDED
#define CONSTANTAS_H_INCLUDED

#include <string>

using namespace std;

string DICE_VERTICAL_FACE = "+-------+";
string DICE_LATERAL = "|";
string NL = "\n";
string DICE_SEPARATION = "  ";
string ZERO_X = "       ";
string LEFT_X = " x     ";
string CENTER_X = "   x   ";
string RIGHT_X = "     x ";
string TWO_X = " x   x ";
string DICES[6][3] = {
        {ZERO_X, CENTER_X, ZERO_X},
        {LEFT_X, ZERO_X, RIGHT_X},
        {LEFT_X, CENTER_X, RIGHT_X},
        {TWO_X, ZERO_X, TWO_X},
        {TWO_X, CENTER_X, TWO_X},
        {TWO_X, TWO_X, TWO_X}
};
char SEPARATOR = '-';
string TITLE = "GRAN CERDO\n";
string MENU = "1 - JUGAR\n2 - ESTADÍSTICAS\n3 - CERDITOS\n0 - SALIR\n";

#endif // CONSTANTAS_H_INCLUDED
