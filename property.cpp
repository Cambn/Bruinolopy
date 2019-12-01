#include "property.h"
#include "player.h"
#include "bank.h"
#include "QLandingWindows.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QRect>
#include <sstream>

class MainWindow;

using std::string; using std::stringstream;

Property::Property(const string& formattedLine, Board* _board, MainWindow* _game) : ownableTile(std::stoi(formattedLine.substr(formattedLine.find('\t'),2)),_board,_game), houseCount(0)                                     {
    stringstream buffer(formattedLine);
    string temp = "";
    stringstream vals;
    getline(buffer, temp, '\t'); getline(buffer,temp, '\t'); //buffer eats "prop" then "1"

    getline(buffer,temp,'\t');
    color = temp;
    getline(buffer,temp,'\t');
    name = temp;
    getline(buffer,temp,'\t');
    cost = std::stoi(temp);
    getline(buffer,temp,'\t');
    houseCost= std::stoi(temp);
    getline(buffer,temp,'\t');
    rents[0]=std::stoi(temp);
    getline(buffer,temp,'\t');
    rents[1]=std::stoi(temp);
    getline(buffer,temp,'\t');
    rents[2]=std::stoi(temp);
    getline(buffer,temp,'\t');
    rents[3]=std::stoi(temp);
    getline(buffer,temp,'\t');
    rents[4]=std::stoi(temp);
    getline(buffer,temp,'\t');
    rents[5]=std::stoi(temp);

}



QWidget*  Property::generateView() const{
    return (new View(*this));
}



bool Property::buildHouse(Bank* bank) {
    if (houseCount<4){ //trying to build a house
        if (bank->housesLeft() && (owner->playerMoney >=houseCost)){//bank has houses left to build and owner has enough money
            bank->take(*owner, houseCost);//charge player for house
            ++houseCount;
            --bank->housesRemaining;
            return true;
        }
        else {return false;} //no houses left do nothing
        //TODO: figure out how to output error message

    }
    else if (houseCount==4 ) {//building a hotel
        if(bank->hotelsLeft() && (owner->playerMoney >=houseCost)) {//hotels left and owner has enough money
        bank->take(*owner,houseCost);//charge owner for a hotel
        ++houseCount;
        --bank->hotelsRemaining;
        return true;
        }
        else {return false;}
        //TODO:figure out how to output error messsage

    }
    else { return false;}
    //TODO: figure out how to output error message

}

int Property::currentRent() const {
    if(propOwner()) {//if property is owned
        return rents[houseCount]; //return rent corresponding to current number of houses
    }
    return 0; //if unowned, no rent is due.
}
//
//
//Property::View class stuff
//
//
Property::View::View(const Property& prop) : mainLayout(new QVBoxLayout(this))  {

// :/properties/blueProperty.png
    std::string fileName= ":/images/properties/"+prop.color+"Property.png";
    QString qfileName(QString::fromStdString(fileName));
    image = QPixmap(qfileName);
    setFixedSize(320,384);
    //make label for name
    string temp = prop.name;
    QFont font("Kabel Heavy",29);
    QLabel* _name = new QLabel(QString::fromStdString(temp),this);
    _name->setFont(font);
    mainLayout->addWidget(_name,1,Qt::AlignHCenter);

    //make label for cost
    temp = "Cost: $"+ std::to_string(prop.cost)+"\n";
    font = QFont("Kabel Heavy",20);
    QLabel* line2 = new QLabel(QString::fromStdString(temp),this);
    line2->setFont(font);
    mainLayout->addWidget(line2, 4, Qt::AlignHCenter );
    //make label for the rest
    temp = "\t      Rent: $"+std::to_string(prop.rents[0])+ "\n" +
           "With 1 House\t\t$"+std::to_string(prop.rents[1])+".\n" +
           "With 2 Houses\t\t$"+std::to_string(prop.rents[2])+".\n" +
           "With 3 Houses\t\t$"+std::to_string(prop.rents[3])+".\n" +
           "With 4 Houses\t\t$"+std::to_string(prop.rents[4])+".\n" +
           "           With HOTEL     $"+std::to_string(prop.rents[5])+".\n";

    QLabel* rentsBlock = new QLabel(QString::fromStdString(temp),this);
    font = QFont("Kabel Heavy", 15);
    rentsBlock->setFont(font);
    mainLayout->addWidget(rentsBlock,1,Qt::AlignHCenter);

    temp =  "      Houses cost $"+std::to_string(prop.houseCost)+". each\n"+
            "Hotels cost $"+std::to_string(prop.houseCost)+". plus 4 houses\n" ;
    QLabel* bottomBlock = new QLabel(QString::fromStdString(temp),this);
    bottomBlock->setFont(font);
    mainLayout->addWidget(bottomBlock,1,Qt::AlignHCenter);


}

