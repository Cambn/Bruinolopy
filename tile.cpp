#include "tile.h"
#include "QLandingWindows.h"
#include "player.h"
#include "mainwindow.h"


#include <string>
#include <QWidget>
#include <QPainter>
//
//Tile stuff.
//
bool Tile::operator>(const Tile &oth) const {
    return this->tileNumber > oth.tileNumber;
}

bool Tile::operator< ( const Tile& oth) const{
    return this->tileNumber< oth.tileNumber;
}
bool Tile::operator==(const Tile& oth) const{
    return this->tileNumber == oth.tileNumber;
}
bool Tile::operator!=(const Tile& oth) const {
    return !(*this == oth);
}

QPixmap* Tile::generateBoardView() const {
    std::string filename= ":/tile/tile"+(std::to_string(tileNumber))+".png";
    QString qfileName(QString::fromStdString(std::move(filename)));
   return new QPixmap(qfileName);
}
//
//
//OwnableTile Stuff
//
//

ownableTile::ownableTile(int _tileNum, Board* _board, MainWindow* _game):
    Tile(_tileNum, _board, _game), owner(nullptr)
    {}

void ownableTile::landingEvent( Player& currPlayer){
    if(!propOwner()) { //property is unowned
        QLandingOptions* propWindow = new QLandingOptions
                                    (generateView(),
                                    "Unowned!\n Purchase this property?",
                                     game,
                                    "Yes",  "No");

        QObject::connect(propWindow->getLeft(),&QPushButton::clicked,     //connects Yes button to player buy fxn
                        &currPlayer, &Player::buyBankProp);

    }
    else if (propOwner() == &currPlayer) {//player lands on their own property
    //do nothing
    }

    else { //someone else owns the property so pay them rent
        std::string popupMessage ("Rent due:" +std::to_string(currentRent())+"!"); //generate message that asks for proper rent.

        QLandNoOptions* rentWindow = new QLandNoOptions ( generateView(), 
                                                          QString::fromStdString(popupMessage),
                                                          game);
        this->owner->take(&currPlayer, this->currentRent()); //owner of tile takes appropriate rent from person who landed on it.

    }
}

Player* ownableTile::propOwner() const {return owner;}



void ownableTile::transfer(Player* newOwner){owner = newOwner;}


