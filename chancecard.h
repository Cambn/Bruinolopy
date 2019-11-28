#ifndef EVENTTILE_H
#define EVENTTILE_H
#include "tile.h"

#include <QWidget>
#include <string>
#include <functional>


class Player;

class ChanceTile : public eventTile {
 public:
    ChanceTile(int _tileNum, Board* _board, MainWindow* _game) :eventTile ( _tileNum,_board,_game) {}

    void landingEvent(Player & currPlayer) override;

    QWidget* generateView() const override {return new QWidget;}


};


/**
designate return type of the function that the chance card uses will return
@default: void

Will be inline so i don't have to use crappy Template syntax
*/
//template <typename fxnReturnType = void>
class ChanceCard : public QWidget {

public slots:
    ChanceCard(std::string _description, std::function<void(Player*)> f):
    description(std::move(_description)),
    effect(std::move(f))
    {}
void conduct_change(Player& currPlayer);

private:
    std::string description;
    std::function<void(Player*)> effect;
};



#endif // EVENTTILE_H
