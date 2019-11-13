#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <string>
#include <QObject>


#include "board.h"

using Dollars = int;

class Bank;
class Property;


class Player{

	friend Bank;
    friend Property;

    class QInteractor;

public:
    //big 4
    Player(const std::string& _name, bool makeInteractor = true );
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
	buys property from another player 
	
//	@return true if other player accepts the deal.
//	*/
//	bool buyPropertyPlayer (?? ,Dollars price) // unsure of params/implementation for this one
	

    /**
    attempts to buy property that player is currently on from bank.
    return false if not enough money to purchase property.
    */
    bool buyPropertyBank();

    //swap for copy and swap idiom
    friend void swap(Player& left, Player& right){
        using std::swap;

        swap(left.bank, right.bank);
        swap(left.board, right.board);
        swap(left.boardPos, right.boardPos);
        swap(left.playerMoney, right.playerMoney);
        swap(left.interactor, right.interactor);
        swap(left.name, right.name);
    }
private:
    Bank* bank;
    Board* board;
	int boardPos; //position on board 
	Dollars playerMoney; //stores player money
	std::vector<Property*> playerProperties;
    QInteractor* interactor;
    std::string name;
	
};
//
//Player::QInteractor stuff
//This class will allow a player to interact with QObjects without making it a QObject itself.
//Unless set to false, each instance of player will generate a QInteractor upon its construction.
class Player::QInteractor: public QObject {
    Q_OBJECT
public:
    QInteractor(Player* _player);

public slots:
    void buyBankProp ();
signals:
    void buyPropFail();

private:
    Player* player; //This QInteractor will control implement QInteractions with this player


};

#endif
