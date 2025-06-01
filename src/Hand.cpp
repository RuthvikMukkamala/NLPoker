#include "Hand.h"
#include "Evaluator.h" // For HandStrength and HandEvaluator
#include <vector>

Hand::Hand() {
    // Default constructor
}

// Constructor that takes a vector of Cards (from official Card.h)
Hand::Hand(const std::vector<Card>& initialCards) : cards(initialCards) {
}

void Hand::addCard(const Card& card) { // Card type from Card.h
    cards.push_back(card);
}

std::vector<Card> Hand::getCards() const {
    return cards;
}

// Updated getHandStrength
HandStrength Hand::getHandStrength(const std::vector<Card>& communityCards) const {
    std::vector<Card> allCards = cards; // Start with player's hole cards
    allCards.insert(allCards.end(), communityCards.begin(), communityCards.end());

    // Use HandEvaluator to evaluate the combined cards
    // HandEvaluator::evaluate should be able to handle more than 5 cards
    // and find the best 5-card combination.
    return HandEvaluator::evaluate(allCards);
}
