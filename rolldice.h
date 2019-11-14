#ifndef ROLLDICE_H
#define ROLLDICE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMovie>
#include <QLayout>
#include <QTime>
#include <QPixmap>
#include <QVector>

class Dice : public QWidget{
    Q_OBJECT
public:
    Dice(QWidget * parent = 0);
    //~Dice();
private slots:
     void roll();
     void dice_result();
private:
    QWidget *main;
    QMovie *rolldice;
    QLabel *dicedisplay;
    QPushButton *rollStart;
    QPushButton *rollStop;
    QLayout *layout_main;
    QLayout *layout_sub;
    QWidget *roll_page;
    QWidget *result_window;
    QLayout *layout_subpage;
    QLabel *display1;
    QLabel *display2;
    QPushButton *move;

};


#endif // ROLLDICE_H
