#include "player.h"
#include "bank.h"
#include "property.h"
#include "QLandingWindows.h"


#include <QLabel>
#include <string>

class Board;


Player::Player() : bank(nullptr), board(nullptr),
    playerMoney(1500), playerProperties(),name() {}

Player::Player(const QString &_name, const QString& _character, int turnNumber, int startingAmount, Bank* _bank, Board* _board,  QWidget* parent):
    QWidget(parent), bank(_bank),
    board(_board) , playerMoney(startingAmount),
    hasLost(false), isDisabled(false),
    playerProperties(),
    name(_name), charactor(_character),
    movement(new Movement(this, parent, turnNumber,money(), QString(":/images/Misc/gb_" + _character + ".png")))
    {



    }


Player::Player(const Player& oth){
    bank = oth.bank;
    board = oth.board;

    playerMoney = oth.playerMoney;
    hasLost = oth.hasLost;
    isDisabled = oth.isDisabled;

    playerProperties = oth.playerProperties;
    tempObjects = oth.tempObjects;

    name = oth.name;
    charactor= oth.charactor;
    movement = oth.movement;
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
    ownableTile* currProp = dynamic_cast<ownableTile*>(getTile());//cast curr tile that player is on to property type
    if(money() >= currProp->getCost() && currProp->propOwner() == nullptr) {//if player has at least enough money to buy and property unowned
        bank->take(*this, currProp->getCost()); //charge player for property
        playerProperties.push_back(currProp); //add to back of player's properties
        currProp->transfer(this);
        return true;
    }
    return false;//player doesn't have enough money to buy
}

void Player::move(int val) {
   int unadjustedPos = (getPos()+val);
   int newPos = unadjustedPos % (board->tiles.size());
}

int Player::getPos() const {return movement->getpos();}

Tile* Player::getTile() const {return board->getTile(this->movement->getpos());}

void Player::land()  {
    getTile()->landingEvent(*this);
}

void Player::setDice (Dice* newDice, bool deleteOld) {
    if (deleteOld) { //if you wanna delete old
        delete (this->getmovement()->d); //do it
    }
    this->getmovement()->d = newDice;//playerArea->playerlist[i]->getmovement()->d=maindice

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

void Player::addTempObject(QObject* temp) {
    tempObjects.push_back(temp);
}


bool Player::eraseTempObject(QObject* temp) {
    for (auto iter = tempObjects.begin(); iter != tempObjects.begin(); ++iter){ //manual ranged for loop
        if (*iter == temp){//if we find temp
           tempObjects.erase(iter); //erase it
           return true;//to signal success
         }
     }
    return false; //fail if we can't find removeTempObject;
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
    QLandNoOptions* failureMessage= new QLandNoOptions(getTile()->generateView(),
                                                       "Unable to purchase property (:/)");
        emit buyPropFail();
    }


}

void Player::payRent() {
    ownableTile* prop = dynamic_cast<ownableTile*> (getTile()); //prop is the tile the player is on.
    prop->propOwner()->take(this, prop->currentRent()); //owner of the property that the curr player is on takes appropriate amount of money from curr player .
}

void Player::buildHouse()  {
    {
        if (dynamic_cast<Property*>( getTile() )){//if we're on a property
            Property* currProp = dynamic_cast<Property*>( getTile() );//cast currTile to property
            if(currProp->buildHouse(bank)){//house build successful.
                QLandNoOptions* successMessage = new QLandNoOptions(getTile()->generateView(),
                                                                    "Property improved !");
            }
            else {//house build unsuccssful
                QLandNoOptions* failureMessage = new QLandNoOptions(getTile()->generateView(),
                                                                    "Property improved!");
            }

        }
        else
            throw std::logic_error("buildHouse on non property tile");
    }
}
