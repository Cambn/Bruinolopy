#ifndef _PROPERTY_
#define  _PROPERTY_

#include "tile.h"

#include <string>
#include <QWidget>
#include <QPainter>

class Bank;
class Player;


/**
represents normal property tiles
*/
class Property : public ownableTile{
public:

    friend Player;
    class View;

    /**
    for use for building a property from a line of "tileBuilder.txt"
    @param formattedLine properly formatted line from tileBuilder.txt
    */
    Property(const std::string& formattedLine, Board* _board);


    Property(const Property& oth) = default;


	/**
    generates a QWidget with the approperiate property tile painted onto it
	@return pointer to viewing window to allow for manipulation. 
	*/
    virtual QWidget* generateView () override;

    /**
    Implements landing event w/ prompt to
    pay owner if property is owned
    purchase property if desired if unowned
    @param currPlayer player whose turn it is.
    */
    //virtual void landingEvent(Player* currPlayer) override;
	

	/**
	adds a house/hotel as appropriate if there are any remaining in the bank
	and deducts the appropriate amount from their moneyRemaining. 
	@param bank of this game. 
	@return true if house is successfuly built.
	*/
	
    bool buildHouse(Bank* bank);
	/**
	returns rent amount taking into account current number of houses
	@return 0 if unowned, otherwise the appropriate rent.
	*/
    int currentRent() const override;


private:
	std::string color;
	std::string name;
	
	//0 houses represents no houses, 5 represents a hotel
    int houseCount;
	//costs
	int cost;
	int houseCost;
	//rent prices with rent[0] being base rent and rent [5] being rent w/ hotel
	int rents[6];


};
/**
A minimal class to allow Property to be displayed. Upon being created with Property::generateView(),
the View instance will create a pixmap from the appropriate image for the calling property.

*/
class Property::View : public QWidget {
   Q_OBJECT
public:
    View(const Property& prop);

    //160x192 -> 320x384
    void paintEvent(QPaintEvent* ) override;
private:
    QPixmap image;

};

/**
utilities aka water company and electric company from regular game.
*/

class Utility : public ownableTile {
public:
Utility(const std::string& formattedLine, Board* _board);



/**
check if both utilities are owned by same person.
*/
bool checkSameOwner() const;

private:


};

#endif
