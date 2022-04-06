
#include "Kit.h"

using namespace std;

void Kit::tank(){
    kitHealth = 30;
    kitPhysicalDamage = 5;
    kitArmor = 20;
    kitMagicDamage = 1;
    kitMagicResistance = 10;
    kitAgility = -10; //does not have any
    kitStealth = -10; //does not have any
}
void Kit::assasin(){
    kitHealth = 5;
    kitPhysicalDamage = 30;
    kitArmor = 5;
    kitMagicDamage = 5;
    kitMagicResistance = 5;
    kitAgility = 10; //does not have any
    kitStealth = 10; //does not have any
}
void Kit::archer(){
    kitHealth = 15;
    kitPhysicalDamage = 20;
    kitArmor = 10;
    kitMagicDamage = 3;
    kitMagicResistance = 5;
    kitAgility = 7; //does not have any
    kitStealth = 8; //does not have any
}
void Kit::wizard(){
    kitHealth = 15;
    kitPhysicalDamage = 5;
    kitArmor = 5;
    kitMagicDamage = 25;
    kitMagicResistance = 15;
    kitAgility = 3; //does not have any
    kitStealth = 2; //does not have any
}
void Kit::ninja(){
    kitHealth = 5;
    kitPhysicalDamage = 20;
    kitArmor = 5;
    kitMagicDamage = 5;
    kitMagicResistance = 5;
    kitAgility = 15; //does not have any
    kitStealth = 15; //does not have any
}