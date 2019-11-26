#include "bank.h"
#include "player.h"

Bank::Bank(const Statics& seed, const size_t numPlayers)  :
    bankMoney (seed.getMONEY_MAX()- (seed.getSTARTING_AMOUNT() * numPlayers)),
    housesRemaining(seed.getHOUSES_MAX()),
    hotelsRemaining(seed.getHOTELS_MAX())
    {}

bool Bank::pay(Player& payee, int amt) {
	if (bankMoney >= amt){//enough money left in bank
		bankMoney -= amt; //adjust bank money
		payee.playerMoney += amt; //adjust player money
		return true; //fxn was successful
	}
	return false;
}

void Bank::take(Player& payer, int amt) {
	if (payer.playerMoney >= amt) {//player has enough money
		bankMoney += amt; 
        payer.playerMoney -= amt;
	}
	else {
        bankMoney += payer.playerMoney;
        payer.playerMoney=0;
	}
}

bool Bank::housesLeft() const {
return (housesRemaining != 0);
}

bool Bank::hotelsLeft() const {
	return (hotelsRemaining != 0);
}

	
