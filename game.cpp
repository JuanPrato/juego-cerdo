#include <iostream>
#include "game.h"
#include "constants.h"
#include "utils.h"
#include "rlutil.h"
#include "gameUtils.h"

using namespace std;
using namespace rlutil;

void startGame(Game *game, string names[]) {

    int playerQuantity = game->playerQuantity;

    game->players = new Player[playerQuantity];

    for (int i = 0; i < playerQuantity; ++i) {
        game->players[i].name = names[i];
    }

    Player *players = game->players;

    for (int i = 0; i < playerQuantity; ++i) {
        Player* p = &players[i];
        p->truffles = 0;
        p->maxTurnPlayed = 0;
        p->oiks = 0;
        p->points = 0;
        p->porky = false;
    }

    game->currentTurn = PLAYER_1;
    game->currentRound = 1;

    newScreen();

    int results[playerQuantity];

    for (int i = 0; i < playerQuantity; ++i) {
        Player p = game->players[i];

        cout << "Jugando " << p.name << ": tira los dados aprentando una tecla\n";

        keyForContinue();

        cout << getDices(1, &results[i]) << "\n";
    }

    if (results[PLAYER_2] > results[PLAYER_1]) {
        game->currentTurn = PLAYER_2;
    }

    string result;

    result += "TURNO 1: " + game->players[game->currentTurn].name + '\n';
    result += "TURNO 2: " + game->players[game->currentTurn ? 0 : 1].name + '\n';

    cout << result;

    keyForContinue();

}

bool gameIsOver(Game *game) {
    return game->currentRound > game->rounds;
}

void playRoundGame(Game *game) {

    bool keepPlaying = true;
    int trufflesRoundQuantity = 0;
    int throwsRoundQuantity = 0;
    int diceQ = getDiceQuantity(game);
    Player* player = getCurrentPlayer(game);
    Player* notPlayer = getNotCurrentPlayer(game);

    while (keepPlaying) {

        int trufflesThrow = 0;

        newScreen();

        printCurrentRoundStats(*player, *notPlayer, game->currentRound, game->playerQuantity, trufflesRoundQuantity, throwsRoundQuantity);

        int dices[diceQ];

        string dicesString = getDices(diceQ, dices);

        int aseQuantity = getAseQuantity(dices, diceQ);

        if (!notPlayer->porky && (dices[0] == dices[1] + 1 || dices[1] == dices[0] + 1)) {
            player->porky = true;
        }

        if (aseQuantity > 0) {
            if (aseQuantity == diceQ) {
                if (diceQ == 3) {
                    notPlayer->truffles += player->truffles;
                }
                player->truffles = 0;
                player->falls += 1;
            }
            trufflesRoundQuantity = 0;
            keepPlaying = false;
        } else {
            bool isOink = getIsOink(dices, diceQ);
            trufflesThrow = getScore(dices, diceQ, isOink);
            trufflesRoundQuantity += trufflesThrow;
            if (isOink) player->oiks++;
        }

        cout << dicesString << "\nSumaste " << trufflesThrow << " trufas!\n\n";

        if (keepPlaying) {
            keepPlaying = askKeepPlaying();
        } else {
            cout << "\nCambio de turno\n";
            keyForContinue();
        }

        throwsRoundQuantity++;

        diceQ = getDiceQuantity(game);

    }
    player->maxTurnPlayed = player->maxTurnPlayed < throwsRoundQuantity ? throwsRoundQuantity : player->maxTurnPlayed;
    player->truffles += trufflesRoundQuantity;
    game->currentTurn = nextTurn(game->currentTurn);
    game->currentRound++;
}

Player * finishGame(Game *game) {

    newScreen();

    Player *players = game->players;

    int cols = tcols();
    int colsPerCat = cols / (game->playerQuantity + 1);

    cout << "HITO" << string(colsPerCat - 4, ' ');


    for (int i = 0; i < game->playerQuantity; ++i) {
        cout << players[i].name << string(colsPerCat - players[i].name.length(), ' ');
    }

    Separator();

    for (int category = 0 ; category < CategoriesQuantity; ++category) {
        calcAndPrintCategory(players, game->playerQuantity, category);
        cout << "\n";
    }

    Separator();

    printTotal(players, game->playerQuantity);

    Player winner = players[PLAYER_1].points > players[PLAYER_2].points ?
            players[PLAYER_1] : players[PLAYER_2];

    printWinner(winner);

    string input;

    cout << "Ingrese Oink para continuar:";
    cin >> input;

    while (input != "Oink") {
        cout << "\nIngrese Oink para continuar:";
        cin >> input;
    }

    return players;

}
