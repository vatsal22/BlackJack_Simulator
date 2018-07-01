
#include <iostream>
#include <string>
using namespace std;

#include "card.h"
#include "deck.h"

class Player
{

    int numOfCards;
    Card cards[52];

  public:
    Player()
    {
        numOfCards = 0;
    }
    int getNumOfCards()
    {
        return numOfCards;
    }
    void resetCards()
    {
        numOfCards = 0;
    }
    void addCard(Card card)
    {
        cards[numOfCards] = card;
        numOfCards++;
    }
    int cardsValue()
    {
        int value = 0;
        int numOfAces = 0;
        for (int i = 0; i < numOfCards; i++)
        {
            if ((cards[i].getFace())[0] >= '2' && (cards[i].getFace())[0] <= '9' || cards[i].getFace() == "10")
            {
                value += std::stoi(cards[i].getFace());
            }
            else if (cards[i].getFace() == "A")
            {
                numOfAces++;
            }
            else
            {
                value += 10;
            }
        }
        if (numOfAces == 1)
        {
            if ((value + 11) > 21)
            {
                value++;
            }
            else
            {
                value += 11;
            }
        }
        else if (numOfAces > 1)
        {
            value += numOfAces - 1;
            if ((value + 11) > 21)
            {
                value++;
            }
            else
            {
                value += 11;
            }
        }
        return value;
    }
};

int bustThreshold(int threshold)
{
    Deck deck;
    Player p1;
    int numOfBusts = 0;
    for (int i = 0; i < 10000; i++)
    {
        p1.resetCards();
        do
        {
            if (deck.remainingInDeck() <= 0)
            {
                break;
            }
            p1.addCard(deck.dealOneCard());
        } while (p1.cardsValue() < threshold && p1.cardsValue() < 21);

        if (deck.remainingInDeck() <= 0)
        {
            deck.shuffle();
            p1.resetCards();
            i--;
            continue;
        }
        if (p1.cardsValue() > 21)
        {
            numOfBusts++;
        }
    }
    return numOfBusts;
}

void whenToStand()
{

    cout << "\n(threshold, bust fraction):" << endl;
    for (int i = 10; i <= 20; i++)
    {

        float numOfBusts = (float)bustThreshold(i);
        cout << "(" << i << ", " << (numOfBusts / 10000.0) << ")" << endl;
    }
}

int hiOrLowCard(Card deal) //return 1 if low card, -1 if high card, else 0
{
    if ((deal.getFace())[0] >= '2' && (deal.getFace())[0] <= '6')
    {
        return 1;
    }
    else if (deal.getFace() == "10" || deal.getFace() == "A" || deal.getFace() == "J" || deal.getFace() == "Q" || deal.getFace() == "K")
    {
        return -1;
    }
    return 0;
}

void hiLoSim()
{
    Deck deck;
    Player dealer;
    Player p1;
    int runningCount = 0;
    int threshold = 16;
    float numOfRightChoices = 0;
    for (int i = 0; i < 10000; i++)
    {
    BeginningOfLoop:

        int bet = 0; //0 means low bet, 1 mean high/medium bet

        if (runningCount >= 0)
        {
            bet = 1;
        }

        dealer.resetCards();
        p1.resetCards();

        if (deck.remainingInDeck() <= 0)
        {
            deck.shuffle();
            runningCount = 0;
            i--;
        }

        Card deal = deck.dealOneCard();
        runningCount += hiOrLowCard(deal);
        dealer.addCard(deal);

        for (int i = 0; i < 6; i++)
        { //simulate dealing 2 cards to each player besides p1
            if (deck.remainingInDeck() <= 0)
            {
                goto BeginningOfLoop;
            }

            deal = deck.dealOneCard();
            runningCount += hiOrLowCard(deal);
        }

        do
        {
            if (deck.remainingInDeck() <= 0)
            {
                goto BeginningOfLoop;
            }
            deal = deck.dealOneCard();
            runningCount += hiOrLowCard(deal);
            p1.addCard(deal);
        } while (p1.cardsValue() < threshold && p1.cardsValue() < 21);

        do
        {
            if (deck.remainingInDeck() <= 0)
            {
                goto BeginningOfLoop;
            }
            deal = deck.dealOneCard();
            runningCount += hiOrLowCard(deal);
            dealer.addCard(deal);
        } while (dealer.cardsValue() < 17 && dealer.cardsValue() < 21 && dealer.cardsValue() <= p1.cardsValue());

        if (p1.cardsValue() > 21)
        {
            if (bet == 0)
            { //busted but you bet low
                numOfRightChoices++;
            }
        }
        else if (p1.cardsValue() == 21)
        {
            if (bet == 1)
            { //BlackJack and you bet high
                numOfRightChoices++;
            }
        }
        else if (dealer.cardsValue() > 21)
        {
            if (bet == 1)
            { //Dealer busted and you bet high
                numOfRightChoices++;
            }
        }
        else if (p1.cardsValue() > dealer.cardsValue())
        {
            if (bet == 1)
            { //Got higher than dealer and you bet high
                numOfRightChoices++;
            }
        }
        else
        {
            numOfRightChoices += 0.5; //The player and dealer tied, add 0.5 regardless of bet
        }
    }
    cout << "\n(good bets fraction): \n"
         << ((float)numOfRightChoices / 10000.0) << endl;
}

int main()
{
    cout << "\nBlackJack Simulator:" << endl;
    srand(time(0));

    whenToStand();
    hiLoSim();

    return 0;
}
