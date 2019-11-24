#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <string>
#include <QObject>

#include "movement.h"
#include "board.h"

using Dollars = int;

class Bank;
class Property;
class Railroad;


class Player : public QWidget{
Q_OBJECT
	friend Bank;
    friend ownableTile;
    friend Property;
    friend Railroad;


public:
    Player();
    Player(const QString& _name,const QString& _charcter, int turnNumber, Bank* _bank, Board* _board, QWidget* parent = nullptr);

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
	bool pay(Player* payee, Dollars amt);
	
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
    return false if not enough money to purchase property.
    */
    bool buyPropertyBank();

    /**
    player can call when they are on a tile to trigger the tile's landing event.
    */
    void land () ;

    int getTurnNumber()const;


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
signals:
    void buyPropFail();
private:

    Bank* bank;
    Board* board;
    int boardPos;
    Dollars playerMoney;
    std::vector<ownableTile*> playerProperties; //properties owned by player

    QString name;
    QString charactor;
    Movement* movement;
	
};
//
//Player::QInteractor stuff
//This class will allow a player to interact with QObjects without making it a QObject itself.
//Unless set to false, each instance of player will generate a QInteractor upon its construction.
//class Player::QInteractor: public QObject {
//    Q_OBJECT
//public:
//    QInteractor(Player* _player);

//public slots:
//    void buyBankProp ();
//    void payRent ();
//signals:
//    void buyPropFail();

//private:
//    Player* player; //This QInteractor will control implement QInteractions with this player


//};

#endif
