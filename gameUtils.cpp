#include "gameUtils.h"
#include <map>
#include <cmath>

void printResultLine(int size, int points, int quantity, string unit, bool hasUnits = true) {
    string score;
    score = to_string(points) + " PDV";
    if (hasUnits) {
        score += " (" + to_string(quantity) + " " + unit + ")";
    }
    printStringCol(score, size);

}

void printCategoryTitle(string title, int size) {
    cout << title << string( size - title.length(), ' ');
}

int getDiceQuantity(Game *game) {

    if ((game->players[PLAYER_1].truffles >= 50 || game->players[PLAYER_2].truffles >= 50) ||
        game->players[PLAYER_1].falls > 0 || game->players[PLAYER_2].falls > 0)
        return 3;
    return 2;

}

Player* getCurrentPlayer(Game *game) {

    return &game->players[game->currentTurn];

}

Player* getNotCurrentPlayer(Game *game) {

    if (game->currentTurn == 1) return &game->players[PLAYER_1];
    return &game->players[PLAYER_2];

}

int getAseQuantity(const int *dices, int q) {

    int quantity = 0;
    for (int i = 0; i < q; ++i) {
        if (dices[i] == diceFaces::ONE) quantity++;
    }
    return quantity;
}

bool getIsOink(const int* dices, int diceQuantity) {
    const int firstDice = dices[0];

    for (int i = 0; i < diceQuantity; ++i) {
        if (dices[i] != firstDice) {
            return false;
        }
    }
    return true;
}

void printWinner(const Player& winner) {

    cout << "GANADOR: " << winner.name << " con " << to_string(winner.points) << " puntos de victoria\n";

}

bool askKeepPlaying() {
    char res;
    while (res != 'S' && res != 'N') {
        cout << "Continuar? (S/N)";
        cin >> res;
    }
    return res == 'S';
}

void printTotal(Player* players, int playersQuantity) {

    int colsSize = getColSize(playersQuantity + 1);

    printStringCol("TOTAL", colsSize);

    for (int i = 0; i < playersQuantity; ++i) {
        printStringCol(to_string(players[i].points), colsSize);
    }

    cout << "\n";

}

int getScore(const int* dices, int diceQuantity, bool isOink) {
    int response = 0;

    for (int i = 0; i < diceQuantity; ++i) {
        response += dices[i] + 1;
    }

    return isOink ? response * 2 : response;

}

int nextTurn(int current) {
    if (current == PLAYER_2) return PLAYER_1;
    return PLAYER_2;
}

void getMoreTruffles(Player* players, int playerQuantity, int size, const string unit) {

    map<string, int> points;
    int max = players[0].truffles;

    for (int i = 1; i < playerQuantity; ++i) {
        Player p = players[i];
        if (max < p.truffles) {
            max = p.truffles;
        }
    }

    for (int i = 0; i < playerQuantity; ++i) {
        Player* p = &players[i];

        points[p->name] = p->truffles == max ? 5 : 0;

        p->points += points[p->name];

    }


    for (int i = 0; i < playerQuantity; ++i) {
        Player p = players[i];
        printResultLine(size, points[p.name], p.truffles, unit);
    }

}

void getEveryFiftyTruffles(Player* players, int playerQuantity, int size, const string unit) {

    map<string, int> points;

    for (int i = 0; i < playerQuantity; ++i) {
        Player* p = &players[i];
        points[p->name] = p->truffles / 50;

        p->points += points[p->name];

    }

    for (int i = 0; i < playerQuantity; ++i) {
        Player p = players[i];
        printResultLine(size, points[p.name], points[p.name] * 50, unit);
    }

}

void getForOinks(Player* players, int playerQuantity, int size, const string unit) {

    map<string, int> points;

    for (int i = 0; i < playerQuantity; ++i) {
        Player* p = &players[i];
        points[p->name] = p->oiks * 2;

        p->points += points[p->name];

    }

    for (int i = 0; i < playerQuantity; ++i) {
        Player p = players[i];
        printResultLine(size, points[p.name], p.oiks, unit);
    }

}

void getGreedyPig(Player* players, int playerQuantity, int size, const string unit) {

    map<string, int> points;
    int max = players[0].maxTurnPlayed;

    for (int i = 1; i < playerQuantity; ++i) {
        Player p = players[i];
        if (max < p.maxTurnPlayed) {
            max = p.maxTurnPlayed;
        }
    }

    for (int i = 0; i < playerQuantity; ++i) {
        Player* p = &players[i];

        points[p->name] = p->maxTurnPlayed == max ? 3 : 0;

        p->points += points[p->name];

    }

    for (int i = 0; i < playerQuantity; ++i) {
        Player p = players[i];
        printResultLine(size, points[p.name], p.maxTurnPlayed, unit);
    }

}

void getPorky (Player* players, int playerQuantity, int size, const string unit) {

    int winner = -1;
    int losser = -1;

    if (players[0].porky) {
        winner = 0;
        losser = 1;
    } else if (players[1].porky) {
        winner = 1;
        losser = 0;
    }

    int penalization = 0;

    if (winner != -1) {
        Player* loss = &players[losser];
        Player* win = &players[winner];

        if (loss->points > 15) {
            penalization = -3;
        } else if (loss->points > 10) {
            penalization = -2;
        } else {
            penalization = -1;
        }

        win->points += 1;
        loss->points += penalization;
    }


    printResultLine(size, winner == 0 ? 1 : penalization, 0, unit, false);
    printResultLine(size, winner == 1 ? 1 : penalization, 0, unit, false);

}

void calcAndPrintCategory(Player* players, int playersQuantity, int category) {

    int colsSize = getColSize(playersQuantity + 1);

    const string winCategories[5][2] = {
            {"Más trufas en total", "trufas"},
            {"Cada 50 trufas", "trufas"},
            {"Oinks", "Oinks"},
            {"Cerdo codicioso", "lanzamientos"},
            {"Porky", "lanzamientos"}
    };

    void (*(functions[5]))(Player* players, int, int size, string) = {
            getMoreTruffles,
            getEveryFiftyTruffles,
            getForOinks,
            getGreedyPig,
            getPorky
    };

    printCategoryTitle(winCategories[category][0], colsSize);

    functions[category](players, playersQuantity, colsSize, winCategories[category][1]);

}


string showScore(const Player& player) {
    return player.name + ": tiene " + to_string(player.truffles) + " trufas";
}

void printCurrentRoundStats(Player player, Player notPlayer, int currentRound, int playersQuantity, int trufflesRoundQuantity, int throwsRoundQuantity) {

    cout << showScore(player) <<
        "\t" << showScore(notPlayer) << "\n";
    cout << "TURNO DE " << player.name << "\n";

    cout << "+-------------------------+\n";
    cout << "| RONDAS #" << ceil(currentRound / (float)playersQuantity) << "               |\n";
    cout << "| TRUFAS DE LA RONDA: "<< trufflesRoundQuantity <<"  |\n";
    cout << "| LANZAMIENTOS: "<< throwsRoundQuantity <<"         |\n";
    cout << "+-------------------------+\n\n";

    cout << "LANZAMIENTO #" << throwsRoundQuantity + 1 << "\n\n";

}
