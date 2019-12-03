/*#ifndef SUBWINDOW_H
#define SUBWINDOW_H
#include "mainwindow.h"
#include "gameboard.h"
#include "playerinfodisplay.h"
#include <QApplication>
#include <QComboBox>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
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
    QVector<QHBoxLayout*> layout_forupdate;//for player nick name
    QVector<QHBoxLayout*> layout_forupdate_icon;// for player icon
public:
    explicit subWindow(QWidget *parent = nullptr);
    Statics s;
   // void PlayNickNameArea(subWindow* window2, QVBoxLayout *layout,QWidget *parent, int numberofplayer);
    bool checking_inputEmpty(subWindow* a);
    bool checking_Nickname(subWindow* a);
    bool checking_Icon(subWindow* a);
public slots:
    void comfirm_num(int);
    void GoSettingPage2();
    void GoGameboard(subWindow *a);
    void checkvalidation(subWindow* window2);
    void succeed(){}

friend WelcomeWindow;
};

#endif // SUBWINDOW_H*/
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

public:
    explicit subWindow(QWidget *parent = nullptr);
    Statics s;


public slots:
    void comfirm_num(int);
    void GoSettingPage2();
    void GoGameboard();

friend WelcomeWindow;
};

#endif // SUBWINDOW_H
