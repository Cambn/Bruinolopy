#include "mainwindow.h"

#include "board.h"
#include "bank.h"
#include "player.h"

#include <QDebug>
#include <algorithm >


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
    players.at(i) ->setDice(maindice);
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
    int currTurn = turn% players.size();
    if(!gameover())
    {
        if(players[currTurn]->isDefeated()){
            turn+=1;
            playerwalk();
        }
        else{
            players[currTurn]->walkbydice();//turn()
            turn+=1;
        }

    }
    else { //gameover
        for(Player* player: players) { //for the players
            if (!player->isDefeated()){ //if not yet defeated
                maindice->infobar->setText("Game is over.\n"+player->getname()+" wins.");
                repaint();
                break;
            }
        }
    }
}


bool MainWindow::gameover(){
    int temp=0;
    for (Player* player : players)
    {
       if(! (player->isDefeated())){
           ++temp;
       }
    }
    if(temp==1)
        return true;
    else
        return false;
}


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
