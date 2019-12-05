#ifndef PROPERTY
#define PROPERTY

#include "tile.h"

#include <string>
#include <QWidget>
#include <QPainter>

class QVBoxLayout;
class Bank;
class Player;

/**
represents normal property tiles
*/
class Property : public ownableTile{
public:

    friend Player;
    class View;
    Property(const std::string& formattedLine, Board* _board, MainWindow* game);
    Property(const Property& oth) = default;
    QWidget* generateView () const override;
    bool buildHouse(Bank* bank);
    int currentRent() const override;
    int getCost() const override {return cost;}
    std::string getName() const override{return name;}
    int checkOwnerRailroads(const Player& player) const override {}
private:
    std::string color;
    std::string name;
    int houseCount;
    int cost;
    int houseCost;
    int rents[6];


};
/**
A minimal class to allow Property to be displayed. Upon being created with Property::generateView(),
the View instance will create a pixmap from the appropriate image for the calling property.

*/
class Property::View : public QWidget {
   Q_OBJECT
public:
    View() = delete;
    View(const Property& prop);
    std::string getName() const {return name;}
    //160x192 -> 320x384
    void paintEvent(QPaintEvent* ) override;
private:
    QPixmap image;
    QVBoxLayout* mainLayout;
    std::string name;
};
/*
class TransportView : public Property::View{
public:
private:

};
*/


class Railroad : public ownableTile {
public:
    Railroad( int _tileNum, std::string name, Board* _board, MainWindow* game);


    int checkOwnerRailroads(const Player& player) const override;
    int currentRent() const override;


    int getCost() const override {return cost;}


    std::string getName() const {return name;}
    QWidget* generateView() const override;
    class View;
protected:
    int cost;
    std::string name;
    int rents[15]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; // each railroad has same rent values;
};




class Railroad::View : public QWidget {
Q_OBJECT
public:
View(const Railroad& rr);
void paintEvent(QPaintEvent *event) override;
private:
QPixmap image;
QVBoxLayout*  mainLayout;
};


#endif
