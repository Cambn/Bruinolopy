/*#ifndef CHANCECARD_H
#define CHANCECARD_H
#include <QWidget>
#include <QMdiArea>
#include <QLabel>
#include <QPixmap>
#include <QLayout>
#include <QTime>
#include "player.h"

//class bank

class ChanceCard : public QWidget
{
    Q_OBJECT
public:
   ChanceCard(QWidget *parent = nullptr);

private:
   QStringList cardcontent={"Money -200","Money +300","Money+800","Money -600","Go to Jail"};


public slots:
    void conduct_change(Player* p);

};

#endif // CHANCECARD_H*/
#ifndef CHANCECARD_H
#define CHANCECARD_H


#include <QWidget>
#include <string>
#include <functional>


class Player;

class ChanceCard : public QWidget {
public slots:
    /**
    Constructs a chance card taking in the following
    @param _description : description of the effect of the card
    @param f: function of return type void with argument (Player* currPlayer)
              that the chanceCard will call when it is drawn.
    */
    ChanceCard(std::string _description, std::function<void(Player*)> f);

    /**
    calls member effect on currPlayer
    @param currPlayer: player whom this chance card is acting upon.
    */
    void conduct_change(Player* currPlayer);

    /**
    deletes member "content"
    */
    ~ChanceCard() {delete content;}
private:
    std::string description;
    std::function<void(Player*)> effect;
    QWidget* content;
};


#endif // CHANCECARD_H


