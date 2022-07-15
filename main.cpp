#include <iostream>
#include "definitions.h"
#include "utils.h"
#include "constants.h"
#include "game.h"

using namespace std;

Best best;

int askMenu() {
    newScreen();

    cout << MENU;

    int selectedOption;
    cin >> selectedOption;
    return selectedOption;
}

bool isValidOption(int option) {
    int options[] = {0, 1, 2, 3};

    for(const int possibleOption : options ) {
        if (possibleOption == option) return true;
    }

    return false;
}

void askNames(string* names) {

    newScreen();

    cout << "Ingrese el nombre del primer jugador\n";

    cin >> names[PLAYER_1];

    cout << "Ingrese el nombre del segundo jugador\n";
    cin >> names[PLAYER_2];
}

void play() {

    string names[2];

    askNames(names);

    Game *game = new Game;

    newScreen();

    startGame(game, names);

    while (!gameIsOver(game)) {
        playRoundGame(game);
    }

    Player *players = finishGame(game);

    for (int i = 0; i < 2; ++i) {
        if (players[i].name == best.name) {
            best.points += players[i].points;
        }
    }

    if (players[0].points > best.points) {
        best.name = players[0].name;
        best.points = players[0].points;
    } else if (players[1].points > best.points) {
        best.name = players[1].name;
        best.points = players[1].points;
    }

}

void showStadistics(Best best) {

    newScreen();

    cout << "El jugador con m�s puntos de victoria es " << best.name
         << " con " << best.points << "\n\n";

    keyForContinue("Presione cualquier tecla para volver al men�\n");

}

void showCredits() {

    newScreen();

    cout << "Integrantes del grupo: \n" <<
    "Esteban Curcio 27106\nMat�as Lencina 25524\nJuan Manuel Prato 26070\n\n";

    keyForContinue("Presione cualquier tecla para volver al men�\n");
}


int main()
{
 int selectedOption;

    newScreen();

    selectedOption = askMenu();

    while (selectedOption != 0) {
        while (selectedOption != 0 && !isValidOption(selectedOption)) {
            selectedOption = askMenu();
        }

        switch (selectedOption) {
            case 1:
                play();
                break;
            case 2:
                showStadistics(best);
                break;
            case 3:
                showCredits();
                break;
            default:
                break;
        }

        newScreen();

        selectedOption = askMenu();

    }
}
