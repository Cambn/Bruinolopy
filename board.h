#ifndef _BOARD_
#define _BOARD_

#include "tile.h"


#include <vector>

class GameManager;


class Board {
friend Player;
		
public:
Board(GameManager* gm = nullptr);

Tile * getTile(int boardPos) ;
GameManager* getGM()const;

/**
checks if both utilities are owned by same player
for use calculating rent paid when landing on a utility tile.
*/
bool checkUtilitiesSameOwner();

private:
std::vector <Tile*> tiles;
GameManager* gameManager;

};

#endif
