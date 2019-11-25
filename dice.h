#ifndef ROLLDICE_H
#define ROLLDICE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMovie>
#include <QLayout>

class Dice : public QWidget{
    Q_OBJECT
public:
    Dice(QWidget * parent = nullptr);
    ~Dice();

    int getresult(){return result;}
    QPushButton *next;
    QPushButton *rollStart;
    QLabel* infobar;
private slots:
     void roll_clicked();
     void dice_result_shown();
     void next_clicked();

private:
    int result;
    QMovie *animation;
    QLabel *animatedisplay;

};


#endif // ROLLDICE_H
