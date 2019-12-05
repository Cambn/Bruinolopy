#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QPushButton>
#include <QMainWindow>
#include <QGroupBox>
#include <QBoxLayout>
#include "gameboard.h"
#include "chancecard.h"
#include "movement.h"
#include "statics.h"
#include "dice.h"
#include "bank.h"

//the MainWindow class controls and stores all the element in the mainwindow
class PlayerInfoDisplay;

class MainWindow : public QMainWindow
{
    friend class Board;
    friend class Player;
    friend class PlayerInfoDisplay;
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr,
               int i=4,
               const QStringList& n={},
               const QStringList& ch={},
               const Statics& stat=Statics());
    ~MainWindow(){delete bank;delete board;}

    //return the player ptr pointing to i th player
    Player* getplayer(int i){return playerlist[i];}

    //check if game is over
    bool gameover();

    Bank* bank;

    /**
    Handles updating record at end of the game.
    */
    void updateRecord() const;

signals:
    void movehappened(int);


public slots:
    void playerwalk();//let the player move
    void actionupdate(int idx);//call landingevent
    void waitasec();//wait one second to conduct landingevent after the player finish moving
    void infoupdate();//repaint playerinfo



private:
    GameBoard *boardArea;
    PlayerInfoDisplay *playerArea;
    QVector<Player*> playerlist;
    Dice* maindice=new Dice(this);
    Board* board=new Board(this);
    QTimer* t=new QTimer(this);
    const int numofplayer;
    QStringList names;
    QStringList charactors;
    Statics s;
    int turn;
    int looserlist[4]={0,0,0,0};
};
#endif // MAINWINDOW_H
