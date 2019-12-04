#include "welcomewindow.h"
#include "dice.h"

#include <QFile>


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


//    QFile test(":/txt/tileBuilder.txt");

//    if (test.open(QIODevice::ReadWrite)) {

//        QLabel* ree = new QLabel("Ree");
//        ree->show();
//    }
//    else {
//        QLabel* ree = new QLabel ("REEEEEEEEE");
//        ree->show();
//    }
