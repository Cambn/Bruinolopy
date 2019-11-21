#include "gameboard.h"



GameBoard::GameBoard(QWidget *parent):QWidget(parent){
    QGridLayout *mainLayout = new QGridLayout(this);
    for(int column = 0; column<BoardLength; ++column){
        for(int row = 0; row< BoardWidth; ++row){
            pixmapLabels[column][row] = createPixmapLabel();
            mainLayout ->addWidget(pixmapLabels[column][row], row+1, column+1);
        }
    }
}

QLabel *GameBoard::createPixmapLabel(){
    QLabel *label = new QLabel;
    label ->setEnabled(false);
    label ->setAlignment(Qt::AlignCenter);
    label ->setFrameShape(QFrame::Box);
    label ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label ->setBackgroundRole(QPalette::Base);
    label ->setAutoFillBackground(true);
    label ->setMinimumSize(130,130);
    return label;
}


