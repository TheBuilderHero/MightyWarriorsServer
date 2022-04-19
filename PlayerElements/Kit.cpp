#include <string>

#include "Kit.h"
#include "../Cipher.h"

using namespace std;

string Kit::getPlayerKit(std::string username, int kitChoice){
    switch(kitChoice){
        case 1:
            return KIT_TANK;
            break;
        case 2:
            return KIT_ASSASIN;
            break;
        case 3:
            return KIT_ARCHER;
            break;
        case 4:
            return KIT_MAGE;
            break;
        case 5:
            return KIT_NINJA;
            break;
        default:
        break;
    }
    return KIT_TANK;
}
string Kit::getPlayerKit(std::string username){
    Cipher code;
    code.userDataDeliminationRead(2, username); 
    return code.getItem(3);//now the kit value is stored in item3 //this will be the string name of the kit
}
void Kit::pullKitStats(string kitInput, string username){
    if(kitInput == KIT_TANK) tank();
    if(kitInput == KIT_ASSASIN) assasin();
    if(kitInput == KIT_ARCHER) archer();
    if(kitInput == KIT_MAGE) mage();
    if(kitInput == KIT_NINJA) ninja();
}
void Kit::pullKitStats(string username){ //overridden version wich should replace the other
    string kitInput = getPlayerKit(username);
    if(kitInput == KIT_TANK) tank();
    if(kitInput == KIT_ASSASIN) assasin();
    if(kitInput == KIT_ARCHER) archer();
    if(kitInput == KIT_MAGE) mage();
    if(kitInput == KIT_NINJA) ninja();
}

string Kit::getRaceDamageTypeForAbility(string username, char abilityLetter){ //this function returns the type of damage a user inflicts based on their kit
    string playerKit = getPlayerKit(username);
    pullKitStats(playerKit, username); //get the info from the players race
    if(abilityLetter == 'q') return qAbilityDamageType;
    if(abilityLetter == 'w') return wAbilityDamageType;
    if(abilityLetter == 'e') return eAbilityDamageType;
    if(abilityLetter == 'r') return rAbilityDamageType;
    return "BadDamageTypeReturn"; //should never get here
}

void Kit::tank(){
    kit = KIT_TANK;
    qAbilityDamageType = DAMAGETYPE_PHYSICAL; //tanks are not magical
    wAbilityDamageType = DAMAGETYPE_PHYSICAL;
    eAbilityDamageType = DAMAGETYPE_PHYSICAL;
    rAbilityDamageType = DAMAGETYPE_PHYSICAL;
    kitHealth = 50;
    kitPhysicalDamage = 5;
    kitArmor = 50;
    kitMagicDamage = 1;
    kitMagicResistance = 50;
    kitAgility = -10;
    kitStealth = -10;
}
void Kit::assasin(){
    kit = KIT_ASSASIN;
    qAbilityDamageType = DAMAGETYPE_PHYSICAL; //assasins have some magic
    wAbilityDamageType = DAMAGETYPE_PHYSICAL;
    eAbilityDamageType = DAMAGETYPE_MAGIC;
    rAbilityDamageType = DAMAGETYPE_PHYSICAL;
    kitHealth = 5;
    kitPhysicalDamage = 30;
    kitArmor = 5;
    kitMagicDamage = 5;
    kitMagicResistance = 5;
    kitAgility = 10;
    kitStealth = 10;
}
void Kit::archer(){
    kit = KIT_ARCHER;
    qAbilityDamageType = DAMAGETYPE_PHYSICAL; //archers have some magic
    wAbilityDamageType = DAMAGETYPE_PHYSICAL;
    eAbilityDamageType = DAMAGETYPE_MAGIC;
    rAbilityDamageType = DAMAGETYPE_PHYSICAL;
    kitHealth = 15;
    kitPhysicalDamage = 20;
    kitArmor = 10;
    kitMagicDamage = 3;
    kitMagicResistance = 5;
    kitAgility = 7;
    kitStealth = 8;
}
void Kit::mage(){
    kit = KIT_MAGE;
    qAbilityDamageType = DAMAGETYPE_MAGIC; //mages are sol magic users
    wAbilityDamageType = DAMAGETYPE_MAGIC;
    eAbilityDamageType = DAMAGETYPE_MAGIC;
    rAbilityDamageType = DAMAGETYPE_MAGIC;
    kitHealth = 15;
    kitPhysicalDamage = 5;
    kitArmor = 5;
    kitMagicDamage = 35;
    kitMagicResistance = 15;
    kitAgility = 3;
    kitStealth = 2;
}
void Kit::ninja(){
    kit = KIT_NINJA;
    qAbilityDamageType = DAMAGETYPE_PHYSICAL; //Ninja is half and half physical and magic
    wAbilityDamageType = DAMAGETYPE_PHYSICAL;
    eAbilityDamageType = DAMAGETYPE_MAGIC;
    rAbilityDamageType = DAMAGETYPE_MAGIC;
    kitHealth = 5;
    kitPhysicalDamage = 20;
    kitArmor = 5;
    kitMagicDamage = 5;
    kitMagicResistance = 5;
    kitAgility = 15;
    kitStealth = 15;
}
