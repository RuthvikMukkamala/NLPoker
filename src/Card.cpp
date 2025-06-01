#include "Card.h"
#include <stdexcept> // For std::invalid_argument in constructor (optional)

// Constructor
Card::Card(RANK r_val, SUIT s_val) : r(r_val), s(s_val) {
    // Optional: Add validation for rank and suit if necessary
    // For example, ensure r_val and s_val are within valid enum ranges
}

// Convert rank to string
std::string Card::getRankString() const {
    switch (r) {
        case TWO: return "2";
        case THREE: return "3";
        case FOUR: return "4";
        case FIVE: return "5";
        case SIX: return "6";
        case SEVEN: return "7";
        case EIGHT: return "8";
        case NINE: return "9";
        case TEN: return "T";
        case JACK: return "J";
        case QUEEN: return "Q";
        case KING: return "K";
        case ACE: return "A";
        default: return "?"; // Should not happen
    }
}

// Convert suit to string
std::string Card::getSuitString() const {
    switch (s) {
        case HEARTS: return "H";
        case DIAMONDS: return "D";
        case CLUBS: return "C";
        case SPADES: return "S";
        default: return "?"; // Should not happen
    }
}

// Convert card to string (e.g., "AH", "TD", "2S")
std::string Card::toString() const {
    return getRankString() + getSuitString();
}

// Equality operator
bool Card::operator==(const Card& other) const {
    return (r == other.r && s == other.s);
}

// Less-than operator (useful for sorting, define based on rank primarily, then suit)
bool Card::operator<(const Card& other) const {
    if (r == other.r) {
        return s < other.s;
    }
    return r < other.r;
}
