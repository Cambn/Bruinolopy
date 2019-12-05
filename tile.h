#ifndef TILE_H
#define TILE_H
#include <QDebug>
#include <string>
#include <QWidget>
#include "board.h"
#include "chancecard.h"

class MainWindow;
class Player;

class Tile  {

public:
    friend class Board;
    Tile (int _tileNum, Board* _board, MainWindow* _game): tileNumber(_tileNum), board(_board), game(_game)  {}
    virtual void landingEvent(Player* currPlayer){}
    virtual ~Tile(){}
protected:
    int tileNumber;
    std::string name;
    Board* board;
    MainWindow* game;
};


class ownableTile : public Tile {

public:
    ownableTile(int _tileNum, Board* _board, MainWindow* _game);
    virtual void landingEvent( Player* currPlayer) override;
    virtual int currentRent() const = 0;
    virtual QWidget* generateView() const {return nullptr;}
    Player* propOwner() const;
    virtual int getCost() const = 0;
    void transfer( Player* newOwner);
    virtual ~ownableTile() override= default;
    virtual std::string getName() const = 0;
    virtual int checkOwnerRailroads(const Player& player) const = 0;
    //160x192 -> 320x384
protected:
    Player* owner=nullptr;

};



class ChanceTile : public Tile{
 public:
    ChanceTile(int _tileNum, Board* _board, MainWindow* _game) :Tile ( _tileNum,_board,_game) {}
    void landingEvent(Player* currPlayer) {
        int cardNum = rand() % board->chanceCards.size();
        board -> chanceCards.at(cardNum)->conduct_change(currPlayer);
    }
};


#endif
