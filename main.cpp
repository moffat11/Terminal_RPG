#include <iostream>
#include <memory> //For smart pointers
#include "Player.h" // Include our new Player class!

int main() {
    std::cout << "--- BATTLE START ---" << std::endl;

    //Spawn a PLAYER dynamically on the Heap
    std::unique_ptr<Player> hero = std::make_unique<Player>("MW", 100, 50);

    hero->printStatus(); // Inherited from Character
    hero->takeDamage(30); // Inherited from Character
    hero-> heal(); // Specific to Player
    hero->printStatus(); // Notice the health went back up

    std::cout << "--- Battle END ---" << std::endl;
    return 0;
}
