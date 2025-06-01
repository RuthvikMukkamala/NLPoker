#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <random>

class Deck {
private:
	std::vector<Card> cards; 

public:
	Deck(); 

	void reset(); 
	void shuffle(); 

	Card deal(); 
	std::vector<Card> dealHand(int numCards); 

	size_t size() const; 
	bool isEmpty() const; 
};

#endif