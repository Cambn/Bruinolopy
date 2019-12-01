#include "mainwindow.h"
#include "bank.h"
#include "board.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent, int num, const QStringList& n, const QStringList& ch, const Statics& stat)
    : QMainWindow(parent),numofplayer(num),names(n),charactors(ch),turn(0),
      players(numofplayer,nullptr),
      bank(new Bank(stat,numofplayer)),
      board(new Board(this))
{
    //first construct players
    for (int i = 0 ; i<numofplayer ; ++i  ) {
        players.at(i) = new Player( n[i],
                                    ch[i],
                                    i,
                                    stat.getSTARTING_AMOUNT(),
                                    bank,
                                    board                   );

    }
    //now that everything else is set up, build chance deck (it relies on everything else)
    board->buildChancecards(this);

    //create the upper board /a map
    QGroupBox *boardGroupBox = new QGroupBox(tr("Board"));
    boardArea = new GameBoard(boardGroupBox);
    QVBoxLayout *boardLayout = new QVBoxLayout(boardGroupBox);
    boardLayout ->addWidget(boardArea);

    //create the lower board /an info section
    QGroupBox *playerGroupBox = new QGroupBox(tr("Player"));
    playerArea = new PlayerInfoDisplay(players,playerGroupBox);

    //set layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout ->addWidget(boardGroupBox);
    QHBoxLayout *playerLayout = new QHBoxLayout(playerGroupBox);
    playerLayout ->addWidget(playerArea);
    mainLayout ->addWidget(playerGroupBox);

    //test movement

    for (int i=0; i<numofplayer;i++){
        playerArea->playerlist[i]->getmovement()->d=maindice;
        playerArea->playerlist[i]->getmovement()->setParent(boardArea);
    }
    QHBoxLayout *dicelayout = new QHBoxLayout;
    dicelayout->addWidget(maindice);
    playerLayout->addLayout(dicelayout);

    QObject::connect(maindice->next,SIGNAL(clicked()),this,SLOT(playerwalk()));
    QObject::connect(this,SIGNAL(movehappened(int)),this,SLOT(actionupdate(int)));
}

void MainWindow::infoupdate(int idx){
    playerArea->playerPixmap[idx]->setText("Charactor: "+players[idx]->getcharactor()+
                   "\nMoney: "+QString::number(players[idx]->money())+
                   "\nProperties:"+QString::number(players[idx]->getProp())+
                   "\nHouses:"+QString::number(players[idx]->getHouse())+
                   "\nHotels:"+QString::number(players[idx]->getHotel()));
    update();
}

bool MainWindow::gameover(){
    int temp=0;
    for (int i=0; i<numofplayer; i++)
    {
        if (playerArea->playerlist[i]->money()>0)
            temp+=1;
        else
            looserlist[i]=1;
    }

    if(temp==1)
        return true;
    else
        return false;
}


void MainWindow::actionupdate(int idx){
//    int position=playerArea->playerlist[idx]->getPos();
//    if(position==12){
//        chancecard->conduct_change(playerArea->playerlist[idx]);
//    }
}

void MainWindow::playerwalk()
    {
    bool test = gameover();

    if(!gameover())
    {
        int currPlayer = turn%numofplayer;
        if(looserlist[turn%numofplayer]==1){
            turn+=1;
            playerwalk();}
        else
            {players[turn%numofplayer]->getmovement()->walkbydice();//turn()
//            QObject::connect(this,SIGNAL(movehappened),this->players[currPlayer], SLOT(land()));
            emit movehappened(turn%numofplayer);
            infoupdate(turn%numofplayer);
            turn+=1;
        }
    }
    else //gameover
    {
        int winner=0;
        for (int i=0; i<4; i++)
        {if(!looserlist[i]){
                winner=i;
                break;
            }}
        maindice->infobar->setText("Game is over.\n"+playerArea->playerlist[winner]->getname()+" wins.");
        repaint();
        return;}
    }


