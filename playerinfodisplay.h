#ifndef PLAYERINFODISPLAY_H
#define PLAYERINFODISPLAY_H
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include "statics.h"
#include "player.h"
#include "mainwindow.h"

//the PlayerInfoDisplay class is responsible for displaying player's up-to-date info during a game

class PlayerInfoDisplay : public QWidget
{
friend class MainWindow;
    Q_OBJECT
public:
    /*
     * constructor
     * @*parent: parent
     * @i: number of players
     * @n: a list of player names
     * @ch: a list of charactors chosen by players
     * @stat: a statics class
     * return a mainwindow */
    explicit PlayerInfoDisplay(QWidget *parent = nullptr, MainWindow* w=nullptr, int i=4, const QStringList& n={}, const QStringList& ch={},const int begin_money=0);

private:

    MainWindow* main;

    /* create a header for a player info block
     * @text: the content of the header
     * return a label of the header*/
    QLabel *createPlayerHeader(const QString& text);

    /* fill in a player info block
     * @text: the content of the block
     * return a label of the block*/
    QLabel *createPlayerPixmap(Player* p);

    QGridLayout* mainLayout;
    const int numofplayer;
    QStringList names;
    QStringList charactors;
    QVector<QLabel *>playerPixmap;
    int initial_money;
};

#endif // PLAYERINFODISPLAY_H
