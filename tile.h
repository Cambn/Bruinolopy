#ifndef _TILE_
#define _TILE_

#include <string>

class MainWindow;
class Player;

#include <QWidget>

class Tile  {

public:
    friend class Board;

    Tile ()            : tileNumber(0)         {}
    Tile (int _tileNum, Board* _board, MainWindow* _game): tileNumber(_tileNum), board(_board), game(_game)  {}

	
    //all comparisons just compare the tile number.  so we can sort tiles, if necessary.
    bool operator > (const Tile& oth) const;
    bool operator < (const Tile& oth) const;
    bool operator ==(const Tile& oth) const;
    bool operator !=(const Tile& oth) const;
    bool operator >=(const Tile& oth) const;

    /**
    @return pointer to QWidget displaying the tile AS IT WILL APPEAR ON THE BOARD
    */
    QPixmap* generateBoardView() const;

    /**
    Call to implement desired behavior of a given tile.
    (e.g. a popup window for landing on a property w/ the option to buy.)
    */
    virtual void landingEvent( Player& currPlayer) =0;

    /**
    @return pointer to QWidget displaying the tile.
        intended to be a closer up view than the board view;
    */
    virtual QWidget* generateView() const= 0;

    virtual ~Tile() = default;


protected:

	int tileNumber;
    Board* board;
    MainWindow* game;

};


/**
abstract base class for tiles that can be purchased/ owned.
Includes regular properties, utilities and railroads.
implements landing event as an option to purchase or charges rent.
*/
class ownableTile : public Tile {

public:

    ownableTile(int _tileNum, Board* _board, MainWindow* _game);

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
    eventTile (int _tileNum, Board* _board, MainWindow* _game): Tile(_tileNum, _board, _game) {}

    virtual void landingEvent(Player& ) override {}

    virtual ~eventTile() override = default;

};



#endif
