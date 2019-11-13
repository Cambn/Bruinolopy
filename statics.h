#ifndef _STATICS
#define _STATICS

/**
This class will be responsible for taking data from the Game Setting screen and passing to 
any other in-game object that need them.

*/
class Statics 
{
	
private: 
		static const int MONEY_MAX, HOUSES_MAX, HOTELS_MAX, STARTING_AMOUNT;
		
	
public: 
	Statics(
	int _money_max = 20580,
	int _houses_max= 32,
	int _hotels_max = 12,
	int _starting_amount =1500
	);
	
    static int getMONEY_MAX ();
    static int getHOUSES_MAX ();
    static int getHOTELS_MAX ();
    static int getSTARTING_AMOUNT ();
	
	friend class GameInitializer;
	
};

#endif
