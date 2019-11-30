#ifndef _BOARD_
#define _BOARD_

#include "tile.h"

class ChanceCard;

#include <vector>

class MainWindow;

class Board {
friend Player;
friend class ChanceTile;

public:
Board(MainWindow* game = nullptr);

Tile * getTile(int boardPos) ;
//GameManager* getGM()const;

void buildChancecards(MainWindow* game);

private:
std::vector <Tile*> tiles;
std::vector <ChanceCard*> chanceCards;

};

#endif
