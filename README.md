# Terminal-Based RPG 🗡️

A lightweight, text-based role-playing game engineered from scratch in C++ to solidify object-oriented programming principles and low-level memory management. 

## Features
* **Modern Memory Safety:** Utilizes <memory> and smart pointers (std::unique_ptr) with virtual destructors to guarantee a leak-free environment.
* **Polymorphic Combat System:** Employs virtual functions and class inheritance (Character -> Player / Enemy) to handle custom damage mitigation and armor logic dynamically.
* **Algorithmic Enemy AI:** Features a Finite State Machine (FSM) where enemies dynamically shift states (Idle, Aggressive, Fleeing) based on real-time health evaluations.
* **Unpredictable RNG Math:** Replaces legacy rand() with the C++ <random> library (Mersenne Twister std::mt19937) to calculate dynamic damage ranges and critical strike multipliers.
* **State Progression & Loot Tables:** Features a mathematics-driven XP leveling system and percentage-based loot tables tied directly to the enemy's lifecycle.
* **Data Persistence (File I/O):** Utilizes the C++ `<fstream>` library to construct a robust save/load architecture, successfully serializing dynamic player states to physical disk space and completely reconstructing them upon engine boot.

## Tech Stack
* **Language:** C++
* **Environment:** Linux Command Line
* **Version Control:** Git

## How to Run
1) Clone the repository and navigate to the project directory:
(`git clone https://github.com/moffat11/Terminal_RPG.git`)
(`cd Terminal_RPG`)

2) Compile the game engine
(`g++ main.cpp Character.cpp Player.cpp Enemy.cpp -o rpg`)

3) Execute the binary:
(`./rpg`)
