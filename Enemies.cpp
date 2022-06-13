#include <iostream>
#include <cmath>
#include "Enemies.h"

using namespace std;

int Enemies::enemyChoiceGetStat(int enemyChoice){ //this version is used by the getXPDrop function because the otherone causes an infinite loop.
    if(enemyChoice == MUTANT_ELF) mutantElf();
    if(enemyChoice == VOID_CAT) voidCat();
    if(enemyChoice == HIGHWAY_ROBBER) highwayRobber();
    if(enemyChoice == ORC_ENEMY) orc();
    if(enemyChoice == SASQUATCH_ENEMY) sasquatch();
    if(enemyChoice == SKUNK_ENEMY) skunk();
    if(enemyChoice == MUTANT_SKUNK) mutantSkunk();
    if(enemyChoice == GIANT_RACCOON) giantRaccoon();
    if(enemyChoice == EVIL_WIZARD) evilWizard();
    if(enemyChoice == WITCH_ENEMY) witch();
    if(enemyChoice == MUTANT_GHOST) mutantGhost();
    if(enemyChoice == WERE_WOLF) wereWolf();
    if(enemyChoice == NORMAL_POTATO) normalPotato();
    if(enemyChoice == GOBLIN_MORG) goblinMorg();
    if(enemyChoice == ORC_KLADE) orcKlade();
    if(enemyChoice == BLACK_NIGHT) blackNight();
    if(enemyChoice == BLUE_WIZARD) blueWizard();
    if(enemyChoice == MONSTROUS_BEHEMOTH) monstrousBehemoth();
    if(enemyChoice == AWFUL_NECROMANCER) awfulNecromancer();
    if(enemyChoice == THE_DRAGON) theDragon();
    return 0; //does not return anything useful
}
int Enemies::enemyChoiceGetStat(int enemyChoice, int returnType, int enemyLevel){ //This function retrives the requested stat (returnType) of a given apponent (enemyChoice) - more then likely we will have the enemy choice randomly generated.
    //based on the enemy choice set the enemy stat values:
    if(enemyChoice == MUTANT_ELF) mutantElf();
    if(enemyChoice == VOID_CAT) voidCat();
    if(enemyChoice == HIGHWAY_ROBBER) highwayRobber();
    if(enemyChoice == ORC_ENEMY) orc();
    if(enemyChoice == SASQUATCH_ENEMY) sasquatch();
    if(enemyChoice == SKUNK_ENEMY) skunk();
    if(enemyChoice == MUTANT_SKUNK) mutantSkunk();
    if(enemyChoice == GIANT_RACCOON) giantRaccoon();
    if(enemyChoice == EVIL_WIZARD) evilWizard();
    if(enemyChoice == WITCH_ENEMY) witch();
    if(enemyChoice == MUTANT_GHOST) mutantGhost();
    if(enemyChoice == WERE_WOLF) wereWolf();
    if(enemyChoice == NORMAL_POTATO) normalPotato();    
    if(enemyChoice == GOBLIN_MORG) goblinMorg();
    if(enemyChoice == ORC_KLADE) orcKlade();
    if(enemyChoice == BLACK_NIGHT) blackNight();
    if(enemyChoice == BLUE_WIZARD) blueWizard();
    if(enemyChoice == MONSTROUS_BEHEMOTH) monstrousBehemoth();
    if(enemyChoice == AWFUL_NECROMANCER) awfulNecromancer();
    if(enemyChoice == THE_DRAGON) theDragon();

    //modify the values based on level of the player 
    enemyLevelStatBuff(enemyChoice, enemyLevel);

    switch (returnType)
    {
    case 1: //health
        return getBaseHealth();
        break;
    case 2: //armor
        return getBaseArmor();
        break;
    case 3: //magicResistance
        return getBaseMagicResistance();
        break;
    case 4: //physicalDamage
        return getBasePhysicalDamage();
        break;
    case 5: //magicDamage
        return getBaseMagicDamage();
        break;
    case 6: //Agility
        return getBaseAgility();
        break;
    case 7: //Stealth
        return getBaseStealth();
        break;
    
    default:
        return 0;
        break;
    }
}

