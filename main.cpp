#include <iostream>
#include <memory> //For smart pointers
#include "Player.h" // Include our new Player class!
// Include the new Enemy
#include "Enemy.h"
// Gonna rewrite the main.cpp file and do the game loop

int main() {
    std::cout << "--- THE DUNGEON GATES OPEN ---" << std::endl;

    std::unique_ptr<Player> hero = std::make_unique<Player>("MW", 100, 50);
    std::unique_ptr<Enemy> goblin = std::make_unique<Enemy>("G.Goblin", 100);

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
            std::cout << "\n*** You swing your sword ***" << std::endl;
            goblin->takeDamage(30);
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
            hero->takeDamage(20); //The Goblin  hits back
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
