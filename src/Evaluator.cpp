#include "Evaluator.h"
#include <algorithm> // For std::sort, std::reverse, std::remove_if, std::find
#include <vector>    // For std::vector
#include <random>    // For std::shuffle, std::random_device, std::mt19937
#include <stdexcept> // For std::runtime_error (if needed)
#include <iostream>  // For placeholder messages (optional, for debugging)

// --- HandStrength struct methods ---
bool HandStrength::operator>(const HandStrength& other) const {
    if (type != other.type) {
        return type > other.type;
    }
    // For same type, compare kickers (more complex, placeholder for now)
    // This basic comparison assumes kickers are sorted high to low
    for (size_t i = 0; i < kickers.size() && i < other.kickers.size(); ++i) {
        if (kickers[i] != other.kickers[i]) {
            return kickers[i] > other.kickers[i];
        }
    }
    return kickers.size() > other.kickers.size(); // Or based on specific game rules
}

std::string HandStrength::toString() const {
    return HandEvaluator::getHandTypeName(type) + " (Kickers: placeholder)";
    // A more detailed kicker string would be useful here.
}

bool HandStrength::operator==(const HandStrength& other) const {
    if (type != other.type) {
        return false;
    }
    // For kickers, the current implementation of HandStrength might not be detailed enough
    // for perfect equality (e.g. if kickers are not sorted or have variable length based on hand type)
    // For now, assume kickers vector comparison is sufficient if types are same.
    // A robust implementation would require kickers to be consistently defined and sorted.
    return kickers == other.kickers;
}


// --- HandEvaluator class static methods ---

std::string HandEvaluator::getHandTypeName(HandType type) {
    switch (type) {
        case HIGH_CARD: return "High Card";
        case PAIR: return "Pair";
        case TWO_PAIR: return "Two Pair";
        case THREE_OF_A_KIND: return "Three of a Kind";
        case STRAIGHT: return "Straight";
        case FLUSH: return "Flush";
        case FULL_HOUSE: return "Full House";
        case FOUR_OF_A_KIND: return "Four of a Kind";
        case STRAIGHT_FLUSH: return "Straight Flush";
        case ROYAL_FLUSH: return "Royal Flush";
        default: return "Unknown Hand Type";
    }
}

// Placeholder: Generates combinations of k cards from the given cards
// This is a helper for evaluating best 5-card hand from 7 cards (2 hole + 5 community)
void HandEvaluator::generateCombinations(const std::vector<Card>& cards, int k, int start,
                                       std::vector<Card> currentCombination,
                                       std::vector<std::vector<Card>>& allCombinations) {
    if (k == 0) {
        allCombinations.push_back(currentCombination);
        return;
    }
    for (size_t i = start; i <= cards.size() - k; ++i) {
        currentCombination.push_back(cards[i]);
        generateCombinations(cards, k - 1, i + 1, currentCombination, allCombinations);
        currentCombination.pop_back(); // Backtrack
    }
}

// Placeholder: Evaluates a 5-card hand.
// This is where the core hand ranking logic for a 5-card hand would go.
HandStrength HandEvaluator::evaluateFiveCards(std::vector<Card> fiveCards) {
    if (fiveCards.size() != 5) {
        // This should ideally not happen if called correctly
        return {HIGH_CARD, {}};
    }
    // Sort cards to make evaluation easier (e.g., by rank)
    std::sort(fiveCards.begin(), fiveCards.end()); // Assumes Card::operator< is defined

    // Basic placeholder logic:
    // For now, just return High Card with the highest card as kicker
    // A real implementation would check for pairs, straights, flushes, etc.
    HandStrength strength;
    strength.type = HIGH_CARD;
    // Example: Add sorted card ranks as kickers (descending)
    for (int i = 4; i >= 0; --i) {
        strength.kickers.push_back(static_cast<int>(fiveCards[i].getRank()));
    }
    // std::cout << "Warning: evaluateFiveCards is a placeholder." << std::endl;
    return strength;
}

