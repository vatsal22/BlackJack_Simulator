#include <iostream>
#include <cstdlib>

using namespace std;

struct Dice
{
  public:
    int roll()
    {
        return rand() % (6 - 1 + 1) + 1;
    }
};

void rollNTimes(int n)
{
    Dice dice1;

    int numOfRolls[6];
    for (int i = 0; i < 6; i++)
    {
        numOfRolls[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        numOfRolls[dice1.roll() - 1]++;
    }
    cout <<"\n"<< n << " single dice rolls: " << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << i + 1 << ": " << numOfRolls[i] / (float)n << endl;
    }
}

void evenSplit()
{
    Dice dice1;
    int numOfEvenSplits = 0;
    for (int i = 0; i < 10000; i++)
    {
        int numOfLows = 0;  //1,2,3
        int numOfHighs = 0; //4,5,6
        int numOfRolls[6];
        for (int i = 0; i < 6; i++)
        {
            numOfRolls[i] = 0;
        }

        for (int i = 0; i < 100; i++)
        {
            numOfRolls[dice1.roll() - 1]++;
        }
        numOfLows = numOfRolls[0] + numOfRolls[1] + numOfRolls[2];
        numOfHighs = numOfRolls[3] + numOfRolls[4] + numOfRolls[5];
        if (numOfHighs == numOfLows)
        {
            numOfEvenSplits++;
        }
    }
    cout << "\nFraction of time there's an even split between highs and lows: \n"
         << numOfEvenSplits / 10000.0 << endl;
}

void rollDoubleDie(){
    Dice dice1;
    Dice dice2;

    int numOfRolls[11]; //2 to 12
    for (int i=0;i<11;i++){
        numOfRolls[i]=0;
    }

    for(int i=0;i<100000;i++){
        numOfRolls[dice1.roll()+dice2.roll()-2]++;
    }

    cout <<"\n100000 double die rolls: " << endl;
    for (int i = 0; i < 11; i++)
    {
        cout << i + 2 << ": " << numOfRolls[i] / 100000.0 << endl;
    }



}

int main()
{
    cout<<"\nDice Simulator:"<<endl;
    srand(time(0));
    Dice dice1;
    Dice dice2;

    rollNTimes(10);
    rollNTimes(1000);
    rollNTimes(100000);

    evenSplit();

    rollDoubleDie();
}