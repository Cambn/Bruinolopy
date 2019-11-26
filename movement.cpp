#include "movement.h"
#include "player.h"

Movement::Movement(QWidget *parent,int order, int money, QString address) :
    QWidget(parent),position(0),modify_x(order),money(money)
{
    for (int i=0;i<12;i++){
        xAxis[i]+=(width+5)*modify_x;
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

Movement::Movement( Player& _player,int turnNumber, const QString& address, QWidget *parent) :
    QWidget(parent), player(&_player),
    d(new Dice(this)),
    Img(new QPixmap(address)),
    position(player->getPos()),
    money(player->money()),
    modify_x(turnNumber)
{
    for (int i=0;i<12;i++){
        xAxis[i]+=(width+5)*modify_x;
    }

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
    if(position/12<(position+d->getresult())/12){
        money+=1000;
    }
    timer=new QTimer(this);
    timer->start(250);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(one_step()));
    //d->rollStart->show();
}

void Movement::one_step(){
    if (step_walked < d->getresult()){

        position+=1;
        this->player->move(1);

        ImgRect ->setX(xAxis[position%12]);
        ImgRect ->setY(yAxis[position%12]);
        ImgRect->setHeight(height);
        ImgRect->setWidth(width);
        repaint();
        step_walked++;
    }
    else
    {
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(showrollbutton()));
        timer->stop();
        timer->start(250);
    }

}

void Movement::showrollbutton(){
    d->rollStart->show();
    timer->stop();
    step_walked=0;
}



Movement::~Movement()
{
    delete Img;
    delete ImgRect;
    delete timer;
    delete timer2;

}


