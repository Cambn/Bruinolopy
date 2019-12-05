#ifndef SUBWINDOW_H
#define SUBWINDOW_H
#include "mainwindow.h"
#include "gameboard.h"
#include "playerinfodisplay.h"
#include <QApplication>
#include <QComboBox>
#include <iostream>

class Statics;
class WelcomeWindow;

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
    //warning layouts:
    QVector<QHBoxLayout*> layout_forUpdate;//for player nick name
    QVector<QHBoxLayout*> layout_forUpdate_icon;// for player icon
    //warning labels
    QLabel* warningLabel_name = new QLabel();
    QLabel* warningLabel_icon = new QLabel();

public:
    explicit subWindow(QWidget *parent = nullptr);
    Statics s;

    //checking functions
    bool checking_inputEmpty();
    bool checking_Nickname();
    bool checking_Icon();

public slots:
    void comfirm_num(int);
    void GoSettingPage2();//go to the second setting page
    void GoGameboard();//go to mainwindow
    void checkValidation();//implement the checking

signals:
    void succeed();

friend WelcomeWindow;
};

#endif // SUBWINDOW_H
