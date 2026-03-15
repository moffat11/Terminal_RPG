// Player is an extension of Character
#pragma once
#include "Character.h"
//The dynamic array library
#include <vector>
#include "Weapon.h"

// The ": public Character" tells C++ to inherit everything from Character
class Player : public Character {
private:
    int mana; //Only the Player has mana
    //The player's dynamic backpack
    std::vector<std::string> inventory;

    // The Equipment Slot. It holds a pointer to a Weapon in the RAM
    std::unique_ptr<Weapon> equippedWeapon; 

public:
    // The Player constructor
    Player(std::string charName, int startingHealth, int startingMana);

    // Rewrite the base class damage logic!
    void takeDamage(int damage) override;
    // Player-specific method
    void heal();

    // Inventory Methods
    void pickUpItem(std::string itemName);
    void showInventory();
    void usePotion();

    // Equipment Methods
    void equip(std::unique_ptr<Weapon> newWeapon);
    int getTotalDamageBonus();
};