// Main evaluation function: evaluates the best 5-card hand from a given set of cards (e.g., 7 cards)
HandStrength HandEvaluator::evaluate(const std::vector<Card>& holeCardsAndCommunityCards) {
    if (holeCardsAndCommunityCards.size() < 5) {
        // Not enough cards to form a 5-card hand. This might be an error
        // or a pre-flop/flop scenario where evaluation isn't usually done this way.
        // For now, return a default low-strength hand.
        return {HIGH_CARD, {}}; // Or throw an error
    }

    if (holeCardsAndCommunityCards.size() == 5) {
        return evaluateFiveCards(holeCardsAndCommunityCards);
    }

    // If more than 5 cards (e.g., 7 cards for Texas Hold'em), generate all 5-card combinations
    std::vector<std::vector<Card>> fiveCardCombinations;
    std::vector<Card> currentCombination;
    generateCombinations(holeCardsAndCommunityCards, 5, 0, currentCombination, fiveCardCombinations);

    HandStrength bestHand = {HIGH_CARD, {}}; // Initialize with lowest possible hand

    if (fiveCardCombinations.empty() && holeCardsAndCommunityCards.size() >= 5) {
        // This might happen if generateCombinations is flawed or not called for >=5 cards
        // Fallback to evaluate the first 5 cards if no combinations generated, though this is not ideal.
        // std::cout << "Warning: No 5-card combinations generated, evaluating first 5 cards as fallback." << std::endl;
        // Consider throwing an error or logging this issue.
        // For now, let's make a new vector of the first 5 cards.
        std::vector<Card> firstFive(holeCardsAndCommunityCards.begin(), holeCardsAndCommunityCards.begin() + 5);
        bestHand = evaluateFiveCards(firstFive);

    } else {
         for (const auto& combo : fiveCardCombinations) {
            HandStrength currentHandStrength = evaluateFiveCards(combo);
            if (currentHandStrength > bestHand) { // Assumes HandStrength::operator> is implemented
                bestHand = currentHandStrength;
            }
        }
    }
    // std::cout << "Warning: HandEvaluator::evaluate is using placeholder logic." << std::endl;
    return bestHand;
}


// Helper: Checks for a straight
bool HandEvaluator::isStraight(const std::vector<Card>& cards, RANK& straightHigh) {
    // Placeholder
    // std::cout << "Warning: isStraight is a placeholder." << std::endl;
    return false;
}

// Helper: Checks for a flush
bool HandEvaluator::isFlush(const std::vector<Card>& cards) {
    // Placeholder
    // std::cout << "Warning: isFlush is a placeholder." << std::endl;
    return false;
}

// Helper: Gets rank counts
std::map<RANK, int> HandEvaluator::getRankCounts(const std::vector<Card>& cards) {
    // Placeholder
    // std::cout << "Warning: getRankCounts is a placeholder." << std::endl;
    return {};
}

// --- Monte Carlo Simulation Methods ---

