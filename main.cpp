#include <iostream>
#include <memory> //For smart pointers
#include "Player.h" // Include our new Player class!
// Include the new Enemy
#include "Enemy.h"
// Including the <random> library in order to initialize our Random Number Generator before the main
// loop starts.
#include <random>
// Graph architecture
#include "Room.h"
// For reading and writing files
#include <fstream>
#include <string>
// The dictionary to hold our dynamic rooms
#include <unordered_map>
#include <sstream>


int main() {
    // --- Random Number Generator ---
    // Obtains a random seed from the Mac's hardware
    std::random_device rd;
    // Seeds the Mersenne Twister engine
    std::mt19937 gen(rd());

    //Defined Ranges
    // Player hits between 15 - 35
    std::uniform_int_distribution<> playerDmgRange(15, 35);
    // Goblin hits between 10 - 25
    std::uniform_int_distribution<> enemyDmgRange(10, 25);
    // Roll a d100 for percentages
    std::uniform_int_distribution<> critChance(1, 100);

    bool engineRunning = true;

    std::cout << "\n==============================" << std::endl;
    std::cout << "     WELCOME TO THE DUNGEON" << std::endl;
    std::cout << "==============================\n" << std::endl;

    // ---The Two-Pass Map Loader ---
    std::cout << "\n[SYSTEM] Booting Map Loader..." << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Room>> dungeonMap;
    std::unordered_map<std::string, std::string> rawExitData;

    std::ifstream mapFile("map.txt");

    if (!mapFile.is_open()) {
        std::cerr << "[CRITICAL ERROR] Could not locate map.txt!" << std::endl;
    }
    else {
        std::string line;

        // Pass 1: Spawn the rooms
        while (std::getline(mapFile, line)) {
            size_t firstPipe = line.find('|');
            size_t secondPipe = line.find('|', firstPipe + 1);

            if (firstPipe != std::string::npos && secondPipe != std::string::npos) {
                // Slice to three parts
                std::string roomName = line.substr(0, firstPipe);
                std::string roomDesc = line.substr(firstPipe + 1, secondPipe - firstPipe - 1);
                std::string exits = line.substr(secondPipe + 1);

                // Spawn the room
                dungeonMap[roomName] = std::make_unique<Room>(roomDesc);

                // Save the exit text in the notepd for Pass 2
                rawExitData[roomName] = exits;
            }
        }
        mapFile.close();
        // Pass 2: Weave the graph
        for (const auto& pair : rawExitData) {
            std::string currentRoomName = pair.first;
            std::string allExitsString = pair.second;

            std::stringstream ss(allExitsString);
            std::string singleExit;

            // Chop the string by commas ("South:Entrance" then "East:armory")
            while (std::getline(ss, singleExit, ',')) {
                size_t colonPos = singleExit.find(':');
                if (colonPos != std::string::npos) {
                    std::string direction = singleExit.substr(0, colonPos);
                    std::string targetName = singleExit.substr(colonPos + 1);

                    // If the target room actually exists in our dungeon, link the pointer
                    if (dungeonMap.count(targetName)) {
                        dungeonMap[currentRoomName]->setExit(direction, dungeonMap[targetName].get());
                    }
                }
            }
        }
        std::cout << "[SYSTEM] Map loading and graph weaving complete. Total Rooms: " << dungeonMap.size() << "\n" << std::endl;
    }
    // --- THE MASTER ENGINE LOOP ---
    while (engineRunning){

        std::unique_ptr<Player> hero = std::make_unique<Player>("MW", 100, 50);

        // Spawn a legendary weapon and transfer ownership to the Player
        std::unique_ptr<Weapon> legendarySword = std::make_unique<Weapon>("MK", 25);
        hero->equip(std::move(legendarySword));

        // Check for a save file immediately
        // If it returns FALSE (no save exists), give starter loot!
        if (!hero->loadGame()) {
            // The Player has some starting gear
        hero->pickUpItem("Health Potion");
        hero->pickUpItem("Health Potion");
        hero->pickUpItem("Rusty Key");
        }

        // Instantiating three rooms and linking them together
        // ---MAP GENERATION ---

        // Spawn the Goblin and lock him in the Hallway
        std::unique_ptr<Enemy> hallwayGoblin = std::make_unique<Enemy>("G.Goblin", 100);
        //hallway->addEnemy(std::move(hallwayGoblin));

        // 3. Track where the Player is standing (Raw Pointer)
        Room* currentRoom = dungeonMap["Entrance"].get();

        // --- NAVIGATION PHASE ---
        bool exploring = true;
        while (exploring) {
            currentRoom->printDescription();
            std::cout << "\n--- LOCATION ---" << std::endl;

            // Print the available doors
            std::cout << "[ EXITS ]: " << currentRoom->getAvailableExits() << std::endl;

            std::cout << "\nWhich way do you want to go? (North, South, East, West) -> ";
            std::string command;;
            std::cin >> command;

            Room* nextRoom = currentRoom->getExit(command);

            if (nextRoom != nullptr) {
                currentRoom = nextRoom;
                std::cout << "\nYou walk " << command << "..." << std::endl;
            }
            else {
                std::cout << "\n[SYSTEM]. You bump into a solid stone wall. You can't go that way!" << std::endl;
            }
        }

        // Get the raw observing pointer from the room we are standing in
        Enemy* target = currentRoom->getEnemy();

        int round = 1;

        if (target != nullptr && target->isAlive()) {
            //THE GAME LOOP: First check if both characters are still alive and keep going till they are dead.
            while (hero->isAlive() && target->isAlive()){
                std::cout << "\n====== ROUND " << round << " ======" << std::endl;
                hero->printStatus();
                target->printStatus();

                // --- 1. PLAYER TURN ---
                // Include the option of showing the backpack every round
                std::cout << "\nChoose your action: [1] Attack  [2] Heal [3] Use Potion [4] Save Game -> ";
                int choice;
                std::cin >> choice; // The engine pauses her waiting for your keyboard
                
                if (choice == 1) {
                    //Roll for base damage + the weapon's damage bonus
                    int damageDealt = playerDmgRange(gen) + hero->getTotalDamageBonus();

                    // Roll for Critical Strike (15% Chance)
                    if (critChance(gen) <= 15){
                        // Double the damage
                        damageDealt *= 2;
                        std::cout << "\n*** CRITICAL STRIKE! ***" << std::endl;
                    }
                    else {
                        std::cout << "\n*** You swing your sword! ***" << std::endl;
                    }
                    target->takeDamage(damageDealt);

                    // LOOT DROP LOGIC
                    if (!target ->isAlive()) {
                        std::cout << "\n*** The " << target->getName() << " collapses! ***" << std::endl;

                        // Give the Player the XP
                        hero->gainXP(target->getXPReward());

                        // Roll a d100 for the loot table
                        std::uniform_int_distribution<> lootRoll(1, 100);
                        std::string droppedItem = target->getLootDrop(lootRoll(gen));

                        // If it dropped something, put it in the Player's vector inventory
                        if (droppedItem != "Nothing") {
                            std::cout << "[SYSTEM] The enemy dropped some loot!" <<std::endl;
                            hero->pickUpItem(droppedItem);
                        }
                        else {
                            std::cout << "[SYSTEM] You search the enemy, but its pockets are empty." << std::endl;
                        }
                    }
                }
                else if (choice == 2) {
                    hero->heal();
                }
                // New Potion Logic
                else if (choice == 3) {
                    hero->usePotion();
                }
                else if (choice == 4) {
                    hero->saveGame();
                }
                else {
                    std::cout << "\nInvalid choice! You trip and lose your turn." << std::endl;
                }

                // --- 2. ENEMY TURN (Only if it survived the player's attack) ---
                if (target->isAlive()) {
                    std::cout << "\n*** Enemy Turn ***" << std::endl;
                    target->decideAction();
                    // The Goblin rolls for its damage
                    int goblinDamage = enemyDmgRange(gen);
                    hero->takeDamage(goblinDamage); //The Goblin  hits back
                }

                round++;
            }
        }

        // --- GAME OVER CONDITIONS ---
        // --- RESTART SEQUENCE ---
        if (!hero->isAlive()) {
            std::cout << "\n[GAME OVER] You have fallen in the dungeon." << std::endl;
        }
        else {
            std::cout << "\n[VICTORY] You survived the dungeon! For now..." << std::endl;
        }

        std::cout << "\nWould you like to play again? (y/n) -> ";
        char playAgain;
        std::cin >> playAgain;

        if (playAgain == 'n' || playAgain == 'N') {
            std::cout << "\nShuttting down engine. Thanks for playing!" << std::endl;
            // This breaks the master loop and exits the program
            engineRunning = false;
        }
        else {
            // The loop will naturally restart at the top, generating a fresh hero and map!
            std::cout << "\n[SYSTEM] Resetting the world...\n" << std::endl;
        }

    }

    return 0; //Triggers the memory clearing destructors
}
