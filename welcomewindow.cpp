#include "welcomewindow.h"


WelcomeWindow::WelcomeWindow(QWidget *parent) : QWidget(parent)
{
    //game title setting
    setFixedSize(1600,900);
    QLabel* title=new QLabel("BRUINOPOLY",this);
    setWindowTitle("Bruinopoly");
    QFont labelfont("Castellar",35,QFont::Bold);
    title->setFont(labelfont);

    //layout setting
    QVBoxLayout* alllayout=new QVBoxLayout;
    QHBoxLayout* buttonlayout=new QHBoxLayout;
    alllayout->addWidget(title);
    title->setAlignment(Qt::AlignHCenter);
    buttonlayout->setSpacing(100);
    buttonlayout->setAlignment(Qt::AlignHCenter);
    alllayout->addLayout(buttonlayout);
    setLayout(alllayout);

    //buttons setting
    QPushButton* b1=new QPushButton("Rules",this);
    QPushButton* b2=new QPushButton("New Game",this);
    QPushButton* b3=new QPushButton("Records",this);
    GeneralBtnSetup(b1,buttonlayout);
    GeneralBtnSetup(b2,buttonlayout);
    GeneralBtnSetup(b3,buttonlayout);
    QObject::connect(b1, SIGNAL(clicked()), this, SLOT(GoRulePage()));
    QObject::connect(b2, SIGNAL(clicked()), this, SLOT(GoSettingPage()));
    QObject::connect(b3, SIGNAL(clicked()), this, SLOT(GoRecordsPage()));

    sound=new QPushButton(this);
    const QSize soundbutton_size= QSize(50,50);
    sound->setMinimumSize(soundbutton_size);
    sound->move(50,25);
    QPixmap soundpic(":/fig/sound");
    soundpic.scaled(size(),Qt::IgnoreAspectRatio);
    QIcon SoundIcon(soundpic);
    sound->setIcon(SoundIcon);

    //bgm setting
    QObject::connect(sound, SIGNAL(clicked()),this, SLOT(soundclick()));
    music=new QMediaPlayer;
    music->setMedia(QUrl("qrc:/sound/welcomemusic.mp3"));
    music->play();
}

//a slot changing bgm to muted or not
void WelcomeWindow::soundclick(){

    if (!music->isMuted()){
        music->setMuted(1);
        QPixmap mutepic(":/fig/mute");
        mutepic.scaled(size(),Qt::IgnoreAspectRatio);
        QIcon MuteIcon(mutepic);
        sound->setIcon(MuteIcon);}
    else
    {
        music->setMuted(0);
        QPixmap soundpic(":/fig/sound");
        soundpic.scaled(size(),Qt::IgnoreAspectRatio);
        QIcon SoundIcon(soundpic);
        sound->setIcon(SoundIcon);
    }
}

//set the buttons at the bottom
void WelcomeWindow::GeneralBtnSetup(QPushButton* &b, QHBoxLayout* &btnlayout){
    QFont buttonfont("Curlz MT",15);
    const QSize b_size = QSize(200, 60);
    b->setMinimumSize(b_size);
    b->setFont(buttonfont);
    btnlayout->addWidget(b);
    QPixmap pawpic(":/fig/paw");
    pawpic.scaled(size(),Qt::IgnoreAspectRatio);
    QIcon PawIcon(pawpic);
    b->setIcon(PawIcon);
}


void WelcomeWindow::GoSettingPage(){
    //stop the music
    if (!music->isMuted())
        music->setMuted(1);
    game_setup = new subWindow();
    game_setup->num_player = 2;
    game_setup->setFixedSize(1600,900);
    game_setup->setWindowTitle("Game Set Up");
    QFont labelfont("Times",20);
    QHBoxLayout *layout1 = new QHBoxLayout;
    QLabel *lb = new QLabel("Please choose the number of players: ",this);
    lb->setFont(labelfont);
    QSpinBox *spinBox_num = new QSpinBox();
    spinBox_num->setRange(2,4);
    layout1->addWidget((lb));
    layout1->addWidget((spinBox_num));
    QObject::connect(spinBox_num, SIGNAL(valueChanged(int)), game_setup, SLOT(comfirm_num(int)));

    QHBoxLayout *layout5 = new QHBoxLayout;
    QLabel *lb5 = new QLabel("Please choose initial amount of money each player has: ");
    lb5->setFont(labelfont);
    QComboBox *c4 = new QComboBox;
    game_setup->firstCBlist.append(c4);
    c4->addItem("1500");
    c4->addItem("2000");
    c4->addItem("4000");
    layout5->addWidget((lb5));
    layout5->addWidget((c4));

    QHBoxLayout *layout2 = new QHBoxLayout;
    QLabel *lb2 = new QLabel("Please choose the maximun number of money existed: ");
    lb2->setFont(labelfont);
    QComboBox *c1 = new QComboBox;
    game_setup->firstCBlist.append(c1);
    c1->addItem("10000");
    c1->addItem("20000");
    c1->addItem("30000");
    layout2->addWidget((lb2));
    layout2->addWidget((c1));

    QHBoxLayout *layout3 = new QHBoxLayout;
    QLabel *lb3 = new QLabel("Please choose the maximun number of house allowed: ");
    lb3->setFont(labelfont);
    QComboBox *c2 = new QComboBox;
    game_setup->firstCBlist.append(c2);
    c2->addItem("10");
    c2->addItem("20");
    c2->addItem("40");
    layout3->addWidget((lb3));
    layout3->addWidget((c2));

    QHBoxLayout *layout4 = new QHBoxLayout;
    QLabel *lb4 = new QLabel("Please choose the maximun number of hotel allowed: ");
    lb4->setFont(labelfont);
    QComboBox *c3 = new QComboBox;
    game_setup->firstCBlist.append(c3);
    c3->addItem("2");
    c3->addItem("4");
    c3->addItem("8");
    layout4->addWidget((lb4));
    layout4->addWidget((c3));

    QVBoxLayout* layout= new QVBoxLayout;
    QPushButton *comfirm = new QPushButton("Comfirm");
    QHBoxLayout *layout6 = new QHBoxLayout;
    layout6->addWidget(comfirm);
    comfirm->setMaximumSize(QSize(200,50));
    QObject::connect(comfirm, SIGNAL(clicked()), game_setup, SLOT(GoSettingPage2()));
    layout->addLayout(layout1);
    layout->addLayout(layout5);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->addLayout(layout6);
    layout->setSpacing(50);
    layout->setAlignment(Qt::AlignCenter);
    game_setup->setLayout(layout);
    this->hide();
    game_setup->show();

    QPixmap bkgnd(":/fig/setting_bkgd.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);
    game_setup->setPalette(p);
}


void WelcomeWindow::GoRulePage(){
    rule = new QWidget;
    rule->setWindowTitle("Rule");
    rule->setFixedSize(1200,900);
    QPixmap bkgnd(":/fig/rules_bkgd.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    rule->setPalette(p);
    rule->show();
}

void WelcomeWindow::GoRecordsPage(){
    record = new QWidget;
    record->setWindowTitle("Records");
    record->show();
    record->setFixedSize(1200,900);
    QPixmap bkgnd(":/fig/records_bkgd.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);
    record->setPalette(p);
}


//reset the background size each time the window size changed
void WelcomeWindow::resizeEvent(QResizeEvent *)
{
QPixmap bkgnd(":/fig/uclaCover.jpg");
bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
QPalette p = palette(); //copy current, not create new
p.setBrush(QPalette::Background, bkgnd);
setPalette(p);
}

