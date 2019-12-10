#include "playerinfodisplay.h"
#include <QDebug>



PlayerInfoDisplay::PlayerInfoDisplay(QWidget *parent, MainWindow* w, int i, const QStringList& n, const QStringList& ch, const int i_money) :
    QWidget(parent),main(w),numofplayer(i),names(n),charactors(ch),initial_money(i_money)
{
   playerPixmap.resize(numofplayer);
    mainLayout = new QGridLayout(this);
    //create player info bar
    for(int column = 0; column<numofplayer;++column){
        mainLayout ->addWidget(createPlayerHeader(names[column]), 0, column+1);
        playerPixmap[column] = createPlayerPixmap(main->playerlist[column]);
        playerPixmap[column]->setParent(this);
        mainLayout ->addWidget(playerPixmap[column], 1, column+1);
    }

}



QLabel *PlayerInfoDisplay::createPlayerHeader(const QString &text){
    QLabel *label = new QLabel(tr("<b>%1</b>").arg(text),this);
    label ->setAlignment(Qt::AlignCenter);
    return label;

}


QLabel *PlayerInfoDisplay::createPlayerPixmap(Player* p){

    QLabel *label = new QLabel(this);

    label->setStyleSheet("QLabel{font: 20 pt; color : blue; }");

    label->setText("Charactor: "+p->getcharactor()+
                   "\nMoney: "+QString::number(p->money())+
                   "\nProperties:"+QString::number(p->getProp())+
                   "\nHouses:"+QString::number(p->getHouse())+
                   "\nHotels:"+QString::number(p->getHotel()));


    //QFrame *custom = new QFrame;
    label ->setEnabled(false);
    label ->setAlignment(Qt::AlignCenter);
    label ->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label ->setLineWidth(2);
    label ->setMidLineWidth(3);
    label ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label ->setBackgroundRole(QPalette::Base);
    label ->setAutoFillBackground(true);
    label ->setMinimumSize(130,60);
    return label;
}
