#include "GameState.h"

GameState::GameState() : potSize(0), currentBettingRound(0) {
    // Default constructor
}

void GameState::addPlayer(const Player& player) {
    players.push_back(player);
}

const std::vector<Player>& GameState::getPlayers() const {
    return players;
}

int GameState::getPotSize() const {
    return potSize;
}

const std::vector<Card>& GameState::getCommunityCards() const {
    return communityCards;
}

int GameState::getCurrentBettingRound() const {
    return currentBettingRound;
}

void GameState::setPotSize(int size) {
    potSize = size;
}

void GameState::addCommunityCard(const Card& card) {
    communityCards.push_back(card);
}

void GameState::setCurrentBettingRound(int round) {
    currentBettingRound = round;
}