void Property::View::paintEvent(QPaintEvent *){

    QPainter p(this);


    p.drawPixmap(QRect(0,0,320,384),image,QRect(0,0,160,192));

}


/**
*
* Railroad Stuff
*
*/
Railroad::Railroad(int _tileNum, std::string _name, Board* _board, MainWindow* _game):
    ownableTile(_tileNum ,_board, _game),
    cost(200), name(std::move(_name))
{}

int Railroad::checkOwnerRailroads(const Player& player) const{
    int railroadCount = 0;
    for ( auto prop : player.playerProperties) {//go through player properties
        if (dynamic_cast<Railroad*>(prop)){//see which ones are railroads
            ++railroadCount;                //count them
        }
    }
    return railroadCount; //return number of railroads they own.
}

int Railroad::currentRent() const {
    return rents[checkOwnerRailroads(*owner)];
}

QWidget* Railroad::generateView() const {
    return new View(*this);
}


Railroad::View::View(const Railroad& rr) : mainLayout(new QVBoxLayout(this)) {
    QString qfileName(":/images/properties/railroadProperty.png");
    image = QPixmap(qfileName);

    setFixedSize(320,384);

    mainLayout->addSpacerItem(new QSpacerItem(319,130,QSizePolicy::Fixed,QSizePolicy::Fixed)); //block out the icon display portion of the card

    string temp(rr.getName()+" Bus Line");
    QFont font("Kabel Heavy",20);
    QLabel* _name = new QLabel(QString::fromStdString(temp),this);
    _name->setStyleSheet("font-weight: bold ; color: black");
    _name->setFont(font);
    mainLayout->addWidget(_name,1,Qt::AlignHCenter | Qt::AlignTop);

    temp = "Cost: $"  +std::to_string(rr.cost) +"\n\n";
    QLabel* _cost = new QLabel(QString::fromStdString(temp));
    font = QFont("Kabel Heavy",15);
    _cost->setFont(font);
    mainLayout->addWidget(_cost,1,Qt::AlignHCenter | Qt::AlignTop);


    temp = "Rent\t\t\t$"+std::to_string(rr.rents[0]) + "\n\n" +
            "If both R.R.'s are owned \t$"+std::to_string(rr.rents[1]);
    font = QFont("Kabel Heavy",15);
    QLabel* block = new QLabel(QString::fromStdString(temp),this);
    block->setFont(font);
    mainLayout->addWidget(block,1,Qt::AlignHCenter | Qt::AlignTop);

}


void Railroad::View::paintEvent(QPaintEvent*) {
    QPainter p(this);


    p.drawPixmap(QRect(0,0,320,384),image,QRect(0,0,160,192));
}
//
//old code
//

//void Property::landingEvent(Player* currPlayer) {
//    if(!propOwner()) { //property is unowned
//        QLandingOptions* propWindow = new QLandingOptions
//                                    (generateView(),
//                                    "Unowned!\n Purchase this property?",
//                                    "Yes",
//                                    "No");

//        QObject::connect(propWindow->getLeft(),&QPushButton::clicked,     //connects Yes button to player buy fxn
//                         currPlayer->interactor, &Player::QInteractor::buyBankProp);

//	}
//  else if (propOwner() == currPlayer) {

//    }

//}

//
// Utility tile stuff
//

//Utility::Utility(const std::string& formattedLine, Board* _board, MainWindow* game):
//    ownableTile(std::stoi(formattedLine.substr(formattedLine.find('\t'),2)),_board,game)
//{}

