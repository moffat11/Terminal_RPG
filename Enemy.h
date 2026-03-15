// Build a custom AIState vocabulary and then build the Enemy class
// so it inherits from the Character.
#pragma once
#include "Character.h"

// Start by defining custom AI States
enum class AIState {
    IDLE,
    AGGRESSIVE,
    FLEEING
};

class Enemy : public Character {
private:
    AIState currentState;

public:
    // Constructor
    Enemy(std::string charName, int startingHealth);

    // The AI Logic method
    void decideAction();

    // Loot calculator
    std::string getLootDrop(int rngRoll);

    // To make sure the Enemy is worth something when they die
    int getXPReward();
};