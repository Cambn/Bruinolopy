#include "property.h"
#include "player.h"
#include "bank.h"
#include "QLandingWindows.h"

#include <QGridLayout>
#include <QPainter>
#include <QRect>
#include <sstream>

using std::string; using std::stringstream;

Property::Property(const string& formattedLine) : Tile(std::stoi(formattedLine.substr(formattedLine.find('\t'),2))),
                                                  owner(nullptr), houseCount(0)                                     {
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


Player* Property::propOwner() const {return owner;}

QWidget*  Property::generateView() {
    return (new View(*this));
}


void Property::landingEvent(Player* currPlayer) {
    if(!propOwner()) { //property is unowned
        QLandingOptions* propWindow = new QLandingOptions
                                    (generateView(),
                                    "Unowned!\n Purchase this property?",
                                    "Yes",
                                    "No");

        QObject::connect(propWindow->getLeft(),&QPushButton::clicked,     //connects Yes button to player buy fxn
                         currPlayer->interactor, &Player::QInteractor::buyBankProp);

        QObject::connect(propWindow->getRight(), &QPushButton::clicked,   //connect No button to closing pop up window
                         propWindow, &QWidget::close);

	
	}
	
}


void Property::transfer(Player* newOwner) {
    owner = newOwner;
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

//    image= QPixmap(":/Properties/Assets/Properties/BlueProperty.png");


    std::string fileName= ":/Properties/Assets/Properties/"+prop.color+"Property.png";
    QString qfileName(QString::fromStdString(fileName));
    image = QPixmap(qfileName);
    setMinimumSize(320,384);
}

void Property::View::paintEvent(QPaintEvent *){

    QPainter p(this);


    p.drawPixmap(QRect(0,0,320,384),image,QRect(0,0,160,192));
}

