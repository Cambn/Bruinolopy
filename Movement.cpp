#include "Movement.h"
#include "ui_Movement.h"
Movement::Movement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Movement),
    shrinkMultiple(2),speed(10)
{
    ui->setupUi(this);
    Img = new QPixmap(":/mario.jpg");
    int width = Img-> width() / shrinkMultiple;
    int height = Img-> height() / shrinkMultiple;
    ImgRect = new QRect(10,10, width, height);
    QRect rect = this->geometry ();
    rect.setWidth (width *4);
    rect.setHeight (height *4);
    rect.setX(20);
    rect.setY(50);
    this ->setGeometry(rect);
}
void Movement::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        painter.drawPixmap(*ImgRect, *Img);

}
void Movement::mouseMoveEvent(QMouseEvent *event){

}
void Movement::keyPressEvent(QKeyEvent *event){
    int width = ImgRect -> width();
    int height = ImgRect ->height();
    switch(event -> key()){
    case Qt::Key_Left:
    {
        ImgRect ->setX(ImgRect->x() - speed);
        break;
    }
    case Qt::Key_Right:
    {
        ImgRect->setX(ImgRect->x()+speed);
        break;
    }
    case Qt::Key_Down:{
        ImgRect->setY(ImgRect->y()+speed);
        break;
    }
    case Qt::Key_Up:{
        ImgRect->setY(ImgRect->y()-speed);
        break;
    }
    }
    ImgRect->setHeight(height);
    ImgRect->setWidth(width);
    this ->repaint();

}
Movement::~Movement()
{
    delete Img;
    delete ImgRect;
    delete ui;
}

void Movement::render(QPainter *p,GameBoard *A){
    p->translate(A->size.height()/2, A->size.width()/2);

}
