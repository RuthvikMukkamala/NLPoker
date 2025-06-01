#include "Deck.h"
#include <algorithm> // For std::shuffle, std::iota
#include <random>    // For std::default_random_engine, std::random_device
#include <vector>    // For std::vector
#include <stdexcept> // For std::out_of_range

// Constructor: Initializes a standard 52-card deck
Deck::Deck() {
    reset();
}

// Resets the deck to a standard 52-card set and shuffles it
void Deck::reset() {
    cards.clear();
    for (int s_int = HEARTS; s_int <= SPADES; ++s_int) {
        for (int r_int = TWO; r_int <= ACE; ++r_int) {
            cards.emplace_back(static_cast<RANK>(r_int), static_cast<SUIT>(s_int));
        }
    }
    shuffle(); // Shuffle after initializing
}

// Shuffles the deck
void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

// Deals one card from the top of the deck
// Removes the card from the deck
Card Deck::deal() {
    if (isEmpty()) {
        throw std::out_of_range("Cannot deal from an empty deck.");
    }
    Card topCard = cards.back();
    cards.pop_back();
    return topCard;
}

// Deals a specified number of cards as a vector (a hand)
// Removes the cards from the deck
std::vector<Card> Deck::dealHand(int numCards) {
    if (numCards < 0) {
        throw std::invalid_argument("Number of cards cannot be negative.");
    }
    if (size() < static_cast<size_t>(numCards)) {
        throw std::out_of_range("Not enough cards in deck to deal specified number.");
    }
    std::vector<Card> hand;
    for (int i = 0; i < numCards; ++i) {
        hand.push_back(deal());
    }
    return hand;
}

// Returns the current number of cards in the deck
size_t Deck::size() const {
    return cards.size();
}

// Checks if the deck is empty
bool Deck::isEmpty() const {
    return cards.empty();
}
