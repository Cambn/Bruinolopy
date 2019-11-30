#ifndef CHANCECARD_H
#define CHANCECARD_H

#include "board.h"
#include "tile.h"


#include <QWidget>
#include <string>
#include <functional>


class Player;



class ChanceCard : public QWidget {

public slots:
    ChanceCard(std::string _description, std::function<void(Player*)> f);

void conduct_change(Player& currPlayer);

private:
    std::string description;
    std::function<void(Player*)> effect;
    QWidget* content;
};



class ChanceTile : public eventTile{
 public:
    ChanceTile(int _tileNum, Board* _board, MainWindow* _game) :eventTile ( _tileNum,_board,_game), cardNum(0) {}

    void landingEvent(Player & currPlayer) override;

    QWidget* generateView() const override;


private:

    int cardNum;

};


/**
designate return type of the function that the chance card uses will return
@default: void
Will be inline so i don't have to use crappy Template syntax
*/
//template <typename fxnReturnType = void>

#endif // CHANCECARD_H
