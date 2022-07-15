#include "utils.h"
#include "rlutil.h"
#include "constants.h"
#include <cmath>

using namespace rlutil;


int getColSize(int colQuantity) {

    int cols = tcols();

    return cols / colQuantity;
}

void printStringCol(string phrase, int size) {
    cout << phrase << string( size - phrase.length(), ' ');
}

void Separator() {

    int cols = tcols();

    cout << string(cols, SEPARATOR) << "\n";

}

void newScreen() {

    cls();

    cout << TITLE;

    Separator();

}

string getVerticalLayer(int dicesQuantity) {

    string response;

    for (int i = 0; i < dicesQuantity; ++i) {
        response += DICE_VERTICAL_FACE + DICE_SEPARATION;
    }

    response += NL;

    return response;
}

string getDices(int diceQuantity, int* results) {

    int diceNumbers[diceQuantity];

    for (int i = 0; i < diceQuantity; ++i) {
        diceNumbers[i] = rand() % 6;
        results[i] = diceNumbers[i];
    }

    string dicesFace = getVerticalLayer(diceQuantity);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < diceQuantity; ++j) {

            dicesFace += DICE_LATERAL;
            dicesFace += DICES[diceNumbers[j]][i];
            dicesFace += DICE_LATERAL;
            dicesFace += DICE_SEPARATION;

        }

        dicesFace += NL;

    }

    dicesFace += getVerticalLayer(diceQuantity);

    return dicesFace;
}

void keyForContinue(string text) {

    cout << text;

    anykey();

}

string showScore(const Player& player) {
    return player.name + ": tiene " + to_string(player.truffles) + " trufas";
}

void printCurrentRoundStats(Player player, Player notPlayer, int currentRound, int playersQuantity, int trufflesRoundQuantity, int throwsRoundQuantity) {

        cout << showScore(player) <<
            "\t" << showScore(notPlayer) << "\n";

        cout << "TURNO DE " << player.name << "\n";

        cout << "+-------------------------+\n";
        cout << "| RONDAS #" << ceil(currentRound / playersQuantity) << "               |\n";
        cout << "| TRUFAS DE LA RONDA: "<< trufflesRoundQuantity <<"  |\n";
        cout << "| LANZAMIENTOS: "<< throwsRoundQuantity <<"         |\n";
        cout << "+-------------------------+\n\n";

        cout << "LANZAMIENTO #" << throwsRoundQuantity + 1 << "\n\n";

}