double Enemies::getXPDrop(int enemyChoice){
    //calls the override function to prevent looping
    enemyChoiceGetStat(enemyChoice); //pull the xpDrop stat from the enemy
    return xpDrop; //return the xpDrop amount
}
void Enemies::enemyLevelStatBuff(int enemyChoice, int enemyLevel){
    double currentDropXP = getXPDrop(enemyChoice); //running at the beguining so that it does not overrite the modifiers below

    //per level stat addition multiplier:
    double healthLevelBuff = .2;
    double physicalDamageLevelBuff = .2;
    double armorLevelBuff = .2;
    double magicDamageLevelBuff = .2;
    double magicResistanceLevelBuff = .2;
    double agilityLevelBuff = .2;
    double stealthLevelBuff = .2;
    double xpLevelBuff = .2;

    //set the new stat values for the enemy with the applied level buff.
    setBaseHealth(getBaseHealth() + round(enemyLevel * healthLevelBuff));
    setBasePhysicalDamage(getBasePhysicalDamage() + round(enemyLevel * physicalDamageLevelBuff));
    setBaseArmor(getBaseArmor()  + round(enemyLevel * armorLevelBuff));
    setBaseMagicDamage(getBaseMagicDamage() + round(enemyLevel * magicDamageLevelBuff));
    setBaseMagicResistance(getBaseMagicResistance() + round(enemyLevel * magicResistanceLevelBuff));
    setBaseAgility(getBaseAgility() + round(enemyLevel * agilityLevelBuff));
    setBaseStealth(getBaseStealth() + round(enemyLevel * stealthLevelBuff));
    xpDrop = currentDropXP + round(enemyLevel * stealthLevelBuff);
}
string Enemies::getEnemyName(int enemyChoice){ //returns names based on input int 1 - 13
    switch (enemyChoice){
        case 1:
            mutantElf();
            return displayName;
            break;
        case 2:
            voidCat();
            return displayName;
            break;
        case 3:
            highwayRobber();
            return displayName;
            break;
        case 4:
            orc();
            return displayName;
            break;
        case 5:
            sasquatch();
            return displayName;
            break;
        case 6:
            skunk();
            return displayName;
            break;
        case 7:
            mutantSkunk();
            return displayName;
            break;
        case 8:
            giantRaccoon();
            return displayName;
            break;
        case 9:
            evilWizard();
            return displayName;
            break;
        case 10:
            witch();
            return displayName;
            break;
        case 11:
            mutantGhost();
            return displayName;
            break;
        case 12:
            wereWolf();
            return displayName;
            break;
        case 13:
            normalPotato();
            return displayName;
            break;
        case 91:
            goblinMorg();
            return displayName;
            break;
        case 92:
            orcKlade();
            return displayName;
            break;
        case 93:
            blackNight();
            return displayName;
            break;
        case 94:
            blueWizard();
            return displayName;
            break;
        case 95:
            monstrousBehemoth();
            return displayName;
            break;
        case 96:
            awfulNecromancer();
            return displayName;
            break;
        case 97:
            theDragon();
            return displayName;
            break;
            //Please note, if you add more enemies to this list you will need to update the range of the random number generator switch statement case 7, in the funcion requestActions() in the file source.cpp
        default: //if none of these we will input mutantElf()
            mutantElf();
            return displayName;
            break;
    }
}

//Found the XP Drop problem LOL - Richard
int Enemies::getEnemyPickedFromName(string enemyName){ //This function is intended to go through and test which enemy the client is fighting currently and output that asociated number value
    mutantElf();
    if (enemyName == displayName) return enemyNum;
    voidCat();
    if (enemyName == displayName) return enemyNum;
    return enemyNum; //if it gets to this point it will just return the value stored in enemyNum.
}

