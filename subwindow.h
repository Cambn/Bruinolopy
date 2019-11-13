#ifndef SUBWINDOW_H
#define SUBWINDOW_H
#include "welcomewindow.h"
#include "mainwindow.h"
#include "gameboard.h"
#include "playerinfodisplay.h"
#include <QApplication>


class subWindow : public QWidget{
    Q_OBJECT
private:
    int num_player;
    QVector<QString> names;
    QVector<QString> charactors;
    QVector<QComboBox*> Comboboxlist;
    QVector<QString> token_list= {"Panda", "Brown Bear", "Polar Bear"};

public:

public slots:
    void comfirm_num(int);
    void GoSettingPage2();
    void GoGameboard();
friend WelcomeWindow;
};

#endif // SUBWINDOW_H
