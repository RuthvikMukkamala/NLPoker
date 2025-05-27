#ifndef CARD_H
#define CARD_H

#include <string>

enum SUIT { 
	HEARTS, 
	DIAMONDS, 
	CLUBS, 
	SPADES }; 

enum RANK { 
	TWO = 2, 
	THREE, 
	FOUR, 
	FIVE, 
	SIX, 
	SEVEN, 
	EIGHT, 
	NINE, 
	TEN, 
	JACK, 
	QUEEN, 
	KING, 
	ACE }

class Card {
private:
	RANK r; 
	SUIT s; 
public:
	Card(RANK r, SUIT s); 

	RANK getRank() const {return r;}
	SUIT getSuit() const {return s;}

	std::string toString() const;
	std::string getRankString() const; 
	std::string getSuitString() const; 

	bool operator==(const Card& other) const; 
	bool operator<(const Card& other) const; 
}; 

#endif