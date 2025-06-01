#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "Player.h"
#include "Card.h" // For community cards

class GameState {
public:
    GameState();

    void addPlayer(const Player& player);
    const std::vector<Player>& getPlayers() const;
    int getPotSize() const;
    const std::vector<Card>& getCommunityCards() const; // Assuming Card is defined
    int getCurrentBettingRound() const;

    void setPotSize(int size);
    void addCommunityCard(const Card& card); // Assuming Card is defined
    void setCurrentBettingRound(int round);

private:
    std::vector<Player> players;
    int potSize;
    std::vector<Card> communityCards; // Assuming Card type from Hand.h
    int currentBettingRound;
};

#endif // GAMESTATE_H