double HandEvaluator::calculateEquityMonteCarlo(const std::vector<Card>& heroHand,
                                                const std::vector<Card>& communityCards,
                                                int numOpponents, // For now, let's assume 1 opponent for simplicity in first pass
                                                int numSimulations) {
    if (heroHand.size() != 2) {
        // Or throw error
        // std::cerr << "Hero hand must have 2 cards for Monte Carlo simulation." << std::endl;
        return 0.0;
    }
    if (numOpponents <= 0) {
        // std::cerr << "Number of opponents must be positive." << std::endl;
        return 0.0; // Or 1.0 if no opponents means hero always wins? Or error.
    }


    int heroWins = 0;
    int ties = 0; // A tie is when hero's hand == best opponent hand and no other opponent is better

    // Create a full card list for building simulation decks
    std::vector<Card> fullDeckCards;
    for (int s_int = HEARTS; s_int <= SPADES; ++s_int) {
        for (int r_int = TWO; r_int <= ACE; ++r_int) {
            fullDeckCards.emplace_back(static_cast<RANK>(r_int), static_cast<SUIT>(s_int));
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = 0; i < numSimulations; ++i) {
        // Variables for win/tie state for the current trial, declared before any goto target
        bool heroWinsThisTrial = true;
        bool heroTiesThisTrial = false;
        int numTiedWithHero = 0; // Number of opponents who tied with hero's hand

        std::vector<Card> simDeckCards = fullDeckCards;

        // Remove known cards (hero hand + community)
        std::vector<Card> knownCards = heroHand;
        knownCards.insert(knownCards.end(), communityCards.begin(), communityCards.end());

        simDeckCards.erase(std::remove_if(simDeckCards.begin(), simDeckCards.end(),
            [&](const Card& c) {
                return std::find(knownCards.begin(), knownCards.end(), c) != knownCards.end();
            }), simDeckCards.end());

        std::shuffle(simDeckCards.begin(), simDeckCards.end(), g);

        std::vector<Card> currentCommunityCards = communityCards;
        unsigned int simDeckIdx = 0; // Current index for drawing from simDeckCards

        // Deal remaining community cards
        int communityCardsNeeded = 5 - currentCommunityCards.size();
        if (communityCardsNeeded < 0) communityCardsNeeded = 0;

        for (int j = 0; j < communityCardsNeeded; ++j) {
            if (simDeckIdx >= simDeckCards.size()) break;
            currentCommunityCards.push_back(simDeckCards[simDeckIdx++]);
        }

        if (currentCommunityCards.size() != 5) continue;

        HandStrength heroBestHand = HandEvaluator::evaluate(heroHand, currentCommunityCards);

        HandStrength overallBestOpponentHand = {HIGH_CARD, {}}; // Tracks the strongest hand among all opponents
        bool atLeastOneOpponentValid = false;

        std::vector<HandStrength> opponentHandsStrengths;

        for (int opp = 0; opp < numOpponents; ++opp) {
            if (simDeckIdx + 1 >= simDeckCards.size()) { // Need 2 cards for opponent
                // Not enough cards for this opponent, can't run a fair trial for *all* opponents
                goto next_simulation; // Break out of outer loop to restart simulation
            }
            std::vector<Card> opponentHandCards;
            opponentHandCards.push_back(simDeckCards[simDeckIdx++]);
            opponentHandCards.push_back(simDeckCards[simDeckIdx++]);

            HandStrength opponentStrength = HandEvaluator::evaluate(opponentHandCards, currentCommunityCards);
            opponentHandsStrengths.push_back(opponentStrength);
            atLeastOneOpponentValid = true; // At least one opponent got cards
        }

        if (!atLeastOneOpponentValid && numOpponents > 0) {
             //This means we couldn't even deal for the first opponent.
             //This can happen if deck runs out.
             goto next_simulation; // Skip this simulation if no opponent hands could be formed
        }

        // Determine winner against all opponents
        // heroWinsThisTrial, heroTiesThisTrial, numTiedWithHero are already declared at the top of the loop

        for(const auto& oppStrength : opponentHandsStrengths) {
            if (oppStrength > heroBestHand) {
                heroWinsThisTrial = false; // Hero is beaten by at least one opponent
                heroTiesThisTrial = false; // No tie if hero is beaten
                break;
            }
            if (oppStrength == heroBestHand) {
                heroTiesThisTrial = true; // Hero ties with at least one opponent
                numTiedWithHero++;
            }
            // If oppStrength < heroBestHand, hero is winning against this one, continue checking
        }

        if (heroWinsThisTrial) {
            if (heroTiesThisTrial) {
                // Hero's hand is equal to the best hand(s) among opponents, and not beaten by any.
                ties++; // Count as a "tie" outcome for equity calculation
                        // More precise: ties += 1.0 / (numTiedWithHero + 1.0) then wins for hero is just wins.
            } else {
                // Hero's hand is strictly better than all opponent hands.
                heroWins++;
            }
        }
        // If !heroWinsThisTrial, hero lost (no win, no tie points for this trial).

        next_simulation:; // Label for goto
    }

    // Equity calculation:
    // A common way: (wins + ties / (number_of_players_in_the_pot_splitting)) / simulations
    // For now, a simple approach: each tie event contributes 1/(N+1) to hero where N is num of tied opponents.
    // Or, simpler: wins contribute 1, ties contribute 0.5 (assuming 1 opponent usually) or 1/num_players_in_tie.
    // The current loop counts 'ties' if hero ties with the best hand among opponents,
    // and is not beaten by anyone.
    // If heroWins = 1, heroTiesThisTrial = false: Hero gets 1 point.
    // If heroWins = 1, heroTiesThisTrial = true: Hero ties with one or more opponents, but beats others.
    // This 'ties' counter currently means "hero was part of a chop".
    // A common poker equity definition is P(win) + P(tie)/N_way_tie.
    // The current code: (heroWins + ties * 0.5) is a simplification.
    // Let's stick to (heroWins + ties * 0.5) / numSimulations for now assuming ties are split evenly on average.
    // This is an approximation, especially with multiple opponents.
    if (numSimulations == 0) return 0.0;
    return (static_cast<double>(heroWins) + static_cast<double>(ties) * 0.5) / static_cast<double>(numSimulations);
}

// This is the evaluate overload that takes hero hand and community cards
HandStrength HandEvaluator::evaluate(const std::vector<Card>& hand, const std::vector<Card>& community) {
    std::vector<Card> combined_cards = hand;
    combined_cards.insert(combined_cards.end(), community.begin(), community.end());
    return HandEvaluator::evaluate(combined_cards); // Calls the existing N-card evaluate
}
