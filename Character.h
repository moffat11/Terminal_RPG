#pragma once //This prevents the file from being included twice and crashing the compiler
#include <string>

//Just the blueeprint, no actual code goes here
class Character {
//With the name and health being private means that only the Character
//class can see them -even its own children (Player) gets locked out.
//Solution: change them to protected.
protected:
    std::string name;
    int health;

public:
    // Constructor
    Character(std::string charName, int startingHealth);

    //Destructor
    // Adding a 'virtual' here which is critical for memory safety in
    //inheritance
    virtual ~Character();

    // Methods
    // To give the child classes permission to rewrite the takeDamage()
    // Will be doing this by adding the virtual keyword
    virtual void takeDamage(int damage);
    void printStatus();
    bool isAlive();

};
