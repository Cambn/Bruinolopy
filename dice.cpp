
#include "dice.h"
Dice::~Dice(){
    delete animation;
    delete animatedisplay;
    delete next;
    delete rollStart;
}


Dice::Dice(QWidget *parent) : QWidget(parent){
   setFixedSize(300,160);
   infobar= new QLabel(this);
   infobar->setFixedSize(300,40);
   rollStart = new QPushButton("Roll",this);
   rollStart->setFixedSize(100,90);
   animation = new QMovie(":/dice/rolling.gif");
   animatedisplay = new QLabel(this);
   animatedisplay->setFixedSize(100,100);
   next = new QPushButton("Next",this);
   next->setFixedSize(100,90);
   QObject::connect(rollStart, SIGNAL(clicked()), this, SLOT(roll_clicked()));
   QHBoxLayout* mainlayout=new QHBoxLayout();
   mainlayout->addWidget(rollStart);
   mainlayout->addWidget(next);
   mainlayout->addWidget(animatedisplay);
   QVBoxLayout* anotherlyt=new QVBoxLayout(this);
   anotherlyt->addWidget(infobar);
   anotherlyt->addLayout(mainlayout);
   setLayout(anotherlyt);
   show();
   next->hide();
}

void Dice::roll_clicked(){
    rollStart->hide();
    animatedisplay->clear();
    animatedisplay->setMovie(animation);
    animation->setScaledSize(animatedisplay->size());
    animation->start();
    QObject::connect(animation, SIGNAL(finished()), this, SLOT(dice_result_shown()));
};

void Dice::dice_result_shown(){
    qsrand(time(0));
    int dice_result = qrand() % 6 + 1;
    QPixmap dice_side1(":/dice/dice1.png");
    QPixmap dice_side2(":/dice/dice2.png");
    QPixmap dice_side3(":/dice/dice3.png");
    QPixmap dice_side4(":/dice/dice4.png");
    QPixmap dice_side5(":/dice/dice5.png");
    QPixmap dice_side6(":/dice/dice6.png");
    QVector<QPixmap> die_list{dice_side1, dice_side2, dice_side3, dice_side4, dice_side5, dice_side6};
    QPixmap current_dice(die_list[dice_result-1]);
    animatedisplay->clear();
    animatedisplay->setPixmap(current_dice);
    current_dice.scaled(animatedisplay->size(),Qt::IgnoreAspectRatio);
    next->show();
    QObject::connect(next, SIGNAL(clicked()), this, SLOT(next_clicked()));
    result=dice_result;
}

void Dice::next_clicked(){
    next->hide();
    animatedisplay->clear();
}
