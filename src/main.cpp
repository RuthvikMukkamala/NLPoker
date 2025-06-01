#include <iostream>
#include <vector>
#include <string>

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Hand.h"
#include "GameState.h"
#include "Evaluator.h" // For HandEvaluator and HandStrength

// Helper function to print a hand
void printHand(const std::vector<Card>& cards) {
    for (size_t i = 0; i < cards.size(); ++i) {
        std::cout << cards[i].toString();
        if (i < cards.size() - 1) {
            std::cout << " ";
        }
    }
}

int main() {
    std::cout << "Starting Simple Poker CLI Game..." << std::endl;

    // 1. Create a GameState object
    GameState gameState;

    // 2. Add a few Player objects
    Player player1(1, 1000); // Player ID 1, Stack 1000
    Player player2(2, 1000); // Player ID 2, Stack 1000

    gameState.addPlayer(player1);
    gameState.addPlayer(player2);

    std::cout << "Players created and added to game state." << std::endl;
    std::cout << "Number of players: " << gameState.getPlayers().size() << std::endl;


    // 3. Create a Deck object and shuffle it
    Deck deck;
    std::cout << "Deck created with " << deck.size() << " cards." << std::endl;
    deck.shuffle(); // Deck is typically shuffled on creation, but explicit shuffle is fine
    std::cout << "Deck shuffled." << std::endl;

    // 4. Deal two cards to each player
    // Note: GameState holds players by value (copied when added).
    // To modify players (like setting their hand), we need to work with references
    // or pointers from the GameState's player list, or re-add them.
    // For simplicity, let's assume GameState::getPlayers() could return non-const if we need to modify them directly
    // Or, players are dealt hands, and these hands are associated with player IDs externally for now.
    // Let's create hands and assign them to player objects, then update them in GameState if necessary.
    // A more robust approach would be for GameState to manage player objects that can be modified.

    // For this example, let's deal hands and store them locally.
    // We'll re-fetch players from GameState to display info.

    std::vector<Player> players_from_state = gameState.getPlayers(); // Gets a copy
    if (players_from_state.size() < 2) {
        std::cerr << "Not enough players to deal cards." << std::endl;
        return 1;
    }

    // Create Hand objects for players
    Hand hand1, hand2;

    try {
        std::cout << "\nDealing hands..." << std::endl;
        hand1.addCard(deck.deal());
        hand1.addCard(deck.deal());
        players_from_state[0].setHand(hand1); // Player object needs to store its hand

        hand2.addCard(deck.deal());
        hand2.addCard(deck.deal());
        players_from_state[1].setHand(hand2);
    } catch (const std::out_of_range& e) {
        std::cerr << "Error dealing cards: " << e.what() << std::endl;
        return 1;
    }

    // The players_from_state vector contains copies. To update the actual players
    // in gameState, GameState would need to provide a way to get references to its players.
    // For this simple CLI, we'll mostly display based on these local copies.
    // A better design:
    // GameState* gs = ...; gs->getPlayer(id)->setHand(...);
    // Or Player* p = gs->getPlayer(id); p->setHand(...);
    // Or gameState.dealCardsToPlayer(playerId, deck);

    std::cout << "Player 1 hand: "; printHand(players_from_state[0].getHand().getCards()); std::cout << std::endl;
    std::cout << "Player 2 hand: "; printHand(players_from_state[1].getHand().getCards()); std::cout << std::endl;


    // 5. Deal community cards (e.g., flop, turn, river)
    std::vector<Card> communityCards;
    try {
        std::cout << "\nDealing Flop..." << std::endl;
        communityCards.push_back(deck.deal());
        communityCards.push_back(deck.deal());
        communityCards.push_back(deck.deal());
        // Update GameState's community cards
        for(const auto& card : communityCards) {
            gameState.addCommunityCard(card);
        }
        std::cout << "Flop: "; printHand(gameState.getCommunityCards()); std::cout << std::endl;

        std::cout << "\nDealing Turn..." << std::endl;
        Card turnCard = deck.deal();
        gameState.addCommunityCard(turnCard); // Add to GameState
        communityCards.push_back(turnCard); // Also keep local copy for evaluation if needed separately
        std::cout << "Turn: "; printHand(gameState.getCommunityCards()); std::cout << std::endl;

        std::cout << "\nDealing River..." << std::endl;
        Card riverCard = deck.deal();
        gameState.addCommunityCard(riverCard); // Add to GameState
        communityCards.push_back(riverCard); // Local copy
        std::cout << "River: "; printHand(gameState.getCommunityCards()); std::cout << std::endl;

    } catch (const std::out_of_range& e) {
        std::cerr << "Error dealing community cards: " << e.what() << std::endl;
        return 1;
    }

    // 6. Display the game state
    std::cout << "\n--- Current Game State ---" << std::endl;
    std::cout << "Pot Size: " << gameState.getPotSize() << std::endl; // Pot not updated in this example
    std::cout << "Community Cards: "; printHand(gameState.getCommunityCards()); std::cout << std::endl;

    const std::vector<Player>& finalPlayers = gameState.getPlayers(); // Get fresh copy
    for (size_t i = 0; i < finalPlayers.size(); ++i) {
        // The hands dealt earlier were to 'players_from_state' copies.
        // The actual Player objects in gameState don't have these hands set.
        // This is a limitation of the current GameState/Player design for this CLI.
        // To show hands correctly here, we'd need to iterate players_from_state or modify GameState
        // For now, let's use the hands from players_from_state which we updated.
        std::cout << "Player " << players_from_state[i].getId() << ": ";
        printHand(players_from_state[i].getHand().getCards());
        // Stack size and bet would also be part of player's state
        std::cout << " (Stack: " << players_from_state[i].getStackSize()
                  << ", Bet: " << players_from_state[i].getCurrentBet() << ")" << std::endl;
    }

    // 7. Use the Evaluator class to determine the best hand for each player
    std::cout << "\n--- Hand Evaluation ---" << std::endl;
    for (size_t i = 0; i < players_from_state.size(); ++i) {
        HandStrength strength = players_from_state[i].getHand().getHandStrength(gameState.getCommunityCards());
        std::cout << "Player " << players_from_state[i].getId() << " best hand: " << strength.toString() << std::endl;
    }

    // 8. Calculate and display Monte Carlo Equity
    std::cout << "\n--- Monte Carlo Equity (vs 1 opponent, 10000 sims) ---" << std::endl;
    int numSimulations = 10000; // Number of simulations to run
    int numOpponents = 1;       // Assuming 1 opponent for this calculation

    for (size_t i = 0; i < players_from_state.size(); ++i) {
        if (players_from_state[i].getHand().getCards().size() == 2) { // Ensure player has a hand
            double equity = HandEvaluator::calculateEquityMonteCarlo(
                players_from_state[i].getHand().getCards(), // Player's 2 hole cards
                gameState.getCommunityCards(),              // All 5 community cards
                numOpponents,
                numSimulations
            );
            std::cout << "Player " << players_from_state[i].getId() << " Equity: "
                      << (equity * 100.0) << "%" << std::endl;
        }
    }

    std::cout << "\nGame finished." << std::endl;

    return 0;
}
