#include "Record.h"
Record::Record(){

}
Record::Record(const QString& _PlayerName,int _PlayerRanking,int _money):
    PlayerName(_PlayerName),ranking(_PlayerRanking), moneyRemaining(_money),file(filename){
    if (file.open(QIODevice::ReadWrite)){
        QTextStream stream (&file);
        stream<<"Num "<< ranking<< " player: "<< PlayerName<<"with money remaining: "<<moneyRemaining;
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
void Record::getPlayerInfo(){


}
