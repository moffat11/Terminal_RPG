#include "Character.h" //Import the blueprint
#include <iostream>

//Constructor logic
Character::Character(std::string charName, int startingHealth) {
    name = charName;
    health = startingHealth;
    std::cout << name << " has entered the battle!" << std::endl;
}

//Damage logic
void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
    std::cout << name << " took " << damage << " damage! Health is now " << health << "." << std::endl;
}

//Status logic
void Character::printStatus() {
    std::cout << "---" << name << " Status: " << health << " HP ---" << std::endl;
}

// Destructor Logic
Character::~Character() {
    std::cout << "[MEMORY CLEARED] " << name << " has been safely removed from RAM!" << std::endl;
}

bool Character::isAlive() {
    return health > 0;
}