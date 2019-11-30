#include "gameboard.h"
#include "board.h"
#include <QPixmap>

QStringList GameBoard::iconLengthNames(){
    static const QStringList result = {tr("L1"),tr("L2"),tr("L3"),tr("L4")};
    return result;
}
QStringList GameBoard::iconWidthNames(){
    static const QStringList result = {tr("W1"),tr("W2"),tr("W3"),tr("W4")};
    return result;
}
GameBoard::GameBoard(QWidget *parent):QWidget(parent){
    QGridLayout *mainLayout = new QGridLayout(this);
    //game board
    /*
    for(int row =0; row < BoardWidth;++row){
        WidthLabels[row]=createHeaderLabel(GameBoard::iconWidthNames().at(row));
        mainLayout ->addWidget(WidthLabels[row], row+1, 0);
    }
    for(int column = 0; column<BoardLength;++column){
        LengthLabels[column]=createHeaderLabel(GameBoard::iconLengthNames().at(column));
        mainLayout ->addWidget(LengthLabels[column], 0, column+1);
    }*/
    for(int column = 0; column<BoardLength; ++column){
        for(int row = 0; row< BoardWidth; ++row){

            pixmapLabels[column][row] = createPixmapLabel();

            mainLayout ->addWidget(pixmapLabels[column][row], row+1, column+1);

        }

    }

}

GameBoard::GameBoard(Board& _board, QWidget *parent):QWidget(parent){
    QGridLayout *mainLayout = new QGridLayout(this);

    for(int column = 0; column<BoardLength; ++column){
        for(int row = 0; row< BoardWidth; ++row){
            pixmapLabels[column][row] = createPixmapLabel();
            //makeTileImages(column,row, _board);
            mainLayout ->addWidget(pixmapLabels[column][row], row+1, column+1);


            }


        }

    }


void GameBoard::makeTileImages(int column, int row, Board& _board) {
    if (column ==0) {//if on the left side of gameBoard
        int i = column + 4 - row;
        QPixmap* image = _board.getTile(i) ->generateBoardView();
        //pixmapLabels[0][0]->setPixmap(bg.scaled(pixmapLabels[0][0]->width(), pixmapLabels[0][0]->height(), Qt::IgnoreAspectRatio))
        pixmapLabels[column][row]->setPixmap((*image).scaled(pixmapLabels[0][0]->width(), pixmapLabels[0][0]->height(), Qt::IgnoreAspectRatio));
    }
    else if (column ==BoardWidth) {//if on the right side of gameBoard
        int i = column + 4 - row;
        QPixmap* image = _board.getTile(i) ->generateBoardView();
        pixmapLabels[column][row]->setPixmap((*image).scaled(pixmapLabels[0][0]->width(), pixmapLabels[0][0]->height(), Qt::IgnoreAspectRatio));
    }
    else if (row ==0) {//if on the top row of gameBoard, not counting the first and last column
        int i = column + 4 - row;
        QPixmap* image = _board.getTile(i) ->generateBoardView();
        pixmapLabels[column][row]->setPixmap((*image).scaled(pixmapLabels[0][0]->width(), pixmapLabels[0][0]->height(), Qt::IgnoreAspectRatio));
    }
    else if (row ==BoardLength) {//if on the bottom row of gameBoard, not counting the first and last column
        int i = column + 4 - row;
        QPixmap* image = _board.getTile(i) ->generateBoardView();
        pixmapLabels[column][row]->setPixmap((*image).scaled(pixmapLabels[0][0]->width(), pixmapLabels[0][0]->height(), Qt::IgnoreAspectRatio));

    }
    else {} //if on the inside, do nothing.

}



    //Player info



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


//convert the string into a pointer to QLabel object
QLabel *GameBoard::createHeaderLabel(const QString &text){
    QLabel *label = new QLabel(tr("<b>%1</b>").arg(text));
    label ->setAlignment(Qt::AlignCenter);
    return label;
}
/*
void GameBoard::updatePixmapLabels(){
    QWindow *window = nullptr;
    if(const QWidget *nativeParent = nativeParentWidget()){
        window = nativeParent ->windowHandle();
    }
    for(int column=0;column<BoardLength; ++column){
        for(int row = 0; row <BoardWidth; ++row){
          const QPixmap pixmap(5,5);
        QLabel *pixmapLabel= pixmapLabels[column][row];
        pixmapLabel ->setPixmap(pixmap);
        pixmapLabel ->setEnabled(!pixmap.isNull());
        QString toolTip;
        if(!pixmap.isNull()){
            const QSize actualSize = icon.actualSize(size);
            toolTip = tr("Size: %1x%2\nActual Size: %3x%4\nDevice pixel ratio: %5")
                    .arg(size.width()).arg(size.height()).arg(actualSize.width()).
                    arg(actualSize.height()).arg(pixmap.devicePixelRatioF());

        }
        pixmapLabel ->setToolTip(toolTip);
    }
    }
}
*/
/*
QVector<QIcon::Mode> GameBoard::iconModes()
{
    static const QVector<QIcon::Mode> result = {QIcon::Normal, QIcon::Active, QIcon::Disabled, QIcon::Selected};
    return result;
}
QVector<QIcon::State> GameBoard::iconStates(){
    static const QVector<QIcon::State> result = {QIcon::Off,QIcon::On};
    return result;
}*/
/*
//changes the icon or the icon size, and make sure is updated
void GameBoard::setIcon(const QIcon &icon){
    this ->icon = icon;
    updatePixmapLabels();
}
void GameBoard::setSize(const QSize &size){
    if(size!=this ->size){
        this ->size = size;
        updatePixmapLabels();
    }
}*/
