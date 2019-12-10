#ifndef SUBWINDOW_H
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
    QVector<QHBoxLayout*> layout_forUpdate;//for player nick name
    QVector<QHBoxLayout*> layout_forUpdate_icon;// for player icon
    //warning labels
    QLabel* warningLabel_name = new QLabel();
    QLabel* warningLabel_icon = new QLabel();
public:
    explicit subWindow(QWidget *parent = nullptr);
    Statics s;
   // void PlayNickNameArea(subWindow* window2, QVBoxLayout *layout,QWidget *parent, int numberofplayer);
    //checking functions
    bool checking_inputEmpty();//checks if the player input is empty. Return true if is empty indeed
    bool checking_Nickname();//check if the player name are the same. Return true if two are the same.
    bool checking_Icon();//check if the player choose the same icon. Return true if icons are the same
public slots:
    void comfirm_num(int);
    void GoSettingPage2();
    void GoGameboard();
    void checkValidation();//implement the checking


signals:
    //when checkings are passed, emit this signal to pass to the game board . 
    void succeed();

friend WelcomeWindow;
};

#endif // SUBWINDOW_H
