
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
    int threshold = 17;
    float numOfRightChoices = 0;
    int numOfGames = 0;
    for (int i = 0; i < 10000; i++)
    {
    BeginningOfLoop:

        int bet = 0; //0 means low bet, 1 means high/medium bet

        if (runningCount >= 0)
        {
            bet = 1; //bet high
        }

        dealer.resetCards(); //reset hand
        p1.resetCards();

        if (deck.remainingInDeck() <= 0)
        {
            deck.shuffle(); //If deck is empty, reshuffle, reset runningCount
            runningCount = 0;
        }

        Card deal = deck.dealOneCard();
        runningCount += hiOrLowCard(deal); //Adjust runningCount
        dealer.addCard(deal);              //Dealer gets face up card

        for (int w = 0; w < 6; w++)
        {                                    //simulate dealing 2 cards to three players
            if (deck.remainingInDeck() <= 0) //If deck is empty, restart loop
            {

                goto BeginningOfLoop;
            }

            deal = deck.dealOneCard();
            runningCount += hiOrLowCard(deal); //Adjust runningCount for each dealt card
        }

        do
        {                                    //Simulate player hitting or eventually standing
            if (deck.remainingInDeck() <= 0) //Deck is empty
            {

                goto BeginningOfLoop;
            }
            deal = deck.dealOneCard();
            runningCount += hiOrLowCard(deal); //Adjust count and deal to player
            p1.addCard(deal);
        } while (p1.cardsValue() < threshold && p1.cardsValue() < 21); //When player busts or meets threshold, stand

        do
        {                                    //Simulate dealer hitting/standing
            if (deck.remainingInDeck() <= 0) //Deck is empty
            {

                goto BeginningOfLoop;
            }
            deal = deck.dealOneCard();
            runningCount += hiOrLowCard(deal); //Adjust count and deal to dealer
            dealer.addCard(deal);
        } while (dealer.cardsValue() < 17 && dealer.cardsValue() < 21 && dealer.cardsValue() <= p1.cardsValue()); //Deal until dealer meets 17, beats player, or busts
        numOfGames++;
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
        else if (p1.cardsValue() == dealer.cardsValue())
        {
            numOfRightChoices++; //The player and dealer tied, add 1 regardless of bet
        }
        else if (p1.cardsValue() < dealer.cardsValue())
        {
            if (bet == 0)
            { //Got lower than dealer but bet low
                numOfRightChoices++;
            }
        }
    }

    cout << "\n(good bets fraction with threshold=" << threshold << "): \n"
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
