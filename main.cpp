#include <QApplication>
#include "rolldice.h"
int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    Dice dice;
    //dice.show();
    return app.exec();

}
