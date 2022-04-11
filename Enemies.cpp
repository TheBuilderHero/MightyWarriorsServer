#include <iostream>
#include "Enemies.h"

using namespace std;

int Enemies::enemyChoiceGetStat(int enemyChoice, int returnType, int enemyLevel){ //This function retrives the requested stat (returnType) of a given apponent (enemyChoice) - more then likely we will have the enemy choice randomly generated.
    if(enemyChoice == MUTANT_ELF) mutantElf();
    if(enemyChoice == VOID_CAT) voidCat();

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

int Enemies::getEnemyPickedFromName(string enemyName){ //This function is intended to go through and test which enemy the client is fighting currently and output that asociated number value
    mutantElf();
    if (enemyName == displayName) return enemyNum;
    voidCat();
    if (enemyName == displayName) return enemyNum;
    return enemyNum; //if it gets to this point it will just return the value stored in enemyNum.
}

void Enemies::mutantElf() {
    enemyNum = MUTANT_ELF; //this is the number associated with this enemy declared in the Enemies.h file
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
    enemyNum = VOID_CAT; //this is the number associated with this enemy declared in the Enemies.h file
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