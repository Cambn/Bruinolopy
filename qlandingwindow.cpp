#include "qlandingwindow.h"
#include "mainwindow.h"
#include <QDialog>

QLandingWindow::QLandingWindow(QObject* _game, QWidget* parent):
    QWidget(parent),
    layout(new QGridLayout(this)),
    game(_game)
{}

QLandingWindow::QLandingWindow(QWidget* _mainWidget, QObject* game, QWidget* parent):
    QWidget(parent),
    layout(new QGridLayout(this)),
    mainWidget(_mainWidget)
    {}

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

void NoOptionWindow(QWidget*parent, QString statement){
    QDialog* content = new QDialog(parent);
    QHBoxLayout* layout = new QHBoxLayout;
    QLabel* lb = new QLabel(statement);
    content->setFixedSize(400,200);
    layout->addWidget(lb);
    content->setLayout(layout);
    content->setWindowTitle("Notice");
    content->show();
}

