#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QStringList>
#include <QLabel>
#include <QLayout>


//the GameBoard class constructs the UI of the upperhalf of the mainwindow

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);

private:
    //return one box-shaped label* for a tile
    QLabel *createPixmapLabel();

    //set the n and m for the n*m map
    enum{BoardLength = 4, BoardWidth = 4};

    //A label* array storing all the box-shaped label*'s
    QLabel *pixmapLabels[BoardWidth][BoardLength];


};

#endif // GAMEBOARD_H
