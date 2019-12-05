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
    //@_description the text shown on chance card
    //@_f: the corresponding change made by the chance card
    ChanceCard(std::string _description, std::function<void(Player*)> f);

    ~ChanceCard();

    //pop up window and conduct f on currPlayer
    void conduct_change(Player* currPlayer);
private:
    std::string description;
    std::function<void(Player*)> effect;
    QWidget* content;
};


#endif // CHANCECARD_H


