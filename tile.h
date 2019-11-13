#ifndef _TILE_
#define _TILE_



class Player;

class Tile  {

public:
    friend class Board;

    Tile ()            : tileNumber(0)         {}
    Tile (int _tileNum): tileNumber(_tileNum)  {}

	
	
	
	virtual void landingEvent(Player* currPlayer) =0;

    virtual ~Tile() = default;


protected:
	int tileNumber;

};


#endif
