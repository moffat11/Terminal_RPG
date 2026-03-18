#include "Room.h"

Room::Room(std::string desc) {
    description = desc;
    north = nullptr;
    south = nullptr;
    east = nullptr;
    west = nullptr;
}

void Room::setExits(Room* n, Room* s, Room* e, Room* w) {
    north = n;
    south = s;
    east = e;
    west = w;
}

void Room::printDescription() {
    std::cout << "\n--- LOCATION ---" << std::endl;
    std::cout << description << std::endl;

    // Warning the Player
    if (residentEnemy != nullptr && residentEnemy->isAlive()) {
        std::cout << "\n[WARNING] A " << residentEnemy->getName() << " is blocking your path!" << std::endl;
    }

    std::cout << "Exits: ";
    if (north != nullptr) std::cout << "[North] ";
    if (south != nullptr) std::cout << "[South] ";
    if (east != nullptr) std::cout << "[East] ";
    if (west != nullptr) std::cout << "[West] ";
    std::cout << "\n----------------" << std::endl;
}

// --- ENEMY MANAGEMENT ---
void Room::addEnemy(std::unique_ptr<Enemy> newEnemy) {
    residentEnemy = std::move(newEnemy);
}

Enemy* Room::getEnemy() {
    // Return the raw pointer so the combat engine can interact with it
    return residentEnemy.get();
}

Room* Room::getNorth() {
    return north;
}
Room* Room::getSouth() {
    return south;
}
Room* Room::getEast() {
    return east;
}
Room* Room::getWest() {
    return west;
}