#include <string>

#include "Kit.h"

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
void Kit::pullKitStats(string kitInput, string username){
    if(kitInput == KIT_TANK) tank();
    if(kitInput == KIT_ASSASIN) assasin();
    if(kitInput == KIT_ARCHER) archer();
    if(kitInput == KIT_MAGE) mage();
    if(kitInput == KIT_NINJA) ninja();
}

void Kit::tank(){
    kit = KIT_TANK;
    kitHealth = 30;
    kitPhysicalDamage = 5;
    kitArmor = 20;
    kitMagicDamage = 1;
    kitMagicResistance = 10;
    kitAgility = -10;
    kitStealth = -10;
}
void Kit::assasin(){
    kit = KIT_ASSASIN;
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
    kitHealth = 15;
    kitPhysicalDamage = 5;
    kitArmor = 5;
    kitMagicDamage = 25;
    kitMagicResistance = 15;
    kitAgility = 3;
    kitStealth = 2;
}
void Kit::ninja(){
    kit = KIT_NINJA;
    kitHealth = 5;
    kitPhysicalDamage = 20;
    kitArmor = 5;
    kitMagicDamage = 5;
    kitMagicResistance = 5;
    kitAgility = 15;
    kitStealth = 15;
}
