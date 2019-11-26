#ifndef _BOARD_
#define _BOARD_

#include "tile.h"
#include "chancecard.h"

#include <vector>

class MainWindow;

class Board {
friend Player;
friend class ChanceTile;
		
public:
Board(MainWindow* game);

Tile * getTile(int boardPos) ;
//GameManager* getGM()const;



private:
std::vector <Tile*> tiles;
std::vector <ChanceCard*> chanceCards;

};

#endif
