#include <string>
using namespace std;

#include "card.h"

const string Card::CARD_FACES[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
const string Card::CARD_SUITS[] = {"S", "H", "C", "D"};

Card::Card()
{
    _card = 0;
}

Card::Card(int card)
{
    _card = card;
}

string Card::getFace() const
{
    return CARD_FACES[_card % 13];
}

string Card::getSuit() const
{
    return CARD_SUITS[_card / 13];
}
