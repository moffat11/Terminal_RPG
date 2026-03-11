#include <iostream>
#include <memory> //For smart pointers
#include "Player.h" // Include our new Player class!
// Include the new Enemy
#include "Enemy.h"

int main() {
    std::cout << "--- DRAGON ATTACK ---" << std::endl;
    // Hitting both the player and goblin at the same time

    std::unique_ptr<Player> hero = std::make_unique<Player>("MW", 100, 50);
    std::unique_ptr<Enemy> goblin = std::make_unique<Enemy>("G.Goblin", 100);

    std::cout <<"\n*** A Different teamplayer fires for 40 damage! ***" << std::endl;

    //G.Goblin takes the hit (Uses the base Character logic)
    goblin->takeDamage(40);

    //MWtakes the hit (Uses custom Player override logic)
    hero->takeDamage(40);

    std::cout << "\n--- BATTLE END ---" << std::endl;
    return 0;
}
