#include "playerinfodisplay.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent, int i, const QStringList& n, const QStringList& ch, const Statics& stat)
    : QMainWindow(parent),numofplayer(i),names(n),charactors(ch),s(stat),turn(0)
{
    bank=new Bank(s,numofplayer);
    board->buildChancecards(this);
    //create a player pointer list
    playerlist.resize(numofplayer);
    for (int i=0; i<numofplayer;i++){
        Player* p=new Player(this,bank,board,charactors[i],names[i],s.getSTARTING_AMOUNT(),i,":/fig/gb_"+charactors[i]+".png");
        playerlist[i]=p;
    }
    //create the upper board /a map
    QGroupBox *boardGroupBox = new QGroupBox(tr("Board"));
    boardArea = new GameBoard(boardGroupBox);
    QVBoxLayout *boardLayout = new QVBoxLayout(boardGroupBox);
    boardLayout ->addWidget(boardArea);

    //create the lower board /an info section
    QGroupBox *playerGroupBox = new QGroupBox(tr("Player"));
    playerArea = new PlayerInfoDisplay(playerGroupBox,this,numofplayer,names,charactors,s.getSTARTING_AMOUNT());

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
        playerlist[i]->getmovement()->d=maindice;
        playerlist[i]->getmovement()->setParent(this);
    }
   QHBoxLayout *dicelayout = new QHBoxLayout;
   dicelayout->addWidget(maindice);
   playerLayout->addLayout(dicelayout);

    QObject::connect(maindice->next,SIGNAL(clicked()),this,SLOT(playerwalk()));
    QObject::connect(this,SIGNAL(movehappened(int)),this,SLOT(actionupdate(int)));
    QObject::connect(t,SIGNAL(timeout()),this,SLOT(waitasec()));
}



void MainWindow::infoupdate(){
    for (int i=0;i<numofplayer;i++)
    {
        std::string temp("");
        std::for_each(playerlist[i]->playerProperties.begin(),playerlist[i]->playerProperties.end(),
                      [&temp](ownableTile* prop)->void{temp+= (prop->getName()+"\t");});
        playerArea->playerPixmap[i]->setText("Charactor: "+playerlist[i]->getcharactor()+
                   "\nMoney: "+QString::number(playerlist[i]->money())+
                   "\nProperties:"+QString::fromStdString(temp)+
                   "\nHouses:"+QString::number(playerlist[i]->getHouse())+
                   "\nHotels:"+QString::number(playerlist[i]->getHotel()));
    update();}}

bool MainWindow::gameover(){
    int temp=0;
    for (int i=0; i<numofplayer; i++)//check if there is only one player remaining in game, also that set the play to defeated = true if it is defeated
    {
        if (playerlist[i]->money()<=0){
            looserlist[i]=1;
            playerlist[i]->isDefeated = true;
        }
        else{
            temp+=1;
        }
    }

    if(temp==1){
        return true;
    }
    else{
        return false;
    }
}


void MainWindow::actionupdate(int idx){
    int position=playerlist[idx]->getPos();
    board->getTile(position)->landingEvent(playerlist[idx]);
    infoupdate();
}

void MainWindow::waitasec()
{   t->stop();
    emit movehappened((turn-1)%numofplayer);
}



void MainWindow::playerwalk()
    {
    if(!gameover())
    {
        if(looserlist[turn%numofplayer]==1)//already lost
        {
            turn+=1;
            playerwalk();}
        else
            if(playerlist[turn%numofplayer]->isDisable())//player in jail
            {
                maindice->infobar->setText(playerlist[turn%numofplayer]->getname()+" is in jail. Wait for " +QString::number(4-playerlist[turn%numofplayer]->isDisable()) +" turns");
                playerlist[turn%numofplayer]->changeDisable();
                maindice->rollStart->show();
                turn+=1;
            }
            else{
                maindice->infobar->setText("");
                {playerlist[turn%numofplayer]->getmovement()->walkbydice();//turn()
                t->start(1000);
                turn+=1;
            }

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
        maindice->infobar->setText("Game is over.\n"+playerlist[winner]->getname()+" wins.");
        repaint();
        return;}
    }


