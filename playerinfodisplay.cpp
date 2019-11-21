#include "playerinfodisplay.h"
#include <QDebug>


PlayerInfoDisplay::PlayerInfoDisplay(QWidget *parent, int i, const QStringList& n, const QStringList& ch, const Statics& stat) :
    QWidget(parent),numofplayer(i),names(n),charactors(ch),s(stat)
{

    //create a player pointer list
    playerlist.resize(numofplayer);
    for (int i=0; i<numofplayer;i++){
        Player* p=new Player(this,charactors[i],names[i],s.getSTARTING_AMOUNT(),i,":/fig/gb_"+charactors[i]+".png");
        playerlist[i]=p;
    }


    playerPixmap.resize(numofplayer);
    mainLayout = new QGridLayout(this);
    for(int column = 0; column<numofplayer;++column){
        mainLayout ->addWidget(createPlayerHeader(names[column]), 0, column+1);
        playerPixmap[column] = createPlayerPixmap(playerlist[column]);
        mainLayout ->addWidget(playerPixmap[column], 1, column+1);
    }

}



QLabel *PlayerInfoDisplay::createPlayerHeader(const QString &text){
    QLabel *label = new QLabel(tr("<b>%1</b>").arg(text));
    label ->setAlignment(Qt::AlignCenter);
    return label;

}


QLabel *PlayerInfoDisplay::createPlayerPixmap(Player* p){
    QLabel *label = new QLabel;
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
