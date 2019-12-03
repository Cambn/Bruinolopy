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

    Player* getplayer(int i){return playerlist[i];}
    bool gameover();
    Bank* bank;

signals:
    void movehappened(int);


public slots:
    void playerwalk();
    void actionupdate(int idx);
    void waitasec();
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
