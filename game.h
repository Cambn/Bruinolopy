#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <vector>

class Player;

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);



signals:



public slots:



private :

    uint turnCount;
    bool shouldContinue;
    std::vector<Player*> players;
};

#endif // GAME_H
