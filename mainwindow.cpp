#include "playerinfodisplay.h"
#include <QDebug>
#include <QFile>

#include <algorithm>
#include <utility>

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
                      [&temp](ownableTile* prop)-> void { temp += (prop->getName()+ "\t"+',' );});
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

            playerlist[i]->setPlayerPropertiesDefault();// make the properties unowned if the player is dead

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


void MainWindow::updateRecord() const {

    Player* winner = nullptr;
    for (auto player : playerlist) { //find the winner.
        if (!player->isDefeated)
            winner = player;         //set winner to winner
    }

    QFile record(":/txt/record.txt");
    if (record.isOpen()){
            QString line("");
            QTextStream stream(&record); //make textstream on record
            std::vector <std::pair<QString,int>> winners; //store all the names and money from the file
            std::vector <QString> losers(4," ");    //store losers name from first place game here



            //process fist line
            stream.readLineInto(&line);
            QStringList currLine(line.split("\t"));
                 //add "player1,player1.money()" as first pair.
            winners.push_back(std::make_pair(currLine[0],currLine[1].toInt()));
            losers.push_back(currLine[2]);
            losers.push_back(currLine[3]);
            losers.push_back(currLine[4]);

            //all the rest have same structure so just do a loop.
            while(stream.readLineInto(&line)) {
                currLine= (line.split("\t"));
                winners.push_back(std::make_pair(currLine[0],currLine[1].toInt()));
            }
            //now that we have all values, check if winner made it into records.
            //moneys will be already sorted in descending order.
            if (winner->money() > std::get<1>(winners.back())){                         //if curr winner has more money than person with least money on records page
                winners.back() = std::make_pair(winner->getname(), winner->money());    //replace last element of vector w/ curr winner
                bool newMax = (winner->money() > std::get<1>(winners.front()));         //check if winner has new high score

                //sort vector into descending order.
                std::sort(winners.begin(), winners.end(), [](
                 const std::pair<QString,int> & a, const std::pair<QString, int>& b) -> bool {
                 return std::get<1>(a) > std::get<1>(b);                                //true if a money > b money
                });

                //so now we have a vector of (names,money) sorted by descending order of money
                if(newMax) {//this is the new high score so we have to record other players
                    for (int i =0; i < playerlist.size() ; ++i) {
                        if (playerlist[i] != winner){ //for each loser
                            losers[i] = playerlist[i]->getname();//replace previous losers with current losers.

                        }
                    }
                }
                //otherwise not high score so don't care about losers.
                QTextStream out(&record);
                out << std::get<0>(winners.front()) <<"\t" << std::get<1>(winners.front())
                    <<"\t" << losers[0]<<"\t"<<losers[1]<<"\t"<<losers[2]<<"\t"<<losers[3]<<"\n";      //write first line to file

                for (size_t i=1; i< winners.size(); ++i){       //for second until last line
                out<<std::get<0>(winners.at(i)) <<"\t" << std::get<1>(winners.at(i)) <<"\n"; //write "playerName\tplayerName->money()\n"
                }
                record.close();
                return true;
            }


//            //process second line
//            stream.readLineInto(&line);
//             currLine= (line.split("\t"));
//             names.push_back(currLine[0]);
//             moneys.push_back((currLine[1]));
//             //third line
//             stream.readLineInto(&line);
//             currLine= (line.split("\t"));
//             names.push_back(currLine[0]);
//             moneys.push_back((currLine[1]));
//             //fourth line
//             stream.readLineInto(&line);
//             currLine= (line.split("\t"));
//             names.push_back(currLine[0]);
//             moneys.push_back((currLine[1]));


    }
    else throw ( std::exception("Unable to open record.txt"));


}










