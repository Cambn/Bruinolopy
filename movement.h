#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include "dice.h"
#include "player.h"

class Player;
//The movement is essentially the command for the player to "move" on the Game console
//It tracks the dice, the board position
//Everytime the dice is rolled, when emiting appropriate signal, this class will be called. 
//Future implement: everytime chess activatied, make it jump. 

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

    //return current position of the player
    int getpos() const;
    //return the order of the player in the playerlst
    int getorder()const;

public slots:
    void walkbydice();//walk the steps rolled by the dice
    void one_step();//walk one step
    void showrollbutton();//let the next player roll the dice
    void instant_trans(int new_pos);// move to another position instantly

private:
    Player* p;
    QTimer* timer;

    QPixmap *Img;
    QRect *ImgRect;//the size of the drawn pic
    const double oldboard=4;
    double newboard=5;
    int yAxis[16];
    int xAxis[16];
    int Axis_length=4*(newboard-1);
    int width=80*(oldboard/newboard);
    int height=120*(oldboard/newboard);

    int position;
    int order;//modify the x value to avoid icon shown overlapped
    int step_walked=0;
    QString Img_address;
    const int increment=200;
};

#endif // MOVEMENT_H
