#include "Player.h"
#include <iostream>

// Call the base Character constructor to handle name and health,
// then handle mana here.
Player::Player(std::string charName, int startingHealth, int startingMana)
    : Character (charName, startingHealth) {
        mana = startingMana;
    }

void Player::heal() {
    if (mana >= 10) {
        // We have access to 'health' because it is 'protected' in Character
        health += 20;
        mana -= 10;
        std::cout << name << " casts a healing spell! Recovered 20 HP. Mana left: " << mana << std::endl;
    }
    else {
        std::cout << name << " does not have enough mana to heal!" << std::endl;
    }
}