//Enemies:
void Enemies::mutantElf() {
    enemyNum = MUTANT_ELF; //this is the number associated with this enemy declared in the Enemies.h file
    displayName = "Mutant Elf";
    setBaseHealth(40);
    setBasePhysicalDamage(10);
    setBaseArmor(2);
    setBaseMagicDamage(5);
    setBaseMagicResistance(5);
    setBaseAgility(0); //does not have any
    setBaseStealth(0); //does not have any
    setLevel(1);
    xpDrop = 20;
}
void Enemies::voidCat() {
    enemyNum = VOID_CAT; //this is the number associated with this enemy declared in the Enemies.h file
    displayName = "Void Cat";
    setBaseHealth(10);
    setBasePhysicalDamage(1);
    setBaseArmor(1);
    setBaseMagicDamage(1);
    setBaseMagicResistance(1);
    setBaseAgility(0); //does not have any
    setBaseStealth(0); //does not have any
    setLevel(1);
    xpDrop = 200;
    //Radiation damage that mutants can inflict?
}
void Enemies::highwayRobber(){
    enemyNum = HIGHWAY_ROBBER;
    displayName = "Highway Robber";
    setBaseHealth(60);
    setBasePhysicalDamage(15);
    setBaseArmor(10);
    setBaseMagicDamage(2);
    setBaseMagicResistance(2);
    setBaseAgility(0); //does not have any
    setBaseStealth(0); //does not have any
    setLevel(1);
    xpDrop = 10;
}
void Enemies::orc(){
    enemyNum = ORC_ENEMY;
    displayName = "Orc";
    setBaseHealth(70);
    setBasePhysicalDamage(20);
    setBaseArmor(15);
    setBaseMagicDamage(10);
    setBaseMagicResistance(7);
    setLevel(1);
    xpDrop = 10;
}
void Enemies::sasquatch(){
    enemyNum = SASQUATCH_ENEMY;
    displayName = "Sasquatch";
    setBaseHealth(120);
    setBasePhysicalDamage(35);
    setBaseArmor(20);
    setBaseMagicDamage(15);
    setBaseMagicResistance(3);
    setLevel(1);
    xpDrop = 80;
}
void Enemies::skunk(){
    enemyNum = SKUNK_ENEMY;
    displayName = "Skunk";
    setBaseHealth(25);
    setBasePhysicalDamage(10);
    setBaseArmor(1);
    setBaseMagicDamage(2);
    setBaseMagicResistance(2);
    //toxicAttack = 17; //need to declare in headerfile
    setLevel(1);
    xpDrop = 7;
    //Skunk has very low armor and magic stats to compensate for toxic damage.
}
void Enemies::mutantSkunk(){
    enemyNum = MUTANT_SKUNK;
    displayName = "Mutant Skunk";
    setBaseHealth(25);
    setBasePhysicalDamage(10);
    setBaseArmor(1);
    setBaseMagicDamage(0);
    setBaseMagicResistance(0);
    //toxicAttack = 17; //need to declare in headerfile
    //radiation = 10; //need to declare in headerfile
    setLevel(1);
    xpDrop = 12;
}
void Enemies::giantRaccoon(){
    enemyNum = GIANT_RACCOON;
    displayName = "Giant Raccoon";
    setBaseHealth(350);
    setBasePhysicalDamage(65);
    setBaseArmor(80);
    setBaseMagicDamage(25);
    setBaseMagicResistance(15);
    setLevel(1);
    xpDrop = 500;
    //GIANT RACCOON!!! Mini-boss.
}
void Enemies::evilWizard(){
    enemyNum = EVIL_WIZARD;
    displayName = "Evil Wizard";
    setBaseHealth(80);
    setBasePhysicalDamage(20);
    setBaseArmor(8);
    setBaseMagicDamage(20);
    setBaseMagicResistance(12);
    setLevel(1);
    xpDrop = 80;
}
void Enemies::witch(){
    enemyNum = WITCH_ENEMY;
    displayName = "Witch";
    setBaseHealth(70);
    setBasePhysicalDamage(13);
    setBaseArmor(10);
    setBaseMagicDamage(30);
    setBaseMagicResistance(15);
    setLevel(1);
    xpDrop = 80;
}
void Enemies::mutantGhost(){
    enemyNum = MUTANT_GHOST;
    displayName = "Mutant Ghost";
    setBaseHealth(95);
    setBasePhysicalDamage(20);
    setBaseArmor(1);
    setBaseMagicDamage(35);
    setBaseMagicResistance(23);
    setLevel(1);
    xpDrop = 100;
}
void Enemies::wereWolf(){
    enemyNum = WERE_WOLF;
    displayName = "Werewolf";
    setBaseHealth(80);
    setBasePhysicalDamage(25);
    setBaseArmor(5);
    setBaseMagicDamage(12);
    setBaseMagicResistance(8);
    setLevel(1);
    xpDrop = 70;
}
void Enemies::normalPotato(){
    enemyNum = NORMAL_POTATO;
    displayName = "A normal potato";
    setBaseHealth(9999);
    setBasePhysicalDamage(999);
    setBaseArmor(99);
    setBaseMagicDamage(999);
    setBaseMagicResistance(99);
    setLevel(1);
    xpDrop = 9999;
}
void Enemies::goblinMorg(){
    enemyNum = GOBLIN_MORG;
    displayName = "Morg the Goblin";
    setBaseHealth(50);
    setBasePhysicalDamage(9);
    setBaseArmor(2);
    setBaseMagicDamage(0);
    setBaseMagicResistance(2);
    setLevel(1);
    xpDrop = 100;
}
void Enemies::orcKlade(){
    enemyNum = ORC_KLADE;
    displayName = "Klade the Orc";
    setBaseHealth(100);
    setBasePhysicalDamage(15);
    setBaseArmor(3);
    setBaseMagicDamage(20);
    setBaseMagicResistance(4);
    setLevel(1);
    xpDrop = 200;
}
void Enemies::blackNight(){
    enemyNum = BLACK_NIGHT;
    displayName = "The Black Night";
    setBaseHealth(175);
    setBasePhysicalDamage(25);
    setBaseArmor(10);
    setBaseMagicDamage(10);
    setBaseMagicResistance(50);
    setLevel(1);
    xpDrop = 350;
}
void Enemies::blueWizard(){
    enemyNum = BLUE_WIZARD;
    displayName = "The Blue Wizard";
    setBaseHealth(200);
    setBasePhysicalDamage(10);
    setBaseArmor(20);
    setBaseMagicDamage(35);
    setBaseMagicResistance(30);
    setLevel(1);
    xpDrop = 500;
}
void Enemies::monstrousBehemoth(){
    enemyNum = MONSTROUS_BEHEMOTH;
    displayName = "The Monstrous Behemoth";
    setBaseHealth(400);
    setBasePhysicalDamage(50);
    setBaseArmor(20);
    setBaseMagicDamage(20);
    setBaseMagicResistance(20);
    setLevel(1);
    xpDrop = 750;
}
void Enemies::awfulNecromancer(){
    enemyNum = AWFUL_NECROMANCER;
    displayName = "The Awful Necromancer";
    setBaseHealth(400);
    setBasePhysicalDamage(30);
    setBaseArmor(30);
    setBaseMagicDamage(70);
    setBaseMagicResistance(50);
    setLevel(1);
    xpDrop = 1000;
}
void Enemies::theDragon(){
    enemyNum = THE_DRAGON;
    displayName = "The Dragon!!!";
    setBaseHealth(750);
    setBasePhysicalDamage(100);
    setBaseArmor(75);
    setBaseMagicDamage(70);
    setBaseMagicResistance(75);
    setLevel(1);
    xpDrop = 2000;
}