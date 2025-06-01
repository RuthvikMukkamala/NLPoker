#include "Player.h" // Assuming this will be found by include paths later
#include "Hand.h"   // Assuming Hand.h will be in a path accessible by the compiler

Player::Player(int id, int stackSize) : id(id), stackSize(stackSize), currentHand(nullptr), currentBet(0) {}

int Player::getId() const {
    return id;
}

int Player::getStackSize() const {
    return stackSize;
}

int Player::getCurrentBet() const {
    return currentBet;
}

const Hand& Player::getHand() const {
    // Basic error handling or assertion
    if (!currentHand) {
        // Or throw an exception
        // For now, let's consider creating a default/empty hand if appropriate
        // or handle this scenario based on game rules.
        // This part needs careful design based on how hands are managed.
        // For simplicity, returning a static empty hand or throwing is an option.
        // Let's assume for now currentHand will always be set before being accessed in a real scenario.
        // This is a placeholder for proper handling.
        static Hand emptyHand; // Requires Hand to have a default constructor
        return emptyHand;
    }
    return *currentHand;
}

void Player::setCurrentBet(int bet) {
    currentBet = bet;
}

void Player::setHand(const Hand& hand) {
    // Assuming Hand is copyable or Player manages Hand's lifecycle
    // If currentHand is dynamically allocated, manage memory appropriately
    // For now, let's assume Hand objects are managed elsewhere or are simple enough to copy
    // This might need a copy constructor or assignment operator in Hand if it's complex
    if(currentHand) delete currentHand; // Basic memory management
    currentHand = new Hand(hand); // Assumes Hand has a copy constructor
}

void Player::adjustStackSize(int amount) {
    stackSize += amount;
}
