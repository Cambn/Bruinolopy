#include "chancecard.h"
#include "board.h"
#include "QLandingWindows.h"
#include "mainwindow.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QDialog>

#include <algorithm>
#include <ctime>

void ChanceTile::landingEvent(Player &currPlayer) {

    cardNum = rand() % board->chanceCards.size();

    board -> chanceCards.at(cardNum) ->conduct_change(currPlayer); //draw random card from the deck, activate it.

//    QLandNoOptions* popup = new QLandNoOptions (generateView(),
//                                                "",
//                                                game,
//                                                nullptr);

// QObject::connect(popup,&QWidget::destroyed, this,&ChanceTile::conduct_change_start);

}



QWidget* ChanceTile::generateView() const  {return board->chanceCards.at(cardNum);}



ChanceCard:: ChanceCard (std::string _description, std::function<void(Player*)> f):
description(std::move(_description)),
effect(std::move(f))
{
    content = new QDialog(this);
    content->setAttribute(Qt::WA_DeleteOnClose);
    content->setWindowTitle("Chance Card");

    QHBoxLayout* layout = new QHBoxLayout;

    QLabel* statement = new QLabel(QString::fromStdString(description));
    layout->addWidget(statement);
    content->setLayout(layout);



    QLabel* bearlb = new QLabel;
    bearlb->setFixedSize(150,180);
    QPixmap *bear = new QPixmap(":/images/Misc/chance_deco.png");
    bearlb->setPixmap(*bear);
    bearlb->setPixmap(bear->scaled(bearlb->width(), bearlb->height(), Qt::KeepAspectRatio));
    layout->addWidget(bearlb,0,Qt::AlignRight);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::yellow);

    content->setAutoFillBackground(true);
    content->setPalette(pal);
    content->setFixedSize(400,200);


}



void ChanceCard::conduct_change(Player& currPlayer){
    content->show();


    effect(&currPlayer);


}
