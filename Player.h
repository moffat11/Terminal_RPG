// Player is an extension of Character
#pragma once
#include "Character.h"
//The dynamic array library
#include <vector>
#include "Weapon.h"
// The File Stream
#include <fstream>

// The ": public Character" tells C++ to inherit everything from Character
class Player : public Character {
private:
    int mana; //Only the Player has mana
    //The player's dynamic backpack
    std::vector<std::string> inventory;

    // The Equipment Slot. It holds a pointer to a Weapon in the RAM
    std::unique_ptr<Weapon> equippedWeapon; 

    // Track variables for Level and XP, plus the functions to handle them
    // Progression Stats
    int level;
    int currentXP;
    int xpToNextLevel;

    // Helper function for the Player to trigger their own level up
    void levelUp();

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

    // Public method for the engine to give the Player XP
    void gainXP(int amount);

    // Data Persistence
    void saveGame();
    bool loadGame();
};