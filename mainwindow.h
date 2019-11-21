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

    MainWindow(QWidget *parent = nullptr, int i=4, const QStringList& n={}, const QStringList& ch={},const Statics& stat=Statics());
    bool gameover();
    void gameStart();

public slots:
    //void updateinfo();
    void playerwalk();

private:
    int turn=0;
    GameBoard *boardArea;
    PlayerInfoDisplay *playerArea;
    int numofplayer;
    int restnum;
    QStringList names;
    QStringList charactors;
    Statics s;
    Dice* maindice=new Dice();
};
#endif // MAINWINDOW_H
