#ifndef DECK_H
#define DECK_H

class Deck
{
  public:
    Deck();
    Card dealOneCard();
    int remainingInDeck();
    void shuffle();

  private:
    Card _cards[52];
    int _nextCardIndex;
};

#endif
