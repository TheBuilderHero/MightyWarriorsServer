#include <iostream>
#include "Enemies.h"

using namespace std;

void Enemies::mutantElf() {
    name = "Mutant Elf";
    baseHealth = 40;
    basePhysicalDamage = 10;
    baseArmor = 2;
    baseMagicDamage = 5;
    baseMagicResistance = 5;
    level = 1;
    xpDrop = 20;
}