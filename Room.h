#pragma once
#include <string>
#include <iostream>
// For unique_ptr
#include <memory>
// For the enemy blueprint
#include "Enemy.h"
#include <unordered_map>

class Room {
private:
    std::string description;

    // A dictionary linking directions ("North") to Room pointers
    std::unordered_map<std::string, Room*> exits;

    // The Room OWNS whatever enemy is in it
    std::unique_ptr<Enemy> residentEnemy;

public:
    Room(std::string desc);

    // The dynamic exit functions
    void setExit(std::string direction, Room* target);
    Room* getExit(std::string direction);

    void printDescription();

    // Enemy Management methods
    void addEnemy(std::unique_ptr<Enemy> newEnemy);
    // Returns a raw pointer for the engine to look at
    Enemy* getEnemy();
    ~Room();
    // UI Polish
    std::string getAvailableExits();
};