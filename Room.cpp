#include "Room.h"
// Constructor
Room::Room(std::string desc) {
    description = desc;
}

void Room::printDescription() {
    std::cout << description << std::endl;

    // Warning the Player
    if (residentEnemy != nullptr && residentEnemy->isAlive()) {
        std::cout << "\n[WARNING] A " << residentEnemy->getName() << " is blocking your path!" << std::endl;
    }
}

// --- ENEMY MANAGEMENT ---
void Room::addEnemy(std::unique_ptr<Enemy> newEnemy) {
    residentEnemy = std::move(newEnemy);
}

Enemy* Room::getEnemy() {
    // Return the raw pointer so the combat engine can interact with it
    return residentEnemy.get();
}

Room::~Room() {
    std::cout << "[MEMORY] Room destroyed. Cleaning up floor tiles..." << std::endl;
}

// Adds a new door to the room
void Room::setExit(std::string direction, Room * target) {
    exits[direction] = target;
}

// Looks for a door. If it doesn't exist, it returns a null pointer safely.
Room* Room::getExit(std::string direction) {
    if (exits.count(direction)) {
        return exits[direction];
    }
    return nullptr;
}

std::string Room::getAvailableExits() {
    // if there are no doors (a trap room!), return a default message
    if (exits.empty()) {
        return "None. You are trapped!";
    }

    std::string exitList = "";

    // Loop through the dictionary
    // 'pair.first' is the direction string (e.g North, South, ...)
    // 'pair.second' is the pointer (not needed here)
    for (const auto& pair : exits) {
        exitList += pair.first + ", ";
    }

    // The loop leaves a trailing comma and the space at the very end
    //Chop off the last two characters to make it clean
    exitList.pop_back();
    exitList.pop_back();

    return exitList;
}