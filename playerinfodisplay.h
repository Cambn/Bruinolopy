#ifndef PLAYERINFODISPLAY_H
#define PLAYERINFODISPLAY_H
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include "statics.h"
#include "player.h"

//the PlayerInfoDisplay class controls the lower half of the mainwindow which is used for displaying player info

class PlayerInfoDisplay : public QWidget
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
     * return a mainwindow */
    explicit PlayerInfoDisplay(QWidget *parent = nullptr, int i=4, const QStringList& n={}, const QStringList& ch={},const Statics& stat=Statics());
    ~PlayerInfoDisplay();

private:

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
    Statics s;
    QVector<Player*> playerlist;

    friend class MainWindow;
};

#endif // PLAYERINFODISPLAY_H
