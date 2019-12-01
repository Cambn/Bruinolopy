#include "movement.h"
#include "player.h"
#include <QDebug>

Movement::Movement(Player* _player, QWidget *parent,int order, int money, QString address) :
    QWidget(parent),position(0),order(order),money(money), player(_player)
{
    //modify the lower right cornor index by requirement
    int y_max=470;
    int x_max=1240;
    //increment of x and y
    int add_y=140*(oldboard/newboard)+1;
    int add_x=382*(oldboard/newboard);

    for(int i=0;i<newboard;i++){
        yAxis[i]=y_max;
        xAxis[(i+Axis_length/4)%Axis_length]=x_max;

        yAxis[i+Axis_length/2]=y_max-Axis_length/4*add_y;
        xAxis[(i+Axis_length*3/4)%Axis_length]=x_max-Axis_length/4*add_x;
    }

    for(int i=0;i<newboard-2;i++){
        yAxis[i+Axis_length/4+1]=y_max-(i+1)*add_y;
        xAxis[(i+Axis_length/4+1+Axis_length/4)%Axis_length]=x_max-(i+1)*add_x;

        yAxis[i+Axis_length*3/4+1]=y_max-(Axis_length/4-1-i)*add_y;
        xAxis[i+1]=x_max-(Axis_length/4-1-i)*add_x;
    }


    for (int i=0;i<Axis_length;i++){
        xAxis[i]+=(width+4)*order;
    }

    Img = new QPixmap(address);
    ImgRect = new QRect(xAxis[position],yAxis[position], width, height);
    //@rect: area that could be drawn on
    QRect rect = this->geometry ();
    rect.setWidth (width*150);
    rect.setHeight (height*150);
    rect.setX(0);
    rect.setY(0);
    this ->setGeometry(rect);
}


void Movement::paintEvent(QPaintEvent*)
{
        QPainter painter(this);
        painter.drawPixmap(*ImgRect, *Img);
}

void Movement::walkbydice(){
    d->rollStart->hide();
    timer=new QTimer(this);
    timer->start(250);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(one_step()));
    position+=d->getresult();//need to update pos in walkbydice otherwise when the signal for land() emits the position is still the initial one
    if (position/Axis_length<(position+d->getresult())/Axis_length)
        money+=increment;
}

void Movement::one_step(){
    int prev_pos=position-d->getresult();
    if (step_walked<d->getresult()){
        step_walked++;
        ImgRect ->setX(xAxis[(prev_pos+step_walked)%Axis_length]);
        ImgRect ->setY(yAxis[(prev_pos+step_walked)%Axis_length]);
        ImgRect->setHeight(height);
        ImgRect->setWidth(width);
        repaint();
    }
    else
    {
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(showrollbutton()));
        timer->stop();
        timer->start(250);
        QObject::connect(timer,SIGNAL(timeout()),this->player, SLOT(land()));
    }
}

void Movement::showrollbutton(){
    d->rollStart->show();
    timer->stop();
    step_walked=0;
}





