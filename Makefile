run: Dice BlackJack
    ./Dice
    ./BlackJack
Dice: Dice.cpp
    g++ Dice.cpp -std=c++11 -g -o Dice
BlackJack: BlackJack.cpp
    g++ BlackJack.cpp card.cpp deck.cpp -std=c++11 -g -o BlackJack
clean:
    rm -f BlackJack
    rm -f Dice
