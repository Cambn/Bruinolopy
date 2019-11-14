#include "rolldice.h"


Dice::Dice(QWidget *parent) : QWidget(parent){


    main = new QWidget;
    main->setFixedSize(300,300);
    rolldice = new QMovie(":/rolling.gif");
    roll_page = new QWidget;
    result_window = new QWidget;
    display1 = new QLabel;
    display2 = new QLabel;
    move = new QPushButton("move");


    
    roll_page->setFixedSize(300,300);
    dicedisplay = new QLabel;
    roll_page->setFixedSize(300,300);
    dicedisplay->setMovie(rolldice);
    rollStart = new QPushButton("Roll");
    rollStop = new QPushButton("Stop");
    layout_main = new QVBoxLayout;
    layout_sub = new QVBoxLayout;
    layout_subpage = new QVBoxLayout;
    layout_main->addWidget(rollStart);
    
    layout_sub->addWidget(dicedisplay);
    
    layout_sub->addWidget(rollStop);
    main->setLayout(layout_main);
    roll_page->setLayout(layout_sub);
    main->show();
    QObject::connect(rollStart, SIGNAL(clicked()), this, SLOT(roll()));
    

}


/*
Dice::~Dice(){

    delete rolldice;
    delete dicedisplay;
    delete rollStart;
    delete rollStop;
    delete layout_main;
    delete layout_sub;
    //delete roll_page;
    delete result_window;
    delete layout_subpage;
    delete display1;
    delete display2;
    delete move;

}
*/

void Dice::dice_result(){

    qsrand(time(NULL));
    int dice_result1 = qrand() % 6 + 1;
    int dice_result2 = qrand() % 6 + 1;
    QPixmap dice_side1(":/dice1.png");
    QPixmap dice_side2(":/dice2.png");
    QPixmap dice_side3(":/dice3.png");
    QPixmap dice_side4(":/dice4.png");
    QPixmap dice_side5(":/dice5.png");
    QPixmap dice_side6(":/dice6.png");

    QVector<QPixmap> die_list{dice_side1, dice_side2, dice_side3, dice_side4, dice_side5, dice_side6};

    QPixmap dice_1(die_list[dice_result1 - 1]);
    QPixmap dice_2(die_list[dice_result2 - 1]);

    result_window->setFixedSize(300,300);


    result_window->update();

    display1->update();
    display2->update();

    display1->setPixmap(dice_1);
    display2 ->setPixmap(dice_2);


    layout_subpage->addWidget(display1);
    layout_subpage->addWidget(display2);


    layout_subpage->addWidget(move);

    result_window->setLayout(layout_subpage);
    result_window -> show();

    QObject::connect(move, SIGNAL(clicked()), result_window, SLOT(close()));
    QObject::connect(move, SIGNAL(clicked()), roll_page, SLOT(close()));

}

void Dice::roll(){
    roll_page->show();
    rolldice->setScaledSize(main->size());
    dicedisplay->setMovie(rolldice);
    rolldice->start();
    QObject::connect(rollStop, SIGNAL(clicked()), this, SLOT(dice_result()));

};

