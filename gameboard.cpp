#include "gameboard.h"



GameBoard::GameBoard(QWidget *parent):QWidget(parent){
    QGridLayout *mainLayout = new QGridLayout(this);

    //create picture blocks and text blocks
    for(int column = 0; column<BoardLength; ++column){
        for(int row = 0; row<BoardWidth; ++row){
            pixmapLabels[column][row] = createPixmapLabel();
            pixmapLabels[column][row]->setParent(this);
            mainLayout ->addWidget(pixmapLabels[column][row], row+1, column+1);
        }
    }

    //fix size of label
    for(int column = 0; column<BoardLength; ++column){
        for(int row = 0; row< BoardWidth; ++row){
            pixmapLabels[column][row]->setFixedSize(pixmapLabels[0][0]->size());
        }
    }

    //hide labels in the middle
    for(int column = 1; column<BoardLength-1; ++column){
        for(int row = 1; row< BoardWidth-1; ++row){
           pixmapLabels[column][row]->hide();
       }
    }

    int a = pixmapLabels[1][1]->width();
    int b = pixmapLabels[1][1]->height();

    QPixmap bg=  QPixmap(":/fig/chancecard.png");
    pixmapLabels[0][0]->setPixmap(bg.scaled(a,b, Qt::IgnoreAspectRatio));
    pixmapLabels[4][4]->setPixmap(bg.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb1(":/fig/Fowler.png");
    pixmapLabels[1][0]->setPixmap(lb1.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb2(":/fig/Railway.png");
    pixmapLabels[2][0]->setPixmap(lb2.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb3(":/fig/royceHall.png");
    pixmapLabels[3][0]->setPixmap(lb3.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb4(":/fig/Jail.png");
    pixmapLabels[4][0]->setPixmap(lb4.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb5(":/fig/SociologyB.jpg");
    pixmapLabels[4][1]->setPixmap(lb5.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb6(":/fig/MusicB.jpg");
    pixmapLabels[4][2]->setPixmap(lb6.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb7(":/fig/dicksonCourt.jpg");
    pixmapLabels[4][3]->setPixmap(lb7.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb8(":/fig/powell.jpg");
    pixmapLabels[3][4]->setPixmap(lb8.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb9(":/fig/Railway.png");
    pixmapLabels[2][4]->setPixmap(lb9.scaled(a,b,Qt::IgnoreAspectRatio));

    QPixmap lb10(":/fig/Kerckhoff.png");
    pixmapLabels[1][4]->setPixmap(lb10.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb11(":/fig/bear.png");
    pixmapLabels[0][3]->setPixmap(lb11.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb12(":/fig/InstramuralField.png");
    pixmapLabels[0][2]->setPixmap(lb12.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb13(":/fig/msb.png");
    pixmapLabels[0][1]->setPixmap(lb13.scaled(a,b, Qt::IgnoreAspectRatio));

    pixmapLabels[0][4]->setText("Start!");
}

QLabel *GameBoard::createPixmapLabel(){
    QLabel *label = new QLabel(this);
    label ->setAlignment(Qt::AlignCenter);
    label ->setFrameShape(QFrame::Box);
    label ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label ->setBackgroundRole(QPalette::Base);
    label ->setAutoFillBackground(true);
    label ->setMinimumSize(1488/BoardWidth,520/BoardLength);
    return label;
}


