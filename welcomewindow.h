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
    void resizeEvent(QResizeEvent *evt);
    explicit WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow(){delete rule;delete record;delete game_setup;}

private:
    QPushButton* sound;
    QMediaPlayer* music;
    void GeneralBtnSetup(QPushButton* &b, QHBoxLayout* &btnlayout);
    QWidget* rule;
    QWidget* record;
    subWindow *game_setup;

signals:

public slots:
    void soundclick();
    void GoRulePage();
    void GoRecordsPage();
    void GoSettingPage();
};

#endif // WELCOMEWINDOW_H
