#ifndef BOARD_H
#define BOARD_H

#include <vector>

class ChanceCard;
class MainWindow;
class Player;
class Tile;

class Board {
friend Player;
friend class ChanceTile;

public:
Board(MainWindow* game = nullptr);
Tile * getTile(int boardPos) ;
void buildChancecards(MainWindow* game);
MainWindow* w;

private:
std::vector <Tile*> tiles;
std::vector <ChanceCard*> chanceCards;
};

#endif
