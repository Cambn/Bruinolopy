#include "player.h"

Player::Player(QWidget *parent, const QString& ch, const QString& name, Dollars money, int order, const QString& path)
    : QWidget(parent),charactor(ch),name(name)
{movement=new Movement(this,order,money,path);}

int Player::money() const
{return movement->getmoney();}

int Player::getPos() const
{return movement->getpos();}

int Player::getProp() const{return property;}

int Player::getHouse() const{return house;}

int Player::getHotel() const{return hotel;}

QString Player::getname() const{return name;}

QString Player::getcharactor() const{return charactor;}

Movement* Player::getmovement() const{return movement;}


