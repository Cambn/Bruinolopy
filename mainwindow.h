#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QBoxLayout>
#include "gameboard.h"
#include "playerinfodisplay.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(){}

private:
    GameBoard *boardArea;
    PlayerInfoDisplay *playerArea;
};
#endif // MAINWINDOW_H
