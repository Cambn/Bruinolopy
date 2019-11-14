#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <QWidget>
#include "QPainter"
#include "gameboard.h"
#include <QtGui>
namespace Ui {
class Movement;
}

class Movement : public QWidget
{
    Q_OBJECT

public:
    friend class GameBoard;
    explicit Movement(QWidget *parent = nullptr);
    ~Movement();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void render(QPainter *p, GameBoard *A);
    Ui::Movement *ui;
    //pointer to a picture
    QPixmap *Img;
    //the rectangle info of that picture. When the picture moves,x and y changes correspondingly
    QRect *ImgRect;
protected:
    int shrinkMultiple;
    int speed;
};

#endif // MOVEMENT_H
