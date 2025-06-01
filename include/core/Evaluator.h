#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Card.h"
#include <vector>
#include <map>

enum HandType {
	HIGH_CARD = 0,
    PAIR = 1,
    TWO_PAIR = 2,
    THREE_OF_A_KIND = 3,
    STRAIGHT = 4,
    FLUSH = 5,
    FULL_HOUSE = 6,
    FOUR_OF_A_KIND = 7,
    STRAIGHT_FLUSH = 8,
    ROYAL_FLUSH = 9
};

struct HandStrength {
	HandType type; 
	std::vector<int> kickers; 

	bool operator>(const HandStrength& other) const;
    bool operator==(const HandStrength& other) const; // Added for ties
	std::string toString() const; 

}; 

class HandEvaluator {
public:
    static HandStrength evaluate(const std::vector<Card>& cards); // Evaluates N cards (e.g. 7 cards)
    static HandStrength evaluate(const std::vector<Card>& hand, const std::vector<Card>& communityCards); // Convenience overload
    static std::string getHandTypeName(HandType type);
    // Monte Carlo method - should be public
    static double calculateEquityMonteCarlo(const std::vector<Card>& heroHand,
                                            const std::vector<Card>& communityCards,
                                            int numOpponents,
                                            int numSimulations);
    
private:
    static void generateCombinations(const std::vector<Card>& cards, int k, int start, 
                                   std::vector<Card> current, std::vector<std::vector<Card>>& result);
    static HandStrength evaluateFiveCards(std::vector<Card> cards); // Keep this for direct 5-card eval
    // The simulateRandomTrial was initially planned but its logic is currently within calculateEquityMonteCarlo.
    static bool isStraight(const std::vector<Card>& cards, RANK& straightHigh);
    static bool isFlush(const std::vector<Card>& cards);
    static std::map<RANK, int> getRankCounts(const std::vector<Card>& cards);
};

#endif