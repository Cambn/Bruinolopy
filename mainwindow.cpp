#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent, int _numofplayer, const QStringList& n, const QStringList& ch, const Statics& stat)
    : QMainWindow(parent),numofplayer(_numofplayer),names(n),charactors(ch),s(stat),turn(0)
{
    //create the upper board /a map
    QGroupBox *boardGroupBox = new QGroupBox(tr("Board"));
    boardArea = new GameBoard(boardGroupBox);
    QVBoxLayout *boardLayout = new QVBoxLayout(boardGroupBox);
    boardLayout ->addWidget(boardArea);

    //create the lower board /an info section
    QGroupBox *playerGroupBox = new QGroupBox(tr("Player"));
    playerArea = new PlayerInfoDisplay(playerGroupBox,numofplayer,names,charactors,s);

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
}

void MainWindow::infoupdate(int idx){
    playerArea->playerPixmap[idx]->setText("Charactor: "+playerArea->playerlist[idx]->getcharactor()+
                   "\nMoney: "+QString::number(playerArea->playerlist[idx]->money())+
                   "\nProperties:"+QString::number(playerArea->playerlist[idx]->getProp())+
                   "\nHouses:"+QString::number(playerArea->playerlist[idx]->getHouse())+
                   "\nHotels:"+QString::number(playerArea->playerlist[idx]->getHotel()));
    update();
}

bool MainWindow::gameover(){
    int temp=0;
    int ranking = numofplayer;
    for (int i=0; i<numofplayer; i++)
    {
        if (playerArea->playerlist[i]->money()<=0){
            looserlist[i]=1;
            record.push_back(new Record(playerArea->playerlist[i]->getname(),ranking,0));
            ranking-=1;
        }
        else{
                temp+=1;
        }
    }

    if(temp==1)
        return true;
    else
        return false;
}


void MainWindow::playerwalk()
    {if(!gameover())//game not over, that is, temp in game over != 1
    {
        if(looserlist[turn%numofplayer]==1){
            turn+=1;
            playerwalk();}
        else
            {playerArea->playerlist[turn%numofplayer]->getmovement()->walkbydice();
            infoupdate(turn%numofplayer);
            turn+=1;
        }

    }
    else //gameove, that is, temp in game over == 1
    {
        int winner=0;
        for (int i=0; i<4; i++)
        {if(!looserlist[i]){//select the winner, that is, looserlist[i]==0
                winner=i;
                break;
            }}
        maindice->infobar->setText("Game is over.\n"+playerArea->playerlist[winner]->getname()+" wins.");
        repaint();
        return;}
    }


