#include <iostream>
#include <memory> //For smart pointers
#include "Character.h" //Import new class

int main() {
    std::cout << "Initializing Game Engine... " << std::endl;

    // Create a Character dynamically on the Heap using a Smart Pointer
    // std:::make_unique guarantees this memory will not leak
    std::unique_ptr<Character> playerOne = std::make_unique<Character>("Supreme", 100);

    // Because plaayerOne is a pointer, we use -> to call its methods, not a dot
    playerOne->printStatus();
    playerOne->takeDamage(25);
    playerOne->printStatus();

    std::cout << "Shutting downengine ..." << std::endl;
}
