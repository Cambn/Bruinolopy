#ifndef _BOARD_
#define _BOARD_

#include "tile.h"

#include <vector>

class Board {
		
public:
Board();

Tile * getTile(int boardPos) ;

private:
std::vector <Tile*> tiles;
};

#endif
