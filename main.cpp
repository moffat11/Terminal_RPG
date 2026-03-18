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
// Going rewrite the main.cpp file and do the game loop

int main() {
    std::cout << "--- THE DUNGEON GATES OPEN ---" << std::endl;

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
    // 1. The Engine OWNS the memory
    std::unique_ptr<Room> entrance = std::make_unique<Room>("Dungeon Entrance: A cold damp stone room. The heavy iron door behind you is sealed shut.");
    std::unique_ptr<Room> hallway = std::make_unique<Room>("Dark Hallway: Torches flicker on the walls. You can hear a goblin grunting to the North.");
    std::unique_ptr<Room> armory = std::make_unique<Room>("Armory: Old rusted weapons line the walls. It smells like oil and iron.");

    // 2. The Rooms OBSERVE each other using .get()
    // Order: North, South, East, West
    entrance->setExits(hallway.get(), nullptr, nullptr, nullptr);
    hallway->setExits(nullptr, entrance.get(), armory.get(), nullptr);
    armory->setExits(nullptr, nullptr, nullptr, hallway.get());

    // Spawn the Goblin and lock him in the Hallway
    std::unique_ptr<Enemy> hallwayGoblin = std::make_unique<Enemy>("G.Goblin", 100);
    hallway->addEnemy(std::move(hallwayGoblin));

    // 3. Track where the Player is standing (Raw Pointer)
    Room* currentRoom = entrance.get();

    // --- NAVIGATION PHASE ---
    bool exploring = true;
    while (exploring) {
        currentRoom->printDescription();

        std::cout << "\nWhich way do you want to go? (n/s/e/w) or (c) to enter Combat -> ";
        char move;
        std::cin >> move;

        if (move == 'n' && currentRoom->getNorth() != nullptr) {
            currentRoom = currentRoom->getNorth();
            std::cout << "\n[SYSTEM] You walk North." << std::endl;
        }
        else if (move == 's' && currentRoom->getSouth() != nullptr) {
            currentRoom = currentRoom->getSouth();
            std::cout << "\n[SYSTEM] You walk South." << std::endl;
        }
        else if (move == 'e' && currentRoom->getEast() != nullptr) {
            currentRoom = currentRoom->getEast();
            std::cout << "\n[SYSTEM] You walk East." << std::endl;
        }
        else if (move == 'w' && currentRoom->getWest() != nullptr) {
            currentRoom = currentRoom->getWest();
            std::cout << "\n[SYSTEM] You walk West." << std::endl;
        }
        else if (move == 'c') {
            if (currentRoom->getEnemy() != nullptr && currentRoom->getEnemy()->isAlive()) {
                std::cout << "\n[SYSTEM] You draw your weapon and charge the " << currentRoom->getEnemy()->getName() << "!" << std::endl;
                exploring = false;  
            }
            else {
                std::cout << "\n[SYSTEM] You swing your weapon at the air. There is nothing to fight here." << std::endl;
            }
        }
        else {
            std::cout << "\n[SYSTEM]. You bump into a solid stone wall. You can't go that way!" << std::endl;
        }
    }

    // Get the raw observing pointer from the room we are standing in
    Enemy* target = currentRoom->getEnemy();
    

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
    std::cout << "\n====== COMBAT END ======" << std::endl;
    if (hero->isAlive()) {
        std::cout << "VICTORY! You defeated the G.Goblin" << std::endl;
    }
    else {
        std::cout << "DEFEAT! You have fallen in battle..." << std::endl;
    }

    return 0; //Triggers the memory clearing destructors
}
