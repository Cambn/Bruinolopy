#ifndef PLAYER_H
#define PLAYER_H

#include <QLabel>
#include <QVector>
#include <QString>
#include <QObject>
#include "bank.h"
#include "tile.h"
#include "property.h"


class Movement;

class Player : public QWidget{
    friend class Movement;
    friend class Bank;
    friend class Railroad;
    friend class MainWindow;

Q_OBJECT

public:

    Player(QWidget *parent=nullptr,
           Bank* b=nullptr,
           Board* board=nullptr,
           const QString& charactor="panda",
           const QString& name="",
           int money=0, int order=0,
           const QString& path=":/fig/gb_panda.png");
    void pay(Player* payee, int amt);
    void take(Player* target, int amt);
    bool buyPropertyBank();
    Tile* Player::getTile() const {return board->getTile(this->getPos());}
    int money() const;
    int getPos() const;
    int getProp() const;
    int getHouse() const;
    int getHotel() const;
    QString getname()const;
    QString getcharactor() const;
    Movement* getmovement() const;
    bool isDefeated=0;
    int isDisable(){return disable;}
    void changeDisable(){
        if (disable==3){
            disable=0;}
        else{
            disable++;}
    }

    Bank* bank;



public slots:
    void buyBankProp ();
    void payRent ();
    void buildHouse() ;

signals:
    void buyPropFail();

private:
    Board* board;
    QString charactor;
    QString name;
    Movement* movement;//
    int property=0;
    int house=0;
    int hotel=0;
    int disable=0;
    int playerMoney;
    std::vector<ownableTile*> playerProperties; //properties owned by player

};


#endif
