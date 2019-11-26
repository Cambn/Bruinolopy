#include "chancecard.h"
#include "board.h"

#include <algorithm>

void ChanceTile::landingEvent(Player &currPlayer) {

    int cardNum = qrand() % board->chanceCards.size();
    board -> chanceCards.at(cardNum) ->conduct_change(currPlayer);
}





