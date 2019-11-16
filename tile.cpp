#include "tile.h"
#include "QLandingWindows.h"
#include "player.h"
#include <string>


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
//
//OwnableTile Stuff
//

ownableTile::ownableTile(int _tileNum, Board* _board):
    Tile(_tileNum, _board), owner(nullptr)
    {}

void ownableTile::landingEvent(Player *currPlayer){
    if(!propOwner()) { //property is unowned
        QLandingOptions* propWindow = new QLandingOptions
                                    (generateView(),
                                    "Unowned!\n Purchase this property?",
                                    "Yes",
                                    "No");

        QObject::connect(propWindow->getLeft(),&QPushButton::clicked,     //connects Yes button to player buy fxn
                         currPlayer->interactor, &Player::QInteractor::buyBankProp);

    }
    else if (propOwner() == currPlayer) {//player lands on their own property
    //do nothing
    }

    else { //someone else owns the property so pay them rent
        std::string popupMessage ("Rent due:" +std::to_string(currentRent())+"!"); //generate message that asks for proper rent.

        QLandNoOptions* rentWindow = new QLandNoOptions (
                                        generateView(), QString::fromStdString(popupMessage));
        this->owner->take(currPlayer, this->currentRent()); //owner of tile takes appropriate rent from person who landed on it.

    }
}

Player* ownableTile::propOwner() const {return owner;}



void ownableTile::transfer(Player* newOwner){owner = newOwner;}

