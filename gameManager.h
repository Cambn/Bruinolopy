#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <vector>
#include <string>

#include "gameboard.h"

#include "player.h"


class Bank;
class Board;
class subWindow;

class GameManager : public QObject
{
    Q_OBJECT
public:
     GameManager(QObject *parent = nullptr);

    GameManager(const subWindow& settingsInfo, QObject* parent = nullptr);

    /**
    returns turn number of player in question
    @param query player we're looking for
    @return turn number (in the sense of ordering)
    */
    int findPlayerNum(const Player& query) const;

    Board* board;
    Bank* bank;
    GameBoard* gameBoard;
    std::vector<Player*> players; // stored in turn order !

signals:



public slots:



private :

    uint turnCount;
    bool shouldContinue;


};

#endif // GAME_H
