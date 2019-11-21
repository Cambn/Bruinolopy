#ifndef TILE_H
#define TILE_H

#include "board.h"
#include <string>

class Player;
class QWidget;

class Tile  {

public:
    friend class Board;

    Tile ()            : tileNumber(0)         {}
    Tile (int _tileNum, Board* _board): tileNumber(_tileNum), board(_board)  {}


    //all comparisons just compare the tile number.  so we can sort tiles, if necessary.
    bool operator > (const Tile& oth) const;
    bool operator < (const Tile& oth) const;
    bool operator ==(const Tile& oth) const;
    bool operator !=(const Tile& oth) const;
    bool operator >=(const Tile& oth) const;


    /**
    Call to implement desired behavior of a given tile.
    (e.g. a popup window for landing on a property w/ the option to buy.)
    */
    virtual void landingEvent( Player& currPlayer) =0;

    /**
    @return pointer to QWidget displaying the tile.
    */
    virtual QWidget* generateView() const= 0;

    virtual ~Tile() = default;


protected:

    int tileNumber;
    Board* board;


};

/**
abstract base class for tiles that can be purchased/ owned.
Includes regular properties, utilities and railroads.
implements landing event as an option to purchase or charges rent.
*/
class ownableTile : public Tile {

public:

    ownableTile(int _tileNum, Board* _board);

    virtual void landingEvent( Player& currPlayer) override;


    /**
    returns tile's rent to be paid.  Calculation varies on subtype of ownableTile
    @return rent due for this tile.
    */
    virtual int currentRent() const = 0;

    /**
    @return owner of this tile
    */
    Player* propOwner() const;

    /**
    Changes owner of this tile to specified player.
    @param newOwner will become owner of this tile
    */
    void transfer( Player* newOwner);

    virtual ~ownableTile() override= default;

protected:
    Player* owner;

private:

};



class eventTile : public Tile {
public:


    virtual ~eventTile() override = default;

};

#endif
