#pragma once
#include <string>
#include <iostream>
// For unique_ptr
#include <memory>
// For the enemy blueprint
#include "Enemy.h"

class Room {
private:
    std::string description;

    // Raw observing pointers for navigation
    Room* north;
    Room* south;
    Room* east;
    Room* west;

    // The Room OWNS whatever enemy is in it
    std::unique_ptr<Enemy> residentEnemy;

public:
    Room(std::string desc);

    // Linking this room to others
    void setExits(Room* n, Room* s, Room* e, Room* w);

    void printDescription();

    // Getters so the Player knows where they can walk
    Room* getNorth();
    Room* getSouth();
    Room* getEast();
    Room* getWest();

    // Enemy Management methods
    void addEnemy(std::unique_ptr<Enemy> newEnemy);
    // Returns a raw pointer for the engine to look at
    Enemy* getEnemy();
};