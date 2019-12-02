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
