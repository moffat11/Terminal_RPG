#include "Weapon.h"

Weapon::Weapon(std::string weaponName, int bonus) {
    name = weaponName;
    damageBonus = bonus;
}

std::string Weapon::getName() {
    return name;
}
int Weapon::getDamageBonus() {
    return damageBonus;
}