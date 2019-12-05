#include "tile.h"
#include "qlandingwindow.h"
#include "player.h"
#include "mainwindow.h"
#include <string>
#include <QWidget>
#include <QPainter>


ownableTile::ownableTile(int _tileNum, Board* _board, MainWindow* _game):
    Tile(_tileNum, _board, _game), owner(nullptr)
    {}

void ownableTile::landingEvent( Player* currPlayer){
    if(!propOwner()) { //property is unowned
        QLandingOptions* propWindow = new QLandingOptions
                                    (generateView(),
                                    "Unowned!\n Purchase this property?",
                                     game,
                                    "Yes",  "No");

        QObject::connect(propWindow->getLeft(),&QPushButton::clicked,     //connects Yes button to player buy fxn
                         currPlayer, &Player::buyBankProp);

    }
    else if (propOwner() == currPlayer) {//player lands on their own tile
        if (dynamic_cast<Property*>(this)){
            QLandingOptions* buildHouse = new QLandingOptions(
                                                generateView(),
                                                "Build a house/hotel on this property?",
                                            currPlayer,"Yes", "No");
            QObject::connect(buildHouse->getLeft(),&QPushButton::clicked, currPlayer, &Player::buildHouse);
        }
        /*
        Cameron implmented. Check if the owner has two railroads, if yes, then give other options as in rather
        to transport to the other railroad
        */
        else if (dynamic_cast<Railroad*>(this)) {
            //EMIT ANOTHER SLOT IN THE PLAYER CLASS TO CALL THE TRANSPORTATION
            if(dynamic_cast<Railroad*>(this)->checkOwnerRailroads(currPlayer)==2){
                QLandingOptions* RailTransport = new QLandingOptions(
                                                       generateView(),
                                                       "So is that a yes or no?",
                                                       currPlayer,"Yes","No");
                QObject::connect(RailTransport->getLeft(),&QPushButton::clicked,currPlayer,&Player::transferPlayer_Railroad);
            }
        }
    }
    else
    { //someone else owns the property so pay them rent
        std::string popupMessage ("Rent due:" +std::to_string(currentRent())+"!"); //generate message that asks for proper rent.
        NoOptionWindow(game,QString::fromStdString(popupMessage));
        this->owner->take(currPlayer, this->currentRent()); //owner of tile takes appropriate rent from person who landed on it.

    }
}

Player* ownableTile::propOwner() const {return owner;}
void ownableTile::transfer(Player* newOwner){owner = newOwner;}


