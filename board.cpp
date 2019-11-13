#include "board.h"
#include "property.h"

#include <string>
#include <sstream>
#include <fstream>

using std::string;

Tile* Board::getTile(int boardPos)  {
    return tiles.at(boardPos);
}

Board::Board() : tiles(40,nullptr) {
//    std::fstream tileBuilder;
//    tileBuilder.open(":/txts/tileBuilder.txt");//open appropriate txt file
//    bool check = tileBuilder.is_open();

//    if(check){ //file successfully open

//        std::string currLine= "";
//        std::getline(tileBuilder, currLine); //eat the first line of file that displays formatting and is garbage data

//         while(!(tileBuilder.eof())){        //until end of file
//         std::getline(tileBuilder,currLine); //put line into string
//         std::stringstream buffer(currLine); //create ss from string
//         std::string temp = "";
//         buffer>>temp;
//           if (temp == "prop") {//want to construct property
//               Property* tempProp = new Property(currLine);
//               tiles.at(tempProp->tileNumber) = tempProp;


//           }

//        }

//    }
//    else {throw 10;}

    string first("prop	1	purple	prop0	60	50	2	10	30	90	160	250");
    string sec("prop	3	purple	prop1	60	50	4	20	60	180	320	450");
    string third("prop	6	lightBlue	prop2	100	50	6	30	90	270	400	550");
    string four("prop	8	lightBlue	prop3	100	50	6	30	90	270	400	550");
    string five("prop	9	lightBlue	prop4	120	50	8	40	100	300	450	600");
    string six("prop	11	magenta	prop5	140	100	10	50	150	450	625	750");
    string sev("prop	13	magenta	prop6	140	100	10	50	150	450	625	750");
    string eight("prop	14	magenta	prop7	160	100	12	60	180	500	700	900");
    string nine("prop	16	orange	prop8	180	100	14	70	200	550	700	900");
    string ten("prop	18	orange	prop9	180	100	14	70	200	550	700	950");
    string eleven("prop	19	orange	prop10	200	100	16	80	220	600	900	1000");
    string twelve("prop	21	red	prop11	220	150	18	90	250	700	875	1050");
    tiles.at(1)= new Property(first);
    tiles.at(3)= new Property (sec);
    tiles.at(6)= new Property(third);
    tiles.at(8)= new Property(four);
    tiles.at(9)= new Property(five);
    tiles.at(11)=new Property(six);
    tiles.at(13)=new Property(sev);
    tiles.at(14)= new Property(eight);
    tiles.at(16)= new Property(nine);
    tiles.at(18)=new Property(ten);
    tiles.at(19)=new Property(eleven);
    tiles.at(21)= new Property(twelve);

}
