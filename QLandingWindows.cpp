#include "QLandingWindows.h"
#include "mainwindow.h"

#include <QGridLayout>

QLandingWindow::QLandingWindow( QWidget* parent):
    QWidget(parent),
    layout(new QGridLayout(this))
    {}

QLandingWindow::QLandingWindow(QWidget* _mainWidget, QWidget* parent):
    QWidget(parent),
    layout(new QGridLayout(this)),
    mainWidget(_mainWidget)
    {}




//QLandingOptions Stuff

QLandingOptions::QLandingOptions(
        QWidget* _mainWidget,
        const QString& _prompt,
        const QString& leftOpt,
        const QString& rightOpt,
        QWidget* parent          )
        :
        QLandingWindow(_mainWidget, parent),
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


//QLandNoOptions Stuff
QLandNoOptions::QLandNoOptions(QWidget* _mainWidget,
                               const QString& _message,
                               const QString& buttonText,
                               QWidget* parent)
                               :
                               QLandingWindow(_mainWidget,parent),
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

