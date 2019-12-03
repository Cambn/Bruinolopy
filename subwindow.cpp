/*#include "subwindow.h"
#include "gameboard.h"
#include <QLineEdit>
#include <algorithm>
subWindow::subWindow(QWidget *parent) : QWidget(parent){
}

void subWindow::comfirm_num(int _num){
    num_player = _num;
}


void subWindow::GoSettingPage2(){
    Statics a(firstCBlist[1]->currentText().toInt(),firstCBlist[0]->currentText().toInt(),
            firstCBlist[2]->currentText().toInt(),firstCBlist[3]->currentText().toInt());
    s=a;
    this->hide();
    subWindow* window2 = new subWindow();
    window2->layout_forupdate.resize(num_player);
    for(size_t n = 0; n < window2->layout_forupdate.size(); ++n){
       window2->layout_forupdate[n] = new QHBoxLayout();
    }
    window2->layout_forupdate_icon.resize(num_player);
    for(size_t n = 0; n < window2->layout_forupdate_icon.size(); ++n){
       window2->layout_forupdate_icon[n] = new QHBoxLayout();
    }
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
    QVBoxLayout* layout_page2 = new QVBoxLayout();
    //this loop gets to set up the page
    for (int _numberofplayer = 0 ; _numberofplayer < window2->num_player ; ++_numberofplayer){
        QLabel *lb2 = new QLabel("Please enter the nickname of player "+ QString::number(_numberofplayer+1) +":\n",this);

        //lineEdit
        QLineEdit *txt = new QLineEdit(this);
        txt->setMaxLength(25);
        txt ->setPlaceholderText("Please give a nickname");
        txt->setMaximumSize(300,50);
        window2->LElist.append(txt);
        window2->layout_forupdate[_numberofplayer]->addWidget(txt);

        //ComboBox
        QComboBox *combobox = new QComboBox(this);
        combobox->setMaximumSize(200,50);
        combobox->addItem(QIcon(":/fig/panda.png"),"Panda");
        combobox->addItem(QIcon(":/fig/brownbear.png"),"Brown Bear");
        combobox->addItem(QIcon(":/fig/polarbear.png"),"Polar Bear");
        combobox->addItem(QIcon(":/fig/greybear.png"),"Grey Bear");
        window2->CBlist.append(combobox);
        window2->layout_forupdate_icon[_numberofplayer]->addWidget(combobox);

        //font
        QFont labelfont("Times",15);
        lb2->setFont(labelfont);
        txt->setFont(labelfont);
        combobox->setFont(labelfont);

        //set layout
        QVBoxLayout* layout2_page2 = new QVBoxLayout();
        layout2_page2->addWidget(lb2);
        layout2_page2->addLayout(window2->layout_forupdate[_numberofplayer]);
        layout2_page2->addLayout(window2->layout_forupdate_icon[_numberofplayer]);
        layout2_page2->setSpacing(10);
        layout_page2->addLayout(layout2_page2);
    }
    QPushButton* finish = new QPushButton("Finish Setting",this);
    layout_page2->addWidget(finish);
    layout_page2->setAlignment(Qt::AlignCenter);
    layout_page2->setSpacing(50);
    QObject::connect(finish,SIGNAL(clicked()),window2,SLOT(checkvalidation(window2)));
    QObject::connect(window2,SIGNAL(succeed()),window2,SLOT(GoGameboard(window2)));
    window2->setLayout(layout_page2);
    window2->show();

}

bool subWindow::checking_Nickname(subWindow* window2){
      if(std::adjacent_find(window2->LElist.begin(),window2->LElist.end(),std::not_equal_to<>())==window2->LElist.end()){
            return false;
    }
      else{ return true;}
}
bool subWindow::checking_Icon(subWindow *window2){
    if(std::adjacent_find(window2->CBlist.begin(),window2->CBlist.end(),std::not_equal_to<>())==window2->CBlist.end()){
        return false;
        }
    else{ return true;}
}
bool subWindow::checking_inputEmpty(subWindow* window2){
    for (int _numberofplayer = 0 ; _numberofplayer < this->num_player ; ++_numberofplayer){
        if(window2->LElist[_numberofplayer]->text().isEmpty()){
            return true;
        }
    }
            return false;
}
void subWindow::checkvalidation(subWindow* window2){
        if(checking_inputEmpty(window2)){
            QLabel *errormesssage = new QLabel("Error: Nickname cannot be empty. ");
            errormesssage->setStyleSheet("color:red;");
            for(size_t n = 0; n < layout_forupdate.size(); ++n){
            window2->layout_forupdate[n]->addWidget(errormesssage);
            }
        }
        else if(checking_Icon(window2)){
            QLabel *errormesssage = new QLabel("Error: Icon cannot be the same. ");
            errormesssage->setStyleSheet("color:red;");
            for(size_t n = 0; n < layout_forupdate.size(); ++n){
            window2->layout_forupdate_icon[n]->addWidget(errormesssage);
            }
        }
        else if(checking_Nickname(window2)){
            QLabel *errormesssage = new QLabel("Error: Nickname cannot be the same. ");
            errormesssage->setStyleSheet("color:red;");
            for(size_t n = 0; n < layout_forupdate.size(); ++n){
            window2->layout_forupdate[n]->addWidget(errormesssage);
            }
        }
        else{
            emit succeed();
        }
}
void subWindow::GoGameboard(subWindow* window2){

    for (int i=0;i<window2->LElist.length();i++){
        names.append(window2->LElist[i]->text());
        charactors.append(token_list[CBlist[i]->currentIndex()]);
    }

    MainWindow* w=new MainWindow(nullptr,LElist.length(),names,charactors,s);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->setFixedSize(1600,900);
    w->setWindowTitle("Bruinopoly");
    w->show();
    this->hide();
}
*/
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
