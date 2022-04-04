#include <iostream>
#include "Enemies.h"

using namespace std;

int Enemies::enemyChoice(int enemyChoice, int returnType){ //This function retrives the requested stat (returnType) of a given apponent (enemyChoice) - more then likely we will have the enemy choice randomly generated.
    mutantElf();
    switch (returnType)
    {
    case 1: //health
        return baseHealth;
        break;
    case 2: //armor
        return baseArmor;
        break;
    case 3: //magicResistance
        return baseMagicResistance;
        break;
    case 4: //physicalDamage
        return basePhysicalDamage;
        break;
    case 5: //magicDamage
        return baseMagicDamage;
        break;
    case 6: //Agility
        return baseAgility;
        break;
    case 7: //Stealth
        return baseStealth;
        break;
    
    default:
        return 0;
        break;
    }
}

void Enemies::mutantElf() {
    name = "Mutant Elf";
    baseHealth = 40;
    basePhysicalDamage = 10;
    baseArmor = 2;
    baseMagicDamage = 5;
    baseMagicResistance = 5;
    baseAgility = 0; //does not have any
    baseStealth = 0; //does not have any
    level = 1;
    xpDrop = 20;
}