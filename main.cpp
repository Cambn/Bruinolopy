#include "welcomewindow.h"
#include "dice.h"


//Yuxin Qian
//Group members: Hao Zheng, Daniel Becerra, Yuxin Qian, Chuqi Bian
//"I pledge that I have neither given nor received unauthorized assistance on this assignment."

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeWindow w;
    w.show();
    return a.exec();
}

/*
 * main from Daniel
 * #include "bank.h"
#include "board.h"
#include "player.h"
#include "property.h"
#include "statics.h"
#include "tile.h"


#include <QApplication>
#include <QLabel>
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    Board board;


     std::string name("jeff");
     Player* jeff = new Player(name) ;
     jeff->move(9);
    board.getTile(jeff->getPos())->landingEvent(jeff);

//     Property* teest = new Property;

//     teest->landingEvent(jeff);


     return a.exec();

}
 */
