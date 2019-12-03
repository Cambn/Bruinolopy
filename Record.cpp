#include "Record.h"
#include <fstream>
using std::string;using std::stringstream;
Record::Record(){

}
Record::Record(const QString& _PlayerName,int _PlayerRanking,int _money):
    PlayerName(_PlayerName),ranking(_PlayerRanking), moneyRemaining(_money),file(filename){
    if (file.open(QIODevice::ReadWrite)){
        QTextStream stream (&file);
        stream<<"Num"<<'\t'<< QString::number(ranking)<< '\t'<< "player"<<'\t'<< PlayerName<<'\t'<<"with money remaining: "<<QString::number(moneyRemaining);
    }
}
int Record::getPlayerRanking() const{
    return ranking;
}
QString Record::getPlayerName() const{
    return PlayerName;
}
int Record::getPlayerMoney() const{
    return moneyRemaining;
}
/*
QWidget Record::getPlayerInfo(QWidget* parent){

    QFile file("/");
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0,"error",file.errorString());
    }
    QTextStream in(&file);
    QString line;
    QStringList list;
    QString name;
    QString ranking;
    QString money;
    while(!in.atEnd()){
    line = in.readLine();// a string of whole line
    list = line.split('\t');
        ranking = list[1];
        name = list[3];
        money = list[5];
    }
    QLabel* _name =new QLabel(name);
    QLabel* _ranking = new QLabel(ranking);
    QLabel* _money = new QLabel(money);
    QHBoxLayout *layout;
    layout ->addWidget(_name);
    layout ->addWidget(_money);
    layout ->addWidget(_ranking);

}
*/
