#include "statics.h"



#include "welcomewindow.h"


#include <QApplication>
#include <QLabel>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);



        WelcomeWindow w;
        w.show();




     return a.exec();

}
