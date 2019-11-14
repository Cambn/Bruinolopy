#include "playerinfodisplay.h"
#include "ui_playerinfodisplay.h"

PlayerInfoDisplay::PlayerInfoDisplay(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout(this);
    for(int column = 0; column<BoardLength;++column){
        mainLayout ->addWidget(createPlayerHeader(PlayerInfoDisplay::PlayerNames().at(column)), 0, column+1);
        playerPixmap[column] = createPlayerPixmap();
        mainLayout ->addWidget(playerPixmap[column], 1, column+1);
    }
}
QLabel *PlayerInfoDisplay::createPlayerHeader(const QString &text){
    QLabel *label = new QLabel(tr("<b>%1</b>").arg(text));
    label ->setAlignment(Qt::AlignCenter);
    return label;
}
QStringList PlayerInfoDisplay::PlayerNames(){
    static const QStringList result = {tr("Player1: "),tr("Player2: "),tr("Player3: "),tr("Player4: ")};
    return result;
}
QLabel *PlayerInfoDisplay::createPlayerPixmap(){
    QLabel *label = new QLabel;
    //QFrame *custom = new QFrame;
    label ->setEnabled(false);
    label ->setAlignment(Qt::AlignCenter);
    label ->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label ->setLineWidth(2);
    label ->setMidLineWidth(3);
    label ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label ->setBackgroundRole(QPalette::Base);
    label ->setAutoFillBackground(true);
    label ->setMinimumSize(130,60);
return label;
}
