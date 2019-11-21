#ifndef PLAYER_H
#define PLAYER_H

#include <QLabel>
#include <QVector>
#include <QString>
#include <QObject>
#include "movement.h"

using Dollars=int;

class Player : public QWidget{
Q_OBJECT

public:

    //Player();
    Player(QWidget *parent=nullptr, const QString& charactor="panda",
           const QString& name="", Dollars money=0, int order=0, const QString& path=":/fig/gb_panda.png");
    //Player(const std::string& _name, Bank* _bank, Board* _board, QObject* parent = nullptr);
    //Player(const Player& oth);
    //Player(Player&& oth);
    //Player& operator = (Player oth);

    /***
    check player's money. doesn't allow modification.
    @return gets playerMoney
    */
    int money() const;

    /*
    @return current board position of player
    */
    int getPos() const;

    int getProp() const;

    int getHouse() const;

    int getHotel() const;

    QString getname()const;

    QString getcharactor() const;

    Movement* getmovement() const;


private:
    QString charactor;
    QString name;
    Movement* movement;//
    int property=0;
    int house=0;
    int hotel=0;

};

#endif
