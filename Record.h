#ifndef RECORD_H
#define RECORD_H
#include <QString>
#include <QFile>
#include <QTextStream>
class Record{
  public:
    Record();
    Record(const QString&,int _PlayerRanking,int _moeny=0);
    void getPlayerInfo();
    int getPlayerRanking() const;
    QString getPlayerName() const;
    int getPlayerMoney() const;
    void setPlayerRanking(int);
    void setPlayerMoney(int _moeny = 0);
    void setPlayerName(const QString&);
  private:
    int ranking;
    QString PlayerName;
    int moneyRemaining;
    QString filename ="PlayerHistory.txt";
    QFile file;
  protected:
};

#endif // RECORD_H
