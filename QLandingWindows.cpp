#include "QLandingWindows.h"

#include <QGridLayout>

QLandingWindow::QLandingWindow(QWidget* parent):
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
    }
