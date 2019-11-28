#include "chancecard.h"
#include "board.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QDialog>

#include <algorithm>
#include <ctime>

void ChanceTile::landingEvent(Player &currPlayer) {


    int cardNum = rand() % board->chanceCards.size();
    board -> chanceCards.at(cardNum) ->conduct_change(currPlayer);
}


void ChanceCard::conduct_change(Player& currPlayer){
    QWidget* content = new QDialog(this);
    content->setAttribute(Qt::WA_DeleteOnClose);
    content->setWindowTitle("Chance Card");

    QHBoxLayout* layout = new QHBoxLayout;

    QLabel* statement = new QLabel(QString::fromStdString(description));
    layout->addWidget(statement);
    content->setLayout(layout);



    QLabel* bearlb = new QLabel;
    bearlb->setFixedSize(150,180);
    QPixmap *bear = new QPixmap(":/tile/chance_deco.png");
    bearlb->setPixmap(*bear);
    bearlb->setPixmap(bear->scaled(bearlb->width(), bearlb->height(), Qt::KeepAspectRatio));
    layout->addWidget(bearlb,0,Qt::AlignRight);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::yellow);

    content->setAutoFillBackground(true);
    content->setPalette(pal);
    content->setFixedSize(400,200);

    content->show();

    effect(&currPlayer);


}

