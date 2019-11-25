#ifndef SUBWINDOW_H
#define SUBWINDOW_H
#include "welcomewindow.h"
#include "mainwindow.h"
#include "gameboard.h"
#include "playerinfodisplay.h"
#include <QApplication>

class Statics;

class subWindow : public QWidget{
    Q_OBJECT

private:
    int num_player;
    QStringList names;
    QStringList charactors;
    QVector<QComboBox*> CBlist;
    QVector<QLineEdit*> LElist;
    QVector<QString> token_list= {"panda", "brown bear", "polar bear","grey bear"};
    QVector<QComboBox*> firstCBlist;

public:
    explicit subWindow(QWidget *parent = nullptr);
    Statics s;


public slots:
    void comfirm_num(int);
    void GoSettingPage2();
    void GoGameboard();

friend WelcomeWindow;
friend GameManager;
};

#endif // SUBWINDOW_H
