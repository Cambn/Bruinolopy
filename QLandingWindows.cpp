#include "QLandingWindows.h"
#include "mainwindow.h"

#include <QGridLayout>

QLandingWindow::QLandingWindow(QObject* _game, QWidget* parent):
    QWidget(parent),
    layout(new QGridLayout(this)),
    game(_game)
{

    if(dynamic_cast<MainWindow*>(game)){//if we passed it a game pointer
            MainWindow* temp  = dynamic_cast<MainWindow*>(_game);
            temp->addTempObject(this); //add it to the game's object management
    }
    else if(dynamic_cast<Player*>(game)){
        Player* temp = dynamic_cast<Player*>(_game);//if we passed it a player pointer
        temp->addTempObject(this);  //add it to the player's memory management
    }
}

QLandingWindow::QLandingWindow(QWidget* _mainWidget, QObject* game, QWidget* parent):
    QWidget(parent),
    layout(new QGridLayout(this)),
    mainWidget(_mainWidget)
    {
    if(dynamic_cast<MainWindow*>(game)){//if we passed it a game pointer
            MainWindow* temp  = dynamic_cast<MainWindow*>(game);
            temp->addTempObject(this); //add it to the game's object management
    }
    else if(dynamic_cast<Player*>(game)){
        Player* temp = dynamic_cast<Player*>(game);//if we passed it a player pointer
        temp->addTempObject(this);  //add it to the player's memory management
    }
    }


QLandingWindow::~QLandingWindow() {
    if(dynamic_cast<MainWindow*>(game)){
            MainWindow* temp  = dynamic_cast<MainWindow*>(game);
            temp->eraseTempObject(this);
    }
    else if(dynamic_cast<Player*>(game)){
        Player* temp = dynamic_cast<Player*>(game);
        temp->eraseTempObject(this);
    }

    delete layout;
    delete mainWidget;
}


//QLandingOptions Stuff

QLandingOptions::QLandingOptions(
        QWidget* _mainWidget,
        const QString& _prompt,
        QObject* _game,
        const QString& leftOpt,
        const QString& rightOpt,
        QWidget* parent          )
        :
        QLandingWindow(_mainWidget,_game, parent),
        prompt(new QLabel(_prompt, this)),
        left( new QPushButton(leftOpt,this)),
        right( new QPushButton(rightOpt,this))
    {
        this->setAttribute(Qt::WA_DeleteOnClose); //shortlived window don't want it keeping memory after closed

        layout->addWidget(mainWidget,0,0);
        layout->addWidget(prompt,2,0);
        layout->addWidget(left,3,0);
        layout->addWidget(right,4,0);
        this->setLayout(layout);

        sizeHint();

        show();

        //close window once we click a button
        connect(left, &QPushButton::clicked, this, &QWidget::close);
        connect(right, &QPushButton::clicked, this, &QWidget::close);
    }

QLandingOptions::~QLandingOptions() {
    delete prompt;
    delete left;
    delete right;
}




//QLandNoOptions Stuff
QLandNoOptions::QLandNoOptions(QWidget* _mainWidget,
                               const QString& _message,
                               QObject* _game,
                               const QString& buttonText,
                               QWidget* parent)
                               :
                               QLandingWindow(_mainWidget,_game, parent),
                               message(new QLabel(_message,this)),
                               button(new QPushButton(buttonText,this))
{
    this -> setAttribute((Qt::WA_DeleteOnClose)); //shortlived window don't want it keeping memory after closed

    layout->addWidget(mainWidget, 0,0);
    layout->addWidget(message,2,0);
    layout->addWidget(button,3,0);
    this->setLayout(layout);

    sizeHint();
    show();

    connect(button, &QPushButton::clicked, this, &QWidget::close); //closes window w/ button
}

QLandNoOptions::~QLandNoOptions() {
    delete message;
    delete button;
}
