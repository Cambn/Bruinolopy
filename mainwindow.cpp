#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(const Statics& stat, int numPlayer,  const QStringList& n, const QStringList& ch , QWidget *parent )
    : QMainWindow(parent),
      names(n),
      numofplayer(numPlayer),
      charactors(ch),
      s(stat),
      turn(0)
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


void MainWindow::playerwalk()
    {if(!gameover())
    {
        int idx=turn%numofplayer;
        if(looserlist[idx]==1){
            turn+=1;
            int idx=turn%numofplayer;
            if(looserlist[idx]==1){
                turn+=1;
                playerArea->playerlist[idx]->getmovement()->walkbydice();
                infoupdate(idx);}
            else{
                playerArea->playerlist[idx]->getmovement()->walkbydice();
                infoupdate(idx);
                turn+=1;}
            }
        else{
            playerArea->playerlist[idx]->getmovement()->walkbydice();
            infoupdate(idx);
            turn+=1;}

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



