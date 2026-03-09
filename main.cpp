#include <iostream>
#include <memory> //For smart pointers
#include "Player.h" // Include our new Player class!
// Include the new Enemy
#include "Enemy.h"

int main() {
    std::cout << "--- BATTLE START ---" << std::endl;

    //Spawn a PLAYER dynamically on the Heap
    std::unique_ptr<Player> hero = std::make_unique<Player>("MW", 100, 50);
    std::unique_ptr<Enemy> goblin = std::make_unique<Enemy>("G.Goblin", 100);

    std::cout << "\n*** Round 1 ***" << std::endl;
    goblin->decideAction(); // IDLE and health is at 100

    std::cout << "\n*** MW attacks G.Goblin! ***" << std::endl;
    goblin->takeDamage(40);
    goblin->decideAction(); //Health drops below 100 and should be AGGRESSIVE

    std::cout << "\n*** MW hits a critical strike! ***" << std::endl;
    goblin->takeDamage(35);
    goblin->decideAction(); // FLEEING as health is less than < 30

    std::cout << "--- BATTLE END ---" << std::endl;
    return 0;
}
