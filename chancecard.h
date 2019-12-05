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
    ChanceCard(std::string _description, std::function<void(Player*)> f);
void conduct_change(Player* currPlayer);
private:
    std::string description;
    std::function<void(Player*)> effect;
    QWidget* content;
};


#endif // CHANCECARD_H


