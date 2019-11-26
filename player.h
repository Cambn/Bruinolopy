#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <string>
#include <QObject>

#include "movement.h"
#include "board.h"


class Player : public QWidget{
Q_OBJECT
    friend class Bank;
    friend class ownableTile;
    friend class Property;
    friend  class Railroad;


public:
    Player();
    Player(const QString& _name,const QString& _charcter, int turnNumber, int startingAmount, Bank* _bank, Board* _board, QWidget* parent = nullptr);

    Player(const Player& oth);
    Player(Player&& oth);
    Player& operator = (Player oth);

	/***
	check player's money. doesn't allow modification. 
	@return gets playerMoney
	*/
    int money() const;
	
	/**
	pays another player, if possible 
	@param payee player being paid 
	@param amt to be paid 
	@return true if pay successful
	*/
    bool pay(Player* payee, int amt);
	
	/**
	forcibly takes money from another player.  Can reduce their money to zero !!!
	@param target to be taken from 
	@param amt to be taken 
	@return true if target was valid ptr 
	*/
	bool take(Player* target, int amt);

    /**
    move player forward by val amount
    @param val spaces to move forward.  Can be negative.
    */
    void move(int val);

    /**
    @return current board position of player
    */
    int getPos() const;

    /**
    @return Tile the player is currently on
    */
    Tile* getTile() const;


    /**
    attempts to buy property that player is currently on from bank.
    @return false if not enough money to purchase property.
    */
    bool buyPropertyBank();

    /**
    player can call when they are on a tile to trigger the tile's landing event.
    */
    void land () ;

    /**
    sets player's movement's dice to designated Dice.
    Deletes old dice for memory managment, if desired.
    @param Dice will become player's dice
    */
    void setDice(Dice* newDice, bool deleteOld = false);

    /**
    @return number of properties player owns
    */
    size_t getProp() const { return playerProperties.size();}

    /**
    @return number of houses built
    */
    int getHouse() const;

    /**
    @return number of hotels built
    */
    int getHotel() const;

    /**
    @return character of player
    */
    QString getcharactor() const {return charactor;}

    /**
    @return movement component of player
    */
    Movement* getmovement()  {
        return movement;}

    /**
    @return name of player
    */
    QString getname() const {return name;}

    /**
    Activates Movement's walkbydice fxn
    */
    void walkbydice() {movement->walkbydice();}

    /**
    sets player hasLost to true;
    */
    void kill() {hasLost= true; }

    /**
    checks if hasLost is true;
    @return : equal to hasLost
    */
    bool isDefeated() const {return (hasLost);}

    /**
    adds an object to temp objects
    @param temp will be inserted at end of tempObjects
    */
    void addTempObject(QObject* temp);

    /**
    erases a specified QObject in tempObjects
    @param object we wanna delete
    @return true if object erased.
    */
    bool eraseTempObject(QObject* temp);


    //swap for copy and swap idiom
    friend void swap(Player& left, Player& right){
        using std::swap;

        swap(left.bank, right.bank);
        swap(left.board, right.board);
        swap(left.boardPos, right.boardPos);
        swap(left.playerMoney, right.playerMoney);
        swap(left.name, right.name);
    }

public slots:
    void buyBankProp ();
    void payRent ();

    /**
    moves the player via signal and then activates the new tile's landing event.
    */
    void go(int diceVal) {move(diceVal); land();}
signals:
    void buyPropFail();
private:

    Bank* bank;
    Board* board;
    int boardPos;
    int playerMoney;
    bool hasLost;

    std::vector<ownableTile*> playerProperties; //properties owned by player
    std::list<QObject*> tempObjects;

    QString name;
    QString charactor;
    Movement* movement;
	
};

#endif
