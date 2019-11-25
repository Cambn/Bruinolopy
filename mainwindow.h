#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QPushButton>
#include <QMainWindow>
#include <QGroupBox>
#include <QBoxLayout>
#include "gameboard.h"
#include "playerinfodisplay.h"
#include "movement.h"
#include "statics.h"
#include "dice.h"

//the MainWindow class controls and stores all the element in the mainwindow

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*
     * constructor
     * @*parent: parent
     * @i: number of players
     * @n: a list of player names
     * @ch: a list of charactors chosen by players
     * @stat: a statics class
     * @return a mainwindow */

    MainWindow(const Statics& stat=Statics(), QWidget *parent = nullptr, int i=4, const QStringList& n={}, const QStringList& ch={});
    bool gameover();
    void infoupdate(int idx){
        playerArea->playerPixmap[idx]->setText("Character: "+playerArea->playerlist[idx]->getcharactor()+
                       "\nMoney: "+QString::number(playerArea->playerlist[idx]->money())+
                       "\nProperties:"+QString::number(playerArea->playerlist[idx]->getProp())+
                       "\nHouses:"+QString::number(playerArea->playerlist[idx]->getHouse())+
                       "\nHotels:"+QString::number(playerArea->playerlist[idx]->getHotel()));
        update();
    }
    void gameStart();

public slots:
    void playerwalk();

private:
    GameBoard *boardArea;
    PlayerInfoDisplay *playerArea;


    QStringList names;
    QStringList charactors;
    Statics s;
    Dice* maindice=new Dice(this);

    int numofplayer;
    int turn;
    int looserlist[4]={0,0,0,0};
};
#endif // MAINWINDOW_H
