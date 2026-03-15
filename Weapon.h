// Acts as the structural blueprint for every single weapon in the game.
#pragma once
#include <string>

class Weapon {
private:
    std::string name;
    int damageBonus;

public:
    // Constructor
    Weapon(std::string weaponName, int bonus);

    // Getter functions
    std::string getName();
    int getDamageBonus();
};