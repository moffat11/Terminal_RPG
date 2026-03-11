// Player is an extension of Character
#pragma once
#include "Character.h"

// The ": public Character" tells C++ to inherit everything from Character
class Player : public Character {
private:
    int mana; //Only the Player has mana

public:
    // The Player constructor
    Player(std::string charName, int startingHealth, int startingMana);

    // Rewrite the base class damage logic!
    void takeDamage(int damage) override;
    // Player-specific method
    void heal();
};