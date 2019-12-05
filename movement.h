#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include "dice.h"
#include "player.h"

class Player;
//the movement class is part of the player class
//it tracks the dice, the position

class Movement : public QWidget
{
    Q_OBJECT

public:
    friend class GameBoard;
    explicit Movement(QWidget *parent = nullptr,
                      Player* p=nullptr,
                      int order=0,
                      QString address=":/fig/gb_panda.png");
    Dice* d;//a shallow copy to maindice
    void paintEvent(QPaintEvent *event) override;
    int getpos() const {return position%Axis_length;}
    int getorder()const {return order;}

public slots:
    void walkbydice();
    void one_step();
    void showrollbutton();
    void instant_trans(int new_pos){
        position = new_pos;
        ImgRect ->setX(xAxis[position]);
        ImgRect ->setY(yAxis[position]);
        ImgRect->setHeight(height);
        ImgRect->setWidth(width);
        repaint();
    }

private:

    Player* p;
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
    const int increment=1000;//if bank has money
    QVector<int> railroadPos;
};

#endif // MOVEMENT_H
