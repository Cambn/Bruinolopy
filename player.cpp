#include "player.h"
#include "bank.h"
#include "property.h"
#include "QLandingWindows.h"

#include <QLabel>
#include <string>

class Board;

Player::Player(const std::string &_name, Bank* _bank, Board* _board, bool makeInteractor):
    bank(_bank), board(_board),
    boardPos(0) , playerMoney(1500), playerProperties(), name(_name) {
    if (makeInteractor) { //if wanted to make Interactor make one
       interactor= new QInteractor(this);
    }
    else {interactor = nullptr;}
}

Player::Player(const Player& oth){
    bank = oth.bank;
    board = oth.board;
    boardPos = oth.boardPos;
    playerMoney = oth.playerMoney;
    playerProperties = oth.playerProperties;
    name = oth.name;
    if (oth.interactor == nullptr) { // other player didn't have an interactor so we don't want one
        interactor = nullptr;
    }
    else {//if it did have one
        interactor = new QInteractor(this); //make a new interactor pointing to this instance of player
    }
}

Player::Player(Player&& oth):Player("",nullptr,nullptr){
    swap(*this, oth);
}

Player& Player::operator= (Player oth) {
 swap (*this, oth);
 return *this;
}





int Player::money() const { 
return playerMoney;
}

bool Player::pay(Player* payee, int amt) {
	if (payee){ //target player is valid 
		if (playerMoney <= amt) {//have enough money
			payee->playerMoney+= amt;
			playerMoney-= amt;
			return true;
		}
        else{
        payee->playerMoney+= playerMoney;
        playerMoney = 0; //give payee all of current money
		return false; //not enough money to make the payment
        }
	}
	return false; //not a valid target 
}

bool Player::take(Player* target, int amt) {
	if (target) {//valid target 
		if(target->playerMoney >= amt){//target has enough money
			target->playerMoney -= amt; //adjust target money
			playerMoney += amt; //adjust this's money
		}
		else { //target doesn't have enough money. 
			playerMoney += target->playerMoney; //take money they have left
			target->playerMoney = 0;
		}
		return true; //succesfully took money 
	}
	return false; //no valid target, function not successful
}

bool Player::buyPropertyBank() {
    Property* currProp = dynamic_cast<Property*>(board->getTile(boardPos));//cast curr tile that player is on to property type
    if(playerMoney >= currProp->cost/* && currProp->owner == nullptr*/) {//if player has at least enough money to buy
        bank->take(*this, currProp->cost); //charge player for property
        playerProperties.push_back(currProp); //add to back of player's properties
        currProp->transfer(this);
        return true;
    }
    return false;//player doesn't have enough money to buy
}

void Player::move(int val) {boardPos+=val;}

int Player::getPos() const {return boardPos;}

Tile* Player::getTile() const {return board->getTile(this->getPos());}

void Player::land()  {
    board->getTile(this->boardPos)->landingEvent(this);
}

//
//Player::QInteractor stuff
//
Player::QInteractor::QInteractor(Player* _player): player(_player) {}

void Player::QInteractor::buyBankProp() {
    if(player->buyPropertyBank()){//able to buy property
    QLandNoOptions* successMessage = new QLandNoOptions(player->playerProperties.back()->generateView(), //newest property will be at back of player's properties
                                                        "Property purchased!") ;
    }
    else {
    QLandNoOptions* failureMessage= new QLandNoOptions((player->board->getTile(player->getPos()))->generateView(),
                                                       "Unable to purchase property (:/)");
        emit buyPropFail();
    }


}

void Player::QInteractor::payRent() {
    ownableTile* prop = dynamic_cast<ownableTile*> (player->board->getTile((this->player->getPos()))); //prop is the tile the player is on.
    prop->propOwner()->take(this->player, prop->currentRent()); //owner of the property that the curr player is on takes appropriate amount of money from curr player .
}
