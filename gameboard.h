#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QStringList>
#include <QLabel>
#include <QLayout>

class MainWindow;
//the GameBoard class constructs the UI of the upperhalf of the Game Playing console

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);

private:
    //return one box-shaped label* for a tile
    QLabel *createPixmapLabel();

    //set the n and m for the n*m map
    enum{BoardLength = 5, BoardWidth = 5};

    //A label* array storing all the box-shaped label*'s
    QLabel *pixmapLabels[BoardWidth][BoardLength];

};

#endif // GAMEBOARD_H
