#ifndef HAND_H
#define HAND_H

#include <vector>
// #include <string> // No longer needed for Card representation here
#include "Card.h" // Use the official Card definition

// Forward declaration for HandStrength
struct HandStrength;
// Card struct/class is now defined in Card.h

class Hand {
public:
    Hand();
    // Constructor that takes a vector of Cards from the official Card.h
    Hand(const std::vector<Card>& initialCards);

    void addCard(const Card& card); // Card type from Card.h
    std::vector<Card> getCards() const;
    // int getHandStrength() const; // This will be replaced by HandStrength from Evaluator.h
    HandStrength getHandStrength(const std::vector<Card>& communityCards) const; // Updated


private:
    std::vector<Card> cards; // Uses Card from Card.h
};

#endif // HAND_H
