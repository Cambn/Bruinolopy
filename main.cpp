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



    QStringList n = {"jeff", "BIGMIKE"};
    QStringList ch = {"panda", "panda"};

  MainWindow game(2,n,ch,Statics(),nullptr);
  game.show();

//  Player& jeff = *game.players.at(0);
//  Player& BIGMIKE= *game.players.at(1);

//    jeff.go(4);

     return a.exec();

}
