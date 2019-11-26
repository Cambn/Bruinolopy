#include "mainwindow.h"

#include "board.h"
#include "bank.h"
#include "player.h"

#include <QDebug>
#include <algorithm >


//MainWindow::MainWindow(QWidget *parent, int i, const QStringList& n, const QStringList& ch, const Statics& stat)
//    : QMainWindow(parent),numofplayer(i),names(n),charactors(ch),s(stat)
//{
//    //create the upper board /a map
//    QGroupBox *boardGroupBox = new QGroupBox(tr("Board"));
//    boardArea = new GameBoard(boardGroupBox);
//    QVBoxLayout *boardLayout = new QVBoxLayout(boardGroupBox);
//    boardLayout ->addWidget(boardArea);

//    //create the lower board /an info section
//    QGroupBox *playerGroupBox = new QGroupBox(tr("Player"));
//    playerArea = new PlayerInfoDisplay(playerGroupBox,numofplayer,names,charactors,s);

//    //set layout
//    QWidget *centralWidget = new QWidget(this);
//    setCentralWidget(centralWidget);
//    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
//    mainLayout ->addWidget(boardGroupBox);
//    QHBoxLayout *playerLayout = new QHBoxLayout(playerGroupBox);
//    playerLayout ->addWidget(playerArea);
//    mainLayout ->addWidget(playerGroupBox);

//    //test movement

//    for (int i=0; i<numofplayer;i++){
//        playerArea->playerlist[i]->getmovement()->d=maindice;
//        playerArea->playerlist[i]->getmovement()->setParent(boardArea);
//    }
//    QHBoxLayout *dicelayout = new QHBoxLayout;
//    dicelayout->addWidget(maindice);
//    playerLayout->addLayout(dicelayout);

//    QObject::connect(maindice->next,SIGNAL(clicked()),playerArea->playerlist[0]->getmovement(),SLOT(walkbydice()));


//    //QObject::connect(panda->d->next,SIGNAL(clicked()),this,SLOT(updateinfo()));
//}

MainWindow::MainWindow(const int numPlayers, const QStringList& _names, const QStringList& _characters, const Statics& _static, QWidget* parent):
QMainWindow(parent),
board(new Board (this)),               //create board
bank(new Bank(_static,numPlayers)),   //create bank
players(numPlayers)             //appropriately size players vector
{
//first construct players (which also constructs their Movement stuff)
for (int i = 0 ; i<numPlayers ; ++i  ) {
    players.at(i) = new Player( _names[i],
                                _characters[i],
                                i,
                                _static.getSTARTING_AMOUNT(),
                                bank,
                                board                   );

}



//create the upper board /a map
QGroupBox *boardGroupBox = new QGroupBox(tr("Board"));
boardArea = new GameBoard(boardGroupBox);
QVBoxLayout *boardLayout = new QVBoxLayout(boardGroupBox);
boardLayout ->addWidget(boardArea);

//create the lower board /an info section
QGroupBox *playerGroupBox = new QGroupBox(tr("Player"));
playerArea = new PlayerInfoDisplay(players, playerGroupBox);

//set layout
QWidget *centralWidget = new QWidget(this);
setCentralWidget(centralWidget);
QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
mainLayout ->addWidget(boardGroupBox);
QHBoxLayout *playerLayout = new QHBoxLayout(playerGroupBox);
playerLayout ->addWidget(playerArea);
mainLayout ->addWidget(playerGroupBox);

//test movement

for (size_t i=0; i<players.size(); ++i) {
    players.at(i) ->setDice(maindice,true);
    (players.at(i)->getmovement())-> setParent(boardArea);
}

QHBoxLayout *dicelayout = new QHBoxLayout;
dicelayout->addWidget(maindice);
playerLayout->addLayout(dicelayout);

QObject::connect(maindice->next,SIGNAL(clicked()),this,SLOT(playerwalk()));


//QObject::connect(panda->d->next,SIGNAL(clicked()),this,SLOT(updateinfo()));

}
//void MainWindow::gameStart(){}

void MainWindow::playerwalk(){
    {
    size_t numofplayer=players.size();
    if(!gameover())
    {
        if(looserlist[turn%numofplayer]==1){
            turn+=1;
            playerwalk();}
        else
            {playerArea->players[turn%numofplayer]->getmovement()->walkbydice();//turn()
            players[turn&numofplayer]->land();

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
        maindice->infobar->setText("Game is over.\n"+players[winner]->getname()+" wins.");
        repaint();
        return;}
    }
}

bool MainWindow::gameover(){
    int temp=0;
    for (int i=0; i<restnum; i++)
    {
        if (players[i]->money()>0)
            temp+=1;
    }
    restnum=temp;
    if(temp==1)
        return true;
    else
        return false;
}

//void MainWindow::actionupdate(int idx){
//    //int position=playerArea->playerlist[idx]->getPos()%12;
//    //if(position%12==index of chance card){
//        chancecard->conduct_change(playerArea->players[idx]);
//        qDebug()<<"after run chancecard conduct change";
//    //}
//}


/*
void MainWindow::updateinfo(){
    for(int column = 0; column<numofplayer;++column){
        playerArea->playerPixmap[column] = playerArea->createPlayerPixmap(playerArea->playerlist[column]);
        update();
    }
}
*/


void MainWindow::addTempObject(QObject* temp) {
    tempObjects.push_back(temp);
}


bool MainWindow::eraseTempObject(QObject* temp) {
    for (auto iter = tempObjects.begin(); iter != tempObjects.begin(); ++iter){ //manual ranged for loop
        if (*iter == temp){//if we find temp
           tempObjects.erase(iter); //erase it
           return true;//to signal success
         }
     }
    return false; //fail if we can't find removeTempObject;
 }


