#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QPushButton>
#include <QMainWindow>
#include <QGroupBox>
#include <QBoxLayout>

#include <vector>

#include "gameboard.h"
#include "playerinfodisplay.h"
#include "movement.h"
#include "statics.h"
#include "dice.h"

class Player;

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

    MainWindow(QWidget *parent = nullptr,
               int i=4,
               const QStringList& n={},
               const QStringList& ch={},
               const Statics& stat=Statics());

    MainWindow(int numPlayers,
               const QStringList& _names,
               const QStringList& _characters,
               const Statics& _static = Statics(),
               QWidget* = nullptr);



    /**
    adds an object to temp objects
    @param temp will be inserted at end of tempObjects
    */
    void addTempObject(QObject* temp);

    /**
    erases a specified QObject in tempObjects
    @param object we wanna delete
    @return true if object erased.
    */
    bool eraseTempObject(QObject* temp);

    bool gameover();
    void gameStart();

public slots:
   // void actionupdate(int idx);
    void playerwalk();

private:
    int restnum;
    int turn;


    //visual elements
    GameBoard *boardArea;
    PlayerInfoDisplay *playerArea;
    Dice* maindice=new Dice();

    //data fields
    Board* board;
    std::vector<Player*> players;

    std::list<QObject*> tempObjects;
public:
    Bank* bank;
};
#endif // MAINWINDOW_H
