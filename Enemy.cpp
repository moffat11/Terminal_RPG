// Will be using a switch statement(highly optimized if/else block)
// to tell the Goblin exactly what to do depending on its state.

//Since health is protected in the base Character class, the Enemy can read its own health 
// to decide if it needs to panic.

#include "Enemy.h"
#include <iostream>

// Initialize the Enemy and set its default state to IDLE
Enemy::Enemy(std::string charName, int startingHealth)
    : Character(charName, startingHealth) {
    currentState = AIState::IDLE;
}

void Enemy::decideAction() {
    //First start by checking the health to see if our state
    //needs to change.
    if (health < 30) {
        currentState = AIState::FLEEING;
    }
    else if (health < 100) {
        currentState = AIState::AGGRESSIVE;
    }
    //Secondly, execute actions based on the current state
    switch (currentState) {
        case AIState::IDLE:
            std::cout << "[" << name << " AI] " << "Standing still, picking it teeth." << std::endl;
            break;
        case AIState::AGGRESSIVE:
            std::cout << "[" << name << " AI] " << "Lets out a terrifying roar and charges at you!" << std::endl;
            break;
        case AIState::FLEEING:
            std::cout << "[" << name << " AI] " << "Panics and tries to limp away from the battle!" << std::endl;
            break;
    }
}
// --- LOOT SYSTEM ---
std::string Enemy::getLootDrop(int rngRoll) {
    // 20% chance for a rare drop
    if (rngRoll >= 80){
        return "Iron Sword";
    }
    // 40% chance for a consumable
    else if (rngRoll >= 40) {
        return "Health Potion";
    }
    // 40% chance for nothing
    else {
        return "Nothing";
    }
}

int Enemy::getXPReward() {
    // Every Enemy is worth 50XP
    return 50; 
}