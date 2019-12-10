
#include "subwindow.h"
#include "gameboard.h"
#include <QLineEdit>
#include <algorithm>
#include <iostream>
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
    window2->layout_forUpdate.resize(num_player);
    for(size_t n = 0; n < window2->layout_forUpdate.size(); ++n){
       window2->layout_forUpdate[n] = new QHBoxLayout();
    }
    window2->layout_forUpdate_icon.resize(num_player);
    for(size_t n = 0; n < window2->layout_forUpdate_icon.size(); ++n){
       window2->layout_forUpdate_icon[n] = new QHBoxLayout();
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
        //txt->setText("Please give a nickname");

        window2->LElist.append(txt);
        window2->layout_forUpdate[_numberofplayer]->addWidget(txt);
        //window2->layout_forUpdate[_numberofplayer]->addWidget(window2->warningLabel_name);

        //ComboBox
        QComboBox *combobox = new QComboBox(this);
        combobox->setMaximumSize(200,50);
        combobox->addItem(QIcon(":/fig/panda.png"),"Panda");
        combobox->addItem(QIcon(":/fig/brownbear.png"),"Brown Bear");
        combobox->addItem(QIcon(":/fig/polarbear.png"),"Polar Bear");
        combobox->addItem(QIcon(":/fig/greybear.png"),"Grey Bear");
        window2->CBlist.append(combobox);
        window2->layout_forUpdate_icon[_numberofplayer]->addWidget(combobox);
        //window2->layout_forUpdate_icon[_numberofplayer]->addWidget(warningLabel_name);

        //font
        QFont labelfont("Times",15);
        lb2->setFont(labelfont);
        txt->setFont(labelfont);
        combobox->setFont(labelfont);

        //set layout
        QVBoxLayout* layout2_page2 = new QVBoxLayout();
        layout2_page2->addWidget(lb2);
        layout2_page2->addLayout(window2->layout_forUpdate[_numberofplayer]);
        layout2_page2->addLayout(window2->layout_forUpdate_icon[_numberofplayer]);
        layout2_page2->setSpacing(10);
        layout_page2->addLayout(layout2_page2);
    }
    QPushButton* finish = new QPushButton("Finish Setting",this);
    finish->setFixedSize(160,70);
    layout_page2->addWidget(finish);
    layout_page2->setAlignment(Qt::AlignCenter);
    layout_page2->setSpacing(50);

    QObject::connect(finish,SIGNAL(clicked()),window2,SLOT(checkValidation()));
    QObject::connect(window2,SIGNAL(succeed()),window2,SLOT(GoGameboard()));
    window2->setLayout(layout_page2);
    window2->show();

}

bool subWindow::checking_Nickname(){
    QString toCheck;
    for(int _index = 0; _index < this->LElist.length()-1; ++_index){
        toCheck = this->LElist[_index]->text();
        for(int _index2 = _index +1; _index2 <LElist.length();++_index2){
            if(toCheck==this->LElist[_index2]->text()){return true;}
        }
    }
    return false;
}
bool subWindow::checking_Icon(){
    int toCheck;
    for(int _index = 0; _index < this->CBlist.length()-1; ++_index){
        toCheck = this->CBlist[_index]->currentIndex();
        for(int _index2 = _index +1; _index2 <CBlist.length();++_index2){
            if(toCheck==this->CBlist[_index2]->currentIndex()){return true;}
        }
    }
    return false;
}
bool subWindow::checking_inputEmpty(){
    for (int _numberofplayer = 0 ; _numberofplayer < this->LElist.length() ; ++_numberofplayer){
        if(LElist[_numberofplayer]->text().isEmpty()){
            return true;
        }
    }
    return false;
}
void subWindow::checkValidation(){
    //std::cout<<"checking validation"<< std::endl;
        if(checking_inputEmpty()){
            warningLabel_name->setText("Error: Nickname cannot be empty. ");
            warningLabel_name->setStyleSheet("color:red;");
            layout_forUpdate[0]->addWidget(warningLabel_name);
            repaint();
            //std::cout<<"nickname empty"<<std::endl;
            //std::cout << warningLabel_name->text().toStdString() << std::endl;
            //std::cout << "icons same" << std::endl;
        }
        if(checking_Icon()){
            warningLabel_icon->setText("Error: icon cannot be the same. ");
            warningLabel_icon->setStyleSheet("color:red;");
            layout_forUpdate_icon[0]->addWidget(warningLabel_icon);
            //std::cout << "icons same" << std::endl;

        }
        if(checking_Nickname()){
            warningLabel_name->setText("Error: Nickname cannot be the same. ");
            warningLabel_name->setStyleSheet("color:red;");
            layout_forUpdate[0]->addWidget(warningLabel_name);
            //std::cout << "nicknames same" << std::endl;
        }
        if(!checking_inputEmpty() && !checking_Icon() && !checking_Icon()){
            emit succeed();
        }
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
/*
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
}*/

