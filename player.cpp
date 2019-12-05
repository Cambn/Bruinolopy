#include "movement.h"
#include "qlandingwindow.h"
#include "mainwindow.h"

Player::Player(QWidget *parent, Bank* b,Board* b2, const QString& ch, const QString& name, int money, int order, const QString& path)
    : QWidget(parent),bank(b),board(b2),charactor(ch),name(name),playerMoney(money)
{movement=new Movement(this,this,order,path);}

int Player::money() const
{return playerMoney;}

int Player::getPos() const
{return movement->getpos();}

bool pay(Player* payee, int amt);

bool take(Player* target, int amt);

int Player::getProp() const{return property;}

int Player::getHouse() const{return house;}

int Player::getHotel() const{return hotel;}

QString Player::getname() const{return name;}

QString Player::getcharactor() const{return charactor;}

Movement* Player::getmovement() const{return movement;}

void Player::pay(Player* payee, int amt) {
    if (!payee->isDefeated){ //target player is valid
        if (playerMoney <= amt) {//have enough money
            payee->playerMoney+= amt;
            playerMoney-= amt;
        }
        else{
        payee->playerMoney+= playerMoney;
        playerMoney = 0; //give payee all of current money
        }
    }
}

void Player::take(Player* target, int amt) {
    if (!target->isDefeated) {//valid target
        if(target->playerMoney >= amt){//target has enough money
            target->playerMoney -= amt; //adjust target money
            playerMoney += amt; //adjust this's money
        }
        else { //target doesn't have enough money.
            playerMoney += target->playerMoney; //take money they have left
            target->playerMoney = 0;
        }
    }
}



bool Player::buyPropertyBank() {
    ownableTile* currProp = dynamic_cast<ownableTile*>(getTile());//cast curr tile that player is on to property type
    if(playerMoney >= currProp->getCost() && currProp->propOwner() == nullptr) {//if player has at least enough money to buy and property unowned
        bank->take(*this, currProp->getCost()); //charge player for property
        property+=1;
        playerProperties.push_back(currProp); //add to back of player's properties
        currProp->transfer(this);
        board->w->infoupdate();
        return true;
    }
    return false;//player doesn't have enough money to buy
}



void Player::buyBankProp() {
    if(buyPropertyBank()){//able to buy property
    NoOptionWindow(this,"Property purchased!");
    }
    else {
        NoOptionWindow(this,"Unable to purchase property (:/)");
    }
}
//the slot implemented for railroad transporting
void Player::transferPlayer_Railroad(){
    //first get the tail pos, then transfer
    int pos = 2;
    if(this->getmovement()->getpos()==2){
        pos = 10;
    }
    else {pos = 2;}
    this->take(this,10);
    this->getmovement()->instant_trans(pos);
}

void Player::payRent() {
    ownableTile* prop = dynamic_cast<ownableTile*> (getTile()); //prop is the tile the player is on.
    prop->propOwner()->take(this, prop->currentRent()); //owner of the property that the curr player is on takes appropriate amount of money from curr player .
    board->w->infoupdate();
}
void Player::buildHouse()  {
    {
        if (dynamic_cast<Property*>( getTile() )){//if we're on a property
            Property* currProp = dynamic_cast<Property*>( getTile() );//cast currTile to property
        currProp->buildHouse(this->bank);
            }
        else{
            throw std::logic_error("buildHouse on non property tile");
    }
        }
}

