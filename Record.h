#ifndef RECORD_H
#define RECORD_H
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>
/**
  @Q: to be solved:
  looserlist[4] needs to be fixed. Or else in the record there should be 4 players
*/
class Record{
  public:
    Record();
    Record(const QString&,int _PlayerRanking,int _moeny=0);
    QWidget getPlayerInfo(QWidget* parent);
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
