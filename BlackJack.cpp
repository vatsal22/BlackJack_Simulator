
#include <iostream>
#include <string>
using namespace std;

#include "card.h"
#include "deck.h"

class Player{

    int numOfCards;
    Card cards[52];

public:
    Player() { 
        numOfCards = 0; 
    }
    int getNumOfCards(){
        return numOfCards;
    }
    void resetCards(){
        numOfCards=0;
    }
    void addCard(Card card){
        cards[numOfCards] = card;
        numOfCards++;
    }
    int cardsValue() {
        int value = 0;
        int numOfAces = 0;
        for (int i = 0; i<numOfCards; i++){
            if((cards[i].getFace())[0]>='2' && (cards[i].getFace())[0]<='9'||cards[i].getFace()=="10"){
                value+=std::stoi(cards[i].getFace());
            }else if(cards[i].getFace()=="A"){
                numOfAces++;
            }else{
                value+=10;
            }
        }
        if(numOfAces == 1){
            if((value+11)>21){
                value++;
            }else{
                value+=11;
            }
        }else if(numOfAces>1){
            value += numOfAces-1;
            if((value+11)>21){
                value++;
            }else{
                value+=11;
            }           
        }
        return value;
    }

}; 

int bustThreshold (int threshold){
    Deck deck;
    Player p1;
    int numOfBusts = 0;
    for (int i = 0; i<10000; i++){
        p1.resetCards();
        do{
            if (deck.remainingInDeck()<=0){
                break;
            }
            p1.addCard(deck.dealOneCard());
        }while (p1.cardsValue()<threshold && p1.cardsValue()<21);

        if (deck.remainingInDeck()<=0){
            deck.shuffle();
            p1.resetCards();
            i--;
            continue;
        }
        if(p1.cardsValue()>21){
            numOfBusts++;
        }
    }
    return numOfBusts;

}

void whenToStand(){
    cout<<"Bust Threshold: \n(threshold, bust fraction):"<<endl;
    for (int i = 10; i<=20; i++){
        
        float numOfBusts = (float) bustThreshold(i);
        cout<<"("<<i<<", "<<(numOfBusts/10000.0)<<")"<<endl;
    }


}

int main()
{
    //cout << ('10'+1)<<endl; 
    whenToStand();
    Deck deck;
    deck.shuffle();

    Player dealer;
    Player one;
    Player two;
    Player three;


 
    return 0;
}
