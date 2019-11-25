#include "statics.h"


#include "gameManager.h"
#include "welcomewindow.h"


#include <QApplication>
#include <QLabel>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);

        GameManager game ; //game creates a Board and a Bank and all of the players!

        WelcomeWindow w;
        w.show();




     return a.exec();

}
