#include "bank.h"
#include "board.h"
#include "player.h"
#include "property.h"
#include "statics.h"
#include "tile.h"


#include <QApplication>
#include <QLabel>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    Board board;
    Bank bank;


     std::string name("jeff");
     Player* jeff = new Player(name,&bank,&board) ;
     Player* BIGMIKE= new Player("BIG MIKE",&bank, &board);


     jeff->move(9);
     BIGMIKE->move(9);

    jeff->land();




     return a.exec();

}
