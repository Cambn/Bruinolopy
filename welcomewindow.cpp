#include "subwindow.h"


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
    subWindow *game_setup = new subWindow;
    game_setup->num_player = 2;
    game_setup->setFixedSize(1600,900);
    game_setup->setWindowTitle("Game Set Up");

    QFont labelfont("Times",20);

    QHBoxLayout *layout1 = new QHBoxLayout;
    QLabel *lb = new QLabel("Plese choose the number of players: ");
    lb->setFont(labelfont);
    QSpinBox *spinBox_num = new QSpinBox;
    spinBox_num->setRange(2,4);
    layout1->addWidget((lb));
    layout1->addWidget((spinBox_num));
    QObject::connect(spinBox_num, SIGNAL(valueChanged(int)), game_setup, SLOT(comfirm_num(int)));

    QHBoxLayout *layout2 = new QHBoxLayout;
    QLabel *lb2 = new QLabel("Plese choose the maximun number of money existed: ");
    lb2->setFont(labelfont);
    QComboBox *c1 = new QComboBox;
    c1->addItem("100000");
    c1->addItem("200000");
    c1->addItem("300000");
    layout2->addWidget((lb2));
    layout2->addWidget((c1));

    QHBoxLayout *layout3 = new QHBoxLayout;
    QLabel *lb3 = new QLabel("Plese choose the maximun number of house allowed: ");
    lb3->setFont(labelfont);
    QComboBox *c2 = new QComboBox;
    c2->addItem("40");
    c2->addItem("80");
    c2->addItem("120");
    layout3->addWidget((lb3));
    layout3->addWidget((c2));

    QVBoxLayout* layout= new QVBoxLayout;
    QPushButton *comfirm = new QPushButton("Comfirm");
    QHBoxLayout *layout4 = new QHBoxLayout;
    layout4->addWidget(comfirm);
    comfirm->setMaximumSize(QSize(200,50));
    QObject::connect(comfirm, SIGNAL(clicked()), game_setup, SLOT(GoSettingPage2()));
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->setSpacing(50);
    layout->setAlignment(Qt::AlignCenter);
    game_setup->setLayout(layout);
    game_setup->show();
    this->hide();

    QPixmap bkgnd(":/fig/setting_bkgd.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);
    game_setup->setPalette(p);
}


void WelcomeWindow::GoRulePage(){
    QWidget *a = new QWidget;
    a->setWindowTitle("Rule");
    a->setFixedSize(1200,900);
    QPixmap bkgnd(":/fig/rules_bkgd.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);
    a->setPalette(p);
    a->show();
}

void WelcomeWindow::GoRecordsPage(){
    QWidget *a = new QWidget;
    a->setWindowTitle("Records");
    a->show();
    a->setFixedSize(1200,900);
    QPixmap bkgnd(":/fig/records_bkgd.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);
    a->setPalette(p);
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

