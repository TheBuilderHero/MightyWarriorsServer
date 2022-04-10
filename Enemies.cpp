#include <iostream>
#include "Enemies.h"

using namespace std;

int Enemies::enemyChoiceGetStat(int enemyChoice, int returnType, int enemyLevel){ //This function retrives the requested stat (returnType) of a given apponent (enemyChoice) - more then likely we will have the enemy choice randomly generated.
    switch (enemyChoice){
        case 1:
            mutantElf();
            break;
        case 2:
            voidCat();
            break;
        default:
            mutantElf();
            break;
    }
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

string Enemies::getEnemyName(int enemyChoice){
    switch (enemyChoice){
        case 1:
            mutantElf();
            return displayName;
            break;
        case 2:
            voidCat();
            return displayName;
            break;
        default:
            mutantElf();
            return displayName;
            break;
    }
}

void Enemies::mutantElf() {
    displayName = "Mutant Elf";
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

void Enemies::voidCat() {
    displayName = "Void Cat";
    baseHealth = 1000;
    basePhysicalDamage = 10;
    baseArmor = 2;
    baseMagicDamage = 5;
    baseMagicResistance = 5;
    baseAgility = 0; //does not have any
    baseStealth = 0; //does not have any
    level = 1;
    xpDrop = 20;
}