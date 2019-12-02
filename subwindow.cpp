#include "subwindow.h"
#include "gameboard.h"
#include <QLineEdit>

subWindow::subWindow(QWidget *parent) : QWidget(parent){}

void subWindow::comfirm_num(int _num){
    num_player = _num;
}

void subWindow::GoSettingPage2(){
    Statics a(firstCBlist[1]->currentText().toInt(),firstCBlist[0]->currentText().toInt(),
            firstCBlist[2]->currentText().toInt(),firstCBlist[3]->currentText().toInt());
    s=a;
    this->hide();
    subWindow* window2 = new subWindow();
    window2->setAttribute(Qt::WA_DeleteOnClose);
    window2->s=this->s;
    window2->setFixedSize(1600,900);
    window2->setWindowTitle("Game Set up");

    QPixmap bkgnd(":/fig/setting_bkgd.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);
    window2->setPalette(p);
    window2->comfirm_num(num_player);
    QVBoxLayout *layout = new QVBoxLayout();
    for (int numberofplayer = 0 ; numberofplayer < window2->num_player ; ++numberofplayer){
        QVBoxLayout *layout2 = new QVBoxLayout();
        QFont labelfont("Times",15);
        QLabel *lb2 = new QLabel("Please enter the nickname of player "+ QString::number(numberofplayer+1) +":\n",this);

        QLineEdit *txt = new QLineEdit(this);
       // txt->maxLength(20);
        window2->LElist.append(txt);
        txt->setText("Please give a nickname");
        QComboBox *combobox = new QComboBox(this);
        combobox->setMaximumSize(200,50);
        txt->setMaximumSize(300,50);
        window2->CBlist.append(combobox);

        combobox->addItem(QIcon(":/fig/panda.png"),"Panda");
        combobox->addItem(QIcon(":/fig/brownbear.png"),"Brown Bear");
        combobox->addItem(QIcon(":/fig/polarbear.png"),"Polar Bear");
        combobox->addItem(QIcon(":/fig/greybear.png"),"Grey Bear");

        lb2->setFont(labelfont);
        txt->setFont(labelfont);
        combobox->setFont(labelfont);

        layout2->addWidget(lb2);
        layout2->addWidget(txt);
        layout2->addWidget(combobox);
        layout2->setSpacing(10);
        layout->addLayout(layout2);
    }
    QPushButton* finish=new QPushButton("Finish Setting",this);
    layout->addWidget(finish);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(50);
    QObject::connect(finish,SIGNAL(clicked()),window2,SLOT(GoGameboard()));
    window2->setLayout(layout);
    window2->show();

}

void subWindow::GoGameboard(){

    for (int i=0;i<LElist.length();i++){
        names.append(LElist[i]->text());
        charactors.append(token_list[CBlist[i]->currentIndex()]);
    }

    MainWindow* w=new MainWindow(nullptr,LElist.length(),names,charactors,s);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->setFixedSize(1600,900);
    w->setWindowTitle("Bruinopoly");
    w->show();
    this->hide();
}
