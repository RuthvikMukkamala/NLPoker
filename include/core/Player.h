#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
// #include "Hand.h" // Forward declaration or include later

class Hand; // Forward declaration

class Player {
public:
    Player(int id, int stackSize);

    int getId() const;
    int getStackSize() const;
    int getCurrentBet() const;
    const Hand& getHand() const; // Assuming Hand class will be defined

    void setCurrentBet(int bet);
    void setHand(const Hand& hand); // Assuming Hand class will be defined
    void adjustStackSize(int amount);

private:
    int id;
    Hand* currentHand; // Pointer to allow forward declaration
    int stackSize;
    int currentBet;
};

#endif // PLAYER_H
