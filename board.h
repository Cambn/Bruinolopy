#ifndef _BOARD_
#define _BOARD_

#include "tile.h"

#include <vector>

class Board {
		
public:
Board();

Tile * getTile(int boardPos) ;

/**
checks if both utilities are owned by same player
for use calculating rent paid when landing on a utility tile.
*/
bool checkUtilitiesSameOwner();

private:
std::vector <Tile*> tiles;
};

#endif
