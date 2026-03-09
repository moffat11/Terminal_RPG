#pragma once //This prevents the file from being included twice and crashing the compiler
#include <string>

//Just the blueeprint, no actual code goes here
class Character {
private:
    std::string name;
    int health;

public:
    // Constructor
    Character(std::string charName, int startingHealth);

    //Destructor
    ~Character();

    // Methods
    void takeDamage(int damage);
    void printStatus();

};
