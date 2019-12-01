#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
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
#include "Record.h"

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

    MainWindow(QWidget *parent = nullptr, int _numofplayer=4, const QStringList& n={}, const QStringList& ch={},const Statics& stat=Statics());
    bool gameover();
    void infoupdate(int idx);
    void gameStart();

public slots:
    void playerwalk();

private:
    GameBoard *boardArea;
    PlayerInfoDisplay *playerArea;
    Dice* maindice=new Dice(this);
    const int numofplayer;
    QStringList names;
    QStringList charactors;
    Statics s;
    QVector<Record*> record;
    int turn;
    int looserlist[4]={0,0,0,0};
};
#endif // MAINWINDOW_H
