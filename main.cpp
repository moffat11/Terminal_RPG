#include <iostream>

int main(){
    // 1. Create a normal variable
    int playerHealth = 100;
    // 2. Create a pointer that stores the physical memory address of playerHealth
    // The '&' symbol means "get the memory address of"
    int* healthPointer = &playerHealth;

    // Print them out to see the difference
    std::cout << "Player Health Value: " << playerHealth << std::endl;

    //This prints a hexadecimal number, the actual physical memory location which I sometimes 
    // visualize as a box, in the RAM
    std::cout << "Memory Address in RAM: " << healthPointer << std::endl;

    // 3. The dereference operator ('*')
    // Putting a '*' in front of a pointer means "go to that address and get the value"
    std::cout << "Value at the Address: " << *healthPointer << std::endl;
    
    // 4. Changing the value directly through memory
    *healthPointer = 80;

    std::cout << "New Player Health: " << playerHealth << std::endl;

    return 0;
}