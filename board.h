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

/**
Constructs a board for the given mainwindow
@param game: game instance to which this board will belong.
*/
Board(MainWindow* game = nullptr);

/**
@param boardPos: position where you want the tile.
@return: Tile at given position
*/
Tile * getTile(int boardPos) ;

/**
constructs deck of chance cards with info from a specified game instance
@param game : game instance that chance cards will be built from
*/
void buildChancecards(MainWindow* game);


MainWindow* w;

/**
Will handle the clean up for chance cards and tiles.
*/
~Board();
private:
std::vector <Tile*> tiles;
std::vector <ChanceCard*> chanceCards;
};

#endif
