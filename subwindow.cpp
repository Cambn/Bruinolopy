#include "subwindow.h"
#include "gameboard.h"


void subWindow::comfirm_num(int _num){
    num_player = _num;
}

void subWindow::GoSettingPage2(){
    this->hide();
    subWindow *window2 = new subWindow;
    window2->setFixedSize(1600,900);
    window2->setWindowTitle("Game Set up");
    QPixmap bkgnd(":/fig/setting_bkgd.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);
    window2->setPalette(p);
    window2->comfirm_num(num_player);
    QVBoxLayout *layout = new QVBoxLayout;
    for (int a = 0 ; a < window2->num_player ; ++a){
        QVBoxLayout *layout2 = new QVBoxLayout;
        QFont labelfont("Times",15);
        QLabel *lb2 = new QLabel("Please enter the nickname of player "+ QString::number(a+1) +":\n");
        QLineEdit *txt = new QLineEdit();
        txt->setText("Please give a nickname");
        QComboBox *combobox = new QComboBox();
        QPushButton *ok= new QPushButton("OK");
        combobox->setMaximumSize(200,50);
        txt->setMaximumSize(300,50);
        ok->setMaximumSize(100,50);
        Comboboxlist.append(combobox);
        combobox->addItem(QIcon(":/fig/panda.png"),"Panda");
        combobox->addItem(QIcon(":/fig/brownbear.png"),"Brown Bear");
        combobox->addItem(QIcon(":/fig/polarbear.png"),"Polar Bear");
        lb2->setFont(labelfont);
        txt->setFont(labelfont);
        combobox->setFont(labelfont);
        ok->setFont(labelfont);
        layout2->addWidget(lb2);
        layout2->addWidget(txt);
        layout2->addWidget(combobox);
        layout2->addWidget(ok);
        layout2->setSpacing(10);
        layout->addLayout(layout2);
    }
    QPushButton* finish=new QPushButton("Finish Setting");
    layout->addWidget(finish);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(50);
    QObject::connect(finish,SIGNAL(clicked()),window2,SLOT(GoGameboard()));
    window2->setLayout(layout);
    window2->show();
}

void subWindow::GoGameboard(){
    MainWindow* w=new MainWindow;
    w->setFixedSize(1600,900);
    w->setWindowTitle("Bruinopoly");
    w->show();
    this->hide();
}
