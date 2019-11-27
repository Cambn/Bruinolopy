#include "property.h"
#include "player.h"
#include "bank.h"
#include "QLandingWindows.h"

#include <QGridLayout>
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

//Property::View class stuff

Property::View::View(const Property& prop)  {


    //std::string fileName= "Assets\\Properties\\Prop"+std::to_string(prop.tileNumber)+".png";
    //QString qfileName(QString::fromStdString(fileName));
    //image = QPixmap(qfileName);


// :/properties/blueProperty.png
    std::string fileName= ":/properties/"+prop.color+"Property.png";
    QString qfileName(QString::fromStdString(fileName));
    image = QPixmap(qfileName);
    setMinimumSize(320,384);
}

void Property::View::paintEvent(QPaintEvent *){

    QPainter p(this);


    p.drawPixmap(QRect(0,0,320,384),image,QRect(0,0,160,192));
}

//
// Utility tile stuff
//

Utility::Utility(const std::string& formattedLine, Board* _board, MainWindow* game):
    ownableTile(std::stoi(formattedLine.substr(formattedLine.find('\t'),2)),_board,game)
{}


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
    return new QWidget();
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
