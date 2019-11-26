#ifndef _BOARD_
#define _BOARD_

#include "tile.h"


#include <vector>

class MainWindow;


class Board {
friend Player;
		
public:
Board(MainWindow* game);

Tile * getTile(int boardPos) ;
//GameManager* getGM()const;



private:
std::vector <Tile*> tiles;

};

#endif
