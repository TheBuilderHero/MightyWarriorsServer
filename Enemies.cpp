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
    //Radiation damage that mutants can inflict?
}

void Enemies::highwayRobber(){
    name = "Highway Robber";
    health = 60;
    attack = 15;
    armor = 10;
    magicAttack = 2;
    magicResistence = 2;
    level = 1;
    xpDrop = 10;
}

void Enemies::orc(){
    name = "Orc";
    health = 70;
    attack = 20;
    armor = 15;
    magicAttack = 10;
    magicResistence = 7;
    level = 1;
    xpDrop = 10;
}

void Enemies::sasquatch(){
    name = "Sasquatch";
    health = 120;
    attack = 35;
    armor = 20;
    magicAttack = 15;
    magicResistence = 3;
    level = 1;
    xpDrop = 80;
}

void Enemies::skunk(){
    name = "Skunk";
    health = 25;
    attack = 10;
    armor = 1;
    magicAttack = 2;
    magicResistence = 2;
    toxicAttack = 17;
    level = 1;
    xpDrop = 7;
    //Skunk has very low armor and magic stats to compensate for toxic damage.
}

void Enemies::mutantSkunk(){
    name = "Mutant Skunk";
    health = 25;
    attack = 10;
    armor = 1;
    magicAttack = 0;
    magicResistence = 0;
    toxicAttack = 17;
    radiation = 10;
    level = 1;
    xpDrop = 12;
}

void Enemies::giantRaccoon(){
    name = "Giant Raccoon";
    health = 350;
    attack = 65;
    armor = 80;
    magicAttack = 25;
    magicResistence = 15;
    level = 1;
    xpDrop = 500;
    //GIANT RACCOON!!! Mini-boss.
}

void Enemies::evilWizard(){
    name = "Evil Wizard";
    health = 80;
    attack = 20;
    armor = 8;
    magicAttack = 20;
    magicResistence = 12;
    level = 1;
    xpDrop = 80;
}

void Enemies::witch(){
    name = "Witch";
    health = 70;
    attack = 13;
    armor = 10;
    magicAttack = 30;
    magicResistence = 15;
    level = 1;
    xpDrop = 80;
}

void Enemies::mutantGhost(){
    cout << "BOOO!!";
    name = "Mutant Ghost";
    health = 95;
    attack = 20;
    armor = 1;
    magicAttack = 35;
    magicResistence = 23;
    level = 1;
    xpDrop = 100;
}

void Enemies::wereWolf(){
    name = "Werewolf";
    health = 80;
    attack = 25;
    armor = 5;
    magicAttack = 12;
    magicResistence = 8;
    level = 1;
    xpDrop = 70;
}