#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include "dice.h"

class Player;

//the movement class is part of the player class
//it tracks the dice, the position

class Movement : public QWidget
{
    Q_OBJECT

public:
    friend class GameBoard;
    explicit Movement(Player* _player,QWidget *parent = nullptr,int order=0,int money=0, QString address=":/fig/gb_panda.png");
    Dice* d;//a shallow copy to maindice
    void paintEvent(QPaintEvent *event) override;
//    void increaseMoney(int a){money+=a;}
//    int getmoney() const {return money;}
    int getpos() const {return position%Axis_length;}
    //void changePos(int a){position=a;}



public slots:
    void walkbydice();
    void one_step();
    void showrollbutton();

private:

    QTimer* timer;
    QPixmap *Img;
    QRect *ImgRect;//the size of the drawn pic
    int position;
    int order;//modify the x value to avoid icon shown overlapped
    const double oldboard=4;
    double newboard=5;
    int yAxis[16];
    int xAxis[16];
    int Axis_length=4*(newboard-1);
    int width=80*(oldboard/newboard);
    int height=120*(oldboard/newboard);
    int step_walked=0;
    QString Img_address;
    const int increment=200;//amount collected on passing tile0.
    Player* player;
};

#endif // MOVEMENT_H
