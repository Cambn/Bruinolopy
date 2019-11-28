#include "statics.h"



#include "welcomewindow.h"
#include "mainwindow.h"

#include "board.h"
#include "player.h"
#include "bank.h"

#include <QApplication>
#include <QLabel>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);


    MainWindow game (1,QStringList{"Jeff"}, QStringList {"panda"}, Statics());

    game.players.at(0)->go(5);





     return a.exec();

}
