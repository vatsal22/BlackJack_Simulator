#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

#include "card.h"
#include "deck.h"

Deck::Deck()
{

    for (int i = 0; i < 52; i++)
    {
        _cards[i] = Card(i);
    }
    shuffle();
    _nextCardIndex = 0;
}

Card Deck::dealOneCard()
{
    if (_nextCardIndex >= 52)
    {
    std:
        cerr << "Error: No more cards in deck! Exiting." << endl;
        exit(1);
    }
    return _cards[_nextCardIndex++];
}

int Deck::remainingInDeck()
{
    return 52 - _nextCardIndex;
}

void Deck::shuffle()
{
    for (int i = 0; i < (52 - 1); i++)
    {
        int randnum = i + (rand() % (52 - i));
        swap(_cards[i], _cards[randnum]);
    }
    _nextCardIndex = 0;
}
