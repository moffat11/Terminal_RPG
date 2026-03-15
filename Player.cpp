#include "Player.h"
#include <iostream>
// Required for searching vectors
#include <algorithm>

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

// The Player's armour will cut all incoming damage directly in half
void Player::takeDamage(int damage) {
    int actualDamage = damage / 2;
    health -= actualDamage;
    if  (health < 0) health = 0;
    std::cout << "[ARMOUR] " << name << "\'s armour deflected half the blow! Only took " << actualDamage << " damage. Health is now  " << health << "." << std::endl;
}

// ---INVENTORY LOGIC ---
void Player::pickUpItem(std::string itemName) {
    // Dynamically expands the array to fit the new item
    inventory.push_back(itemName);
    std::cout << "[LOOT] " << name << " picked up: " << itemName << "!" << std::endl;
}

void Player::showInventory() {
    std::cout << "\n--- Backpack (" << inventory.size() << " slots used) ---" << std::endl;

    if (inventory.empty()) {
        std::cout << "  (Empty)" << std::endl;
        return;
    }

    // Loop through the dynamic array
    for (size_t i = 0; i < inventory.size(); i++) {
        std::cout << "  [" << i + 1 << "] " <<inventory[i] << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}

void Player::usePotion() {
    // Check if there is indeed something in the backpack
    if (inventory.empty()) {
        std::cout << "\n[ACTION] You reach into your backpack... but it's empty!" << std::endl;
        return;
    }

    // Search the entire inventory for a "Health Potion"
    // std::find return an iterator pointing to the item, or it points to .end() if not found
    auto it = std::find(inventory.begin(), inventory.end(), "Health Potion");

    if (it != inventory.end()) {
        // Get potion to be stronger than normal healing
        health += 40;

        // Cap the health at 100 so that the player does not overheal
        if (health > 100) {
            health = 100;
        }

        std::cout << "\n[ACTION] You drank a Health Potion! Recovered 40 HP. Health is now " << health << "." << std::endl;

        // Erase ONLY that specific potion from the vector
        inventory.erase(it);
    }
    else {
        std::cout << "\n[ACTION] You rummage through your bag, but you don't have any Health Potions left!" << std::endl;
    }
}
void Player::equip(std::unique_ptr<Weapon> newWeapon) {
    //Using std::move to take ownership of the memory address
    equippedWeapon = std::move(newWeapon);

    std::cout << "[SYSTEM] " << name << " equipped the " << equippedWeapon->getName() << " (+ " << equippedWeapon->getDamageBonus() << " Damage)!" << std::endl;
}

int Player::getTotalDamageBonus() {
    // Always check for nullptr before reading a pointer
    if (equippedWeapon != nullptr) {
        return equippedWeapon->getDamageBonus();
    }
    return 0;
}