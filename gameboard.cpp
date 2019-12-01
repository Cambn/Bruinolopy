#include "gameboard.h"


GameBoard::GameBoard(QWidget *parent):QWidget(parent){
    QGridLayout *mainLayout = new QGridLayout(this);

    //create blocks
    for(int column = 0; column<BoardLength; ++column){
        for(int row = 0; row< BoardWidth; ++row){
            pixmapLabels[column][row] = createPixmapLabel();
            pixmapLabels[column][row]->setParent(this);
            mainLayout ->addWidget(pixmapLabels[column][row], row+1, column+1);
        }
    }
    for(int column = 0; column<BoardLength; ++column){
        for(int row = 0; row< BoardWidth; ++row){
            pixmapLabels[column][row]->setFixedSize(pixmapLabels[0][0]->size());
        }
    }

    for(int column = 1; column<BoardLength-1; ++column){
        for(int row = 1; row< BoardWidth-1; ++row){
           pixmapLabels[column][row]->hide();
       }
    }

    QPixmap bg=  QPixmap(":/fig/chancecard.png");
    pixmapLabels[0][0]->setPixmap(bg.scaled(pixmapLabels[0][0]->width(), pixmapLabels[0][0]->height(), Qt::IgnoreAspectRatio));

    int a = pixmapLabels[1][1]->width();
    int b = pixmapLabels[1][1]->height();

    QPixmap lb1(":/images/tiles/Fowler.png");
    pixmapLabels[1][0]->setPixmap(lb1.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb2(":/images/tiles/Railway.png");
    pixmapLabels[2][0]->setPixmap(lb2.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb3(":/images/tiles/royceHall.png");
    pixmapLabels[3][0]->setPixmap(lb3.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb4(":/images/tiles/Jail.png");
    pixmapLabels[4][0]->setPixmap(lb4.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb5(":/images/tiles/SociologyB.jpg");
    pixmapLabels[4][1]->setPixmap(lb5.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb6(":/images/tiles/MusicB.jpg");
    pixmapLabels[4][2]->setPixmap(lb6.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb7(":/images/tiles/dicksonCourt.jpg");
    pixmapLabels[4][3]->setPixmap(lb7.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb8(":/images/tiles/powell.jpg");
    pixmapLabels[3][4]->setPixmap(lb8.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb9(":/images/tiles/Railway.png");
    pixmapLabels[2][4]->setPixmap(lb9.scaled(a,b,Qt::IgnoreAspectRatio));

    QPixmap lb10(":/images/tiles/Kerckhoff.png");
    pixmapLabels[1][4]->setPixmap(lb10.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb11(":/images/tiles/bear.png");
    pixmapLabels[0][3]->setPixmap(lb11.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb12(":/images/tiles/InstramuralField.png");
    pixmapLabels[0][2]->setPixmap(lb12.scaled(a,b, Qt::IgnoreAspectRatio));

    QPixmap lb13(":/images/tiles/msb.png");
    pixmapLabels[0][1]->setPixmap(lb13.scaled(a,b, Qt::IgnoreAspectRatio));


    QPixmap chanceLabel(":/images/tiles/chancecard.png");
    pixmapLabels[0][0]->setPixmap(chanceLabel.scaled(a,b, Qt::IgnoreAspectRatio));
    pixmapLabels[4][4]->setPixmap(chanceLabel.scaled(a,b, Qt::IgnoreAspectRatio));





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


