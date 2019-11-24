#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <QPainter>
#include <QTimer>
#include <QDateTime>


#include "dice.h"

//the movement class is part of the player class
//it tracks the dice, the position

class Player;

class Movement : public QWidget
{
    Q_OBJECT

public:
    friend class GameBoard;

    Movement(QWidget *parent = nullptr,int order=0,int money=0,QString address=":/fig/gb_panda.png");

    Movement(Player& _player, int turnNumber, const QString& address, QWidget *parent = nullptr);


    ~Movement() override;


    void paintEvent(QPaintEvent *event) override;
    int getmoney() const {return money;}
    int getpos() const {return position;}

     Dice* d;


public slots:
    void walkbydice();
    void one_step();
    void showrollbutton();

private:
    Player* player;
    QTimer* timer;
    QTimer* timer2;
    QPixmap *Img;
    QString Img_address;
    QRect *ImgRect;//the size of the drawn pic

    const int width=80;
    const int height=120;

    int position;
    int money;
    int modify_x;//modify the x value to avoid overlapping, increased by 80 at a time
    int yAxis[12]={435,435,435,435,295,155,15,15,15,15,155,295};
    int xAxis[12]={15,397,779,1161,1161,1161,1161,779,397,15,15,15};
    int step_walked=0;

};

#endif // MOVEMENT_H
