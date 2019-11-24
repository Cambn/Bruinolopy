#include "gameManager.h"
#include "board.h"
#include "bank.h"
#include "subwindow.h"


#include <QObject>
#include <fstream>
#include <stdexcept>

GameManager::GameManager(QObject *parent) : QObject(parent) {
    board = new Board(this);
    bank = new Bank;



    players.push_back(new Player("jeff", "panda",0, bank, board));
    players.push_back(new Player("BIG MIKE", "panda",1, bank, board));
}

GameManager::GameManager (const subWindow& settingsInfo, QObject* parent):
QObject(parent), players(settingsInfo.num_player)
{
    try {
        board = new Board(this); //build board
        bank =  new Bank();      //build bank
        for(size_t i = 0; i < players.size(); ++i) { //construct player at proper index in player vector
            players.at(i)= new Player(settingsInfo.names[i], settingsInfo.charactors[i], i ,bank, board);
        }
    }

    catch(...){

    }
}


int GameManager::findPlayerNum(const Player &query) const {
    for (size_t i=0; i<players.size(); ++i) {
        if (players.at(i) == &query){
            return static_cast<int>(i+1); //return position we found query at
        }

    }
    throw (std::logic_error("Invalid Player passed to findPlayerNum"));

}
