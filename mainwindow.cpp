#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent, int i, const QStringList& n, const QStringList& ch, const Statics& stat)
    : QMainWindow(parent),numofplayer(i),names(n),charactors(ch),s(stat)
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

    QObject::connect(maindice->next,SIGNAL(clicked()),playerArea->playerlist[0]->getmovement(),SLOT(walkbydice()));


    //QObject::connect(panda->d->next,SIGNAL(clicked()),this,SLOT(updateinfo()));
}

//void MainWindow::gameStart(){}

void MainWindow::playerwalk(){
    qDebug()<<"enter mainslot";
    if(!gameover()){
        playerArea->playerlist[0]->getmovement()->walkbydice();
        turn+=1;
    }
    else
        return;
}

bool MainWindow::gameover(){
    int temp=0;
    for (int i=0; i<restnum; i++)
    {
        if (playerArea->playerlist[i]->money()>0)
            temp+=1;
    }
    restnum=temp;
    if(temp==1)
        return true;
    else
        return false;
}

/*
void MainWindow::updateinfo(){
    for(int column = 0; column<numofplayer;++column){
        playerArea->playerPixmap[column] = playerArea->createPlayerPixmap(playerArea->playerlist[column]);
        update();
    }
}
*/
