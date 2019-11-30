#include "player.h"

#include "board.h"
#include "property.h"
#include "chancecard.h"
#include "mainwindow.h"
#include "bank.h"


#include <string>
#include <sstream>
#include <fstream>
#include <exception>

using std::string;

Board::Board(MainWindow* game) : tiles(16,nullptr) {

    srand(time(nullptr));

    string first("prop	1	purple	Kerchoff Hall	60	50	2	10	30	90	160	250");
    string sec("prop	3	purple	Powell Library	60	50	4	20	60	180	320	450");

//    string third("prop	5	lightBlue	prop2	100	50	6	30	90	270	400	550");
//    string four("prop	6	lightBlue	Psych. Tower	100	50	6	30	90	270	400	550");
//    string five("prop	7	lightBlue	prop4	120	50	8	40	100	300	450	600");

    string six("prop	5	magenta	Dickson Court	140	100	10	50	150	450	625	750");
    string sev("prop	6	magenta	Music Building	140	100	10	50	150	450	625	750");
    string eight("prop	7	magenta	Haines Hall	160	100	12	60	180	500	700	900");

    string parkPlace("prop\t9\tblue\tRoyce Hall\t350\t200\t35\t175\t500\t1100\t1300\t1500");
    string mathSci("prop\t11\tblue\tFowler Museum\t400\t200\t50\t200\t1600\t1400\t1700\t2000");

    string nine("prop	13	yellow	Math Sci Bldg	180	100	14	70	200	550	700	900");
    string ten("prop	14	yellow	Intermural Field	180	100	14	70	200	550	700	950");
    string eleven("prop	15	yellow	Bear Statues	200	100	16	80	220	600	900	1000");

    //bottom row
    tiles.at(1)= new Property(first,this,game);
    tiles.at(2)= new Railroad(2,"Metro",this,game);
    tiles.at(3)= new Property (sec,this,game);
    tiles.at(4)= new ChanceTile(4,this,game);
    //right column
    tiles.at(5)= new Property(six,this,game);
    tiles.at(6)= new Property(sev,this,game);
    tiles.at(7)= new Property(eight,this,game);

    //top row
    tiles.at(13)=new Property(nine,this,game);
    tiles.at(14)= new Property(ten,this,game);
    tiles.at(15)= new Property(nine,this,game);
    //left column
    tiles.at(9)=new Property(parkPlace,this,game);
    tiles.at(10)= new Railroad(10,"Big Blue Bus",this,game);
    tiles.at(11)= new Property(mathSci,this,game);
    tiles.at(12)=new ChanceTile(12,this,game);





}




Tile* Board::getTile(int boardPos )  {
    return tiles.at(boardPos);
}

void Board::buildChancecards(MainWindow* game) {

    chanceCards.emplace_back(new ChanceCard("Lose 200 Dollars!",
                              [game](Player* currPlayer) -> void {
                              game->bank->take(*currPlayer, 200);
                                 }
                               )

                              );

     chanceCards.emplace_back( new ChanceCard ("Gain 100 Dollars!",
                            [game](Player* currPlayer) -> void {
                                   game->bank->pay(*currPlayer,100);
                               }
                              )
             );
     chanceCards.emplace_back( new ChanceCard("Move Back 3 Spaces.",
                                              [](Player* currPlayer) -> void {
                                              currPlayer->move(-3);
                                              currPlayer->land();
                                              }
                                             )
                             );
     chanceCards.emplace_back( new ChanceCard("Take $50 from each other player",
                                              [game](Player* currPlayer) -> void {
                                   for(auto player: game->players) {//for each player in the game
                                       if (player!= currPlayer && !(player->isDefeated())) {//each other player that is still in game
                                           currPlayer->take(player,50); //take 50 dollars
                                       }
                                   }
                                 }
                               )
             );

     chanceCards.emplace_back(new ChanceCard("Pay each other player $50",
         [game] (Player* currPlayer) -> void {
         for(auto player: game->players) {//for each player in the game
             if (player!= currPlayer && !(player->isDefeated())) {//each other player that is still in game
                 currPlayer->take(player,-50); //pay 20 dollars
             }
          }
         }
         )
        );

     chanceCards.emplace_back(new ChanceCard("Take a break! (Nothing happens).",
                                             [] (Player*) {})
             );

     chanceCards.emplace_back(new ChanceCard("Advance to the Big Blue Bus.",
         [=] (Player* currPlayer) -> void {
        int posDiff =  10 - currPlayer->getPos(); //destination - currentPos

        if (posDiff > 0) {// have to move forward to get to it
            currPlayer->go(posDiff);
        }
        else if (posDiff < 0) {// have to move all around the board to get to it.
           currPlayer->go(tiles.size() - currPlayer->getPos()); //go correct neumber of tiles.
        }
        else {//posDiff is zero  . board is incorrectly configured. throw exception.
        throw   std::exception("Error in Board Configuration");
        }

     } ));

     chanceCards.emplace_back(new ChanceCard ("Advance to MathSci Building. (Yay!)",
        [=] (Player* currPlayer) -> void {
         int posDiff =  13 - currPlayer->getPos(); //destination - currentPos

         if (posDiff > 0) {// have to move forward to get to it
             currPlayer->go(posDiff);
         }
          else if (posDiff < 0) {// have to move all around the board to get to it.
                   currPlayer->go(tiles.size() - currPlayer->getPos()); //go correct neumber of tiles.
          }
        }
     ));

     chanceCards.emplace_back(new ChanceCard("Pay 50 dollars for every House you own, \n100 dollars for each Hotel.",
         [game](Player* currPlayer) -> void{

         int count = currPlayer->getHouse() + 2*currPlayer->getHotel() ; //count hotels twice for cost calculation

         game->bank->take(*currPlayer, count * 50);
         }
      ));

     chanceCards.emplace_back( new ChanceCard("Take $200 from the player with most money.\n"
                                              " If that's you then give $200 dollars to the \n"
                                              "player with the least money.",
                                              [game](Player* currPlayer) -> void {
                                   std::vector <Player*> playersCopy = game->players; //create copy of game's players.
                                   //sort players by least money to most money
                                   std::sort(playersCopy.begin(), playersCopy.end(), [](const Player* a, const Player* b) -> bool { return a->money() < b->money();});
                                   if (playersCopy.back() == currPlayer) {//currPlayer has the most money
                                       playersCopy.front()->take(currPlayer,200); //player with least money gets $200
                                   }
                                   else {//currplayer does not have the most money
                                       currPlayer->take(playersCopy.back(),200);//take 200 from player with most money
                                   }
                               }
                              ));

}

//{
//    std::fstream tileBuilder(":/properties/tileBuilder.txt");//open appropriate txt file
//    bool check = tileBuilder.is_open();

//    if(check){ //file successfully open

//        std::string currLine= "";
//        std::getline(tileBuilder, currLine); //eat the first line of file that displays formatting and is garbage data

//         while(!(tileBuilder.eof())){        //until end of file
//         std::getline(tileBuilder,currLine); //put line into string
//         std::stringstream buffer(currLine); //create ss from string
//         std::string temp = "";
//         buffer>>temp;
//           if (temp == "prop") {//want to construct property
//               Property* tempProp = new Property(currLine,this);
//               tiles.at(tempProp->tileNumber) = tempProp;
//           }
//             if(temp == "rr") {//want to construct railroad
//                 Railroad* tempProp = new Railroad(currLine,this);
//                 tiles.at(tempProp->tileNumber) = tempProp;
//             }


//          }



//    }
//    else {throw 10;}
