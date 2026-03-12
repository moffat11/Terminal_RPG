#include <iostream>
#include <memory> //For smart pointers
#include "Player.h" // Include our new Player class!
// Include the new Enemy
#include "Enemy.h"
// Including the <random> library in order to initialize our Random Number Generator before the main
// loop starts.
#include <random>
// Going rewrite the main.cpp file and do the game loop

int main() {
    std::cout << "--- THE DUNGEON GATES OPEN ---" << std::endl;

    std::unique_ptr<Player> hero = std::make_unique<Player>("MW", 100, 50);
    std::unique_ptr<Enemy> goblin = std::make_unique<Enemy>("G.Goblin", 100);

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

    //THE GAME LOOP: First check if both characters are still alive and keep going till they are dead.
    while (hero->isAlive() && goblin->isAlive()){
        std::cout << "\n====== ROUND " << round << " ======" << std::endl;
        hero->printStatus();
        goblin->printStatus();

        // --- 1. PLAYER TURN ---
        std::cout << "\nChoose your action: [1] Attack  [2] Heal -> ";
        int choice;
        std::cin >> choice; // The engine pauses her waiting for your keyboard
        
        if (choice == 1) {
            //Roll for base damage
            int damageDealt = playerDmgRange(gen);

            // Roll for Critical Strike (15% Chance)
            if (critChance(gen) <= 15){
                // Double the damage
                damageDealt *= 2;
                std::cout << "\n*** CRITICAL STRIKE! ***" << std::endl;
            }
            else {
                std::cout << "\n*** You swing your sword! ***" << std::endl;
            }
            goblin->takeDamage(damageDealt);
        }
        else if (choice == 2) {
            hero->heal();
        }
        else {
            std::cout << "\nInvalid choice! You trip and lose your turn." << std::endl;
        }

        // --- 2. ENEMY TURN (Only if it survived the player's attack) ---
        if (goblin->isAlive()) {
            std::cout << "\n*** Enemy Turn ***" << std::endl;
            goblin->decideAction();
            // The Goblin rolls for its damage
            int goblinDamage = enemyDmgRange(gen);
            hero->takeDamage(goblinDamage); //The Goblin  hits back
        }

        round++;
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
