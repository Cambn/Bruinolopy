#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H
#include "statics.h"
#include "subwindow.h"
#include <QLineEdit>
#include <QComboBox>
#include <QStringList>
#include <QVector>
#include <QSpinBox>
#include <QLabel>
#include <QPixmap>
#include <QApplication>
#include <QObject>
#include <QLayout>
#include <QWidget>
#include <QSize>
#include <QMediaPlayer>
#include <QPushButton>
#include <QFont>

class WelcomeWindow : public QWidget
{
    Q_OBJECT
public:
    //set bkgd and resize it
    void resizeEvent(QResizeEvent *evt);
    explicit WelcomeWindow(QWidget *parent = nullptr);

private:
    QPushButton* sound;
    QMediaPlayer* music;

    //set the buttons at the bottom of the page
    //@b a button ptr
    //@btnlayout the layout ptr of 3 buttons
    void GeneralBtnSetup(QPushButton* &b, QHBoxLayout* &btnlayout);

signals:

public slots:
    //mute or replay sound
    void soundclick();
    //rule page setting
    void GoRulePage();
    //records page setting
    void GoRecordsPage();
    //first setting page setting
    void GoSettingPage();
};

#endif // WELCOMEWINDOW_H
