#include "welcomewindow.h"
#include "mainwindow.h"
#include "statics.h"

#include <QApplication>
#include <QLabel>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);

    WelcomeWindow* game = new WelcomeWindow;
    game-> show();





     return a.exec();

}
