#ifndef SUBWINDOW_H
#define SUBWINDOW_H
#include "mainwindow.h"
#include "gameboard.h"
#include "playerinfodisplay.h"
#include <QApplication>
#include <QComboBox>

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
    subWindow* window2;

public:
    explicit subWindow(QWidget *parent = nullptr);
    Statics s;
    ~subWindow(){delete window2;}


public slots:
    void comfirm_num(int);
    void GoSettingPage2();
    void GoGameboard();

friend WelcomeWindow;
};

#endif // SUBWINDOW_H
