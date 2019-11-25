#include "player.h"
#include "bank.h"
#include "property.h"
#include "QLandingWindows.h"
#include "gameManager.h"

#include <QLabel>
#include <string>

class Board;


Player::Player() : bank(nullptr), board(nullptr), boardPos(0),
    playerMoney(1500), playerProperties(),name() {}

Player::Player(const QString &_name, const QString& _character, int turnNumber, int startingAmount, Bank* _bank, Board* _board,  QWidget* parent):
    QWidget(parent), bank(_bank),
    board(_board),  boardPos(0) , playerMoney(startingAmount),
    playerProperties(),
    name(_name), charactor(_character),
    movement(new Movement(*this, turnNumber, QString(":/fig/gb_" + _character + ".png")))
    {



    }


Player::Player(const Player& oth){
    bank = oth.bank;
    board = oth.board;
    boardPos = oth.boardPos;
    playerMoney = oth.playerMoney;
    playerProperties = oth.playerProperties;
    name = oth.name;
}

Player::Player(Player&& oth):Player("","",0,1500,nullptr,nullptr){
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
    Property* currProp = dynamic_cast<Property*>(getTile());//cast curr tile that player is on to property type
    if(playerMoney >= currProp->cost && currProp->owner == nullptr) {//if player has at least enough money to buy and property unowned
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
    board->getTile(this->boardPos)->landingEvent(*this);
}

int Player::getTurnNumber() const {
    return board->getGM()->findPlayerNum(*this);
}

int Player::getHouse()  const {
    int count = 0;
    for (auto prop : playerProperties) {
        if (dynamic_cast<Property*>(prop)){ //if it is a property
            Property* temp = dynamic_cast<Property*>(prop); //cast to property*
            if (temp->houseCount ==5) {//Special Case: this means there is 4 houses and a hotel
                count += 4; //only add 4 houses
            }
            count += temp->houseCount; // Default Case: houseCount == number of houses.
        }
    }
    return count;
}

int Player::getHotel() const  {
    int count = 0;
    for (auto prop : playerProperties) {
        if (dynamic_cast<Property*>(prop)){ //if it is a property
            Property* temp = dynamic_cast<Property*>(prop); //cast to property*
            if (temp->houseCount ==5) {//hotel exists on prop iff houseCount==5
                ++count;
            }
        }
    }
    return count;
}
//
//
// slots
//
//

void Player::buyBankProp() {
    if(buyPropertyBank()){//able to buy property
    QLandNoOptions* successMessage = new QLandNoOptions(playerProperties.back()->generateView(), //newest property will be at back of player's properties
                                                        "Property purchased!") ;
    }
    else {
    QLandNoOptions* failureMessage= new QLandNoOptions((board->getTile(getPos()))->generateView(),
                                                       "Unable to purchase property (:/)");
        emit buyPropFail();
    }


}

void Player::payRent() {
    ownableTile* prop = dynamic_cast<ownableTile*> (getTile()); //prop is the tile the player is on.
    prop->propOwner()->take(this, prop->currentRent()); //owner of the property that the curr player is on takes appropriate amount of money from curr player .
}
