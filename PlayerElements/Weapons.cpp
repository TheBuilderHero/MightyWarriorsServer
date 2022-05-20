// added these files for the weapon class

#include "Weapons.h"
#include "../Cipher.h"

using namespace std;

Weapons::Weapons(int weaponChoice) 
{
    switch(weaponChoice){
        case 1: 
            weaponType = "Sword";
            physicalDamage = 50;
            magicDamage = 0;
            psychicDamage = 0;
            accuracy = 5; //maybe out of 10
            break;
        case 2: 
            weaponType = "Bow";
            physicalDamage = 30;
            magicDamage = 0;
            psychicDamage = 0;
            accuracy = 4; 
            break;
        case 3: 
            weaponType = "Dagger";
            physicalDamage = 30;
            magicDamage = 0;
            psychicDamage = 0;
            accuracy = 6; 
            break;
         case 4: 
            weaponType = "Fire Rune";
            physicalDamage = 10;
            magicDamage = 45;
            psychicDamage = 0;
            accuracy = 8;
            break;
        case 5: 
            weaponType = "Wind Rune";
            physicalDamage = 15;
            magicDamage = 35;
            psychicDamage = 0;
            accuracy = 9;
            break;
        case 6: 
            weaponType = "Ice Spike";
            physicalDamage = 40;
            magicDamage = 90;
            psychicDamage = 0;
            accuracy = 2;
            break;
        case 7: 
            weaponType = "Black Book";
            physicalDamage = 20;
            magicDamage = 20;
            psychicDamage = 5;
            accuracy = 10;
            break;
        default:
        break;
    }
}

void Weapons::loadWeaponData(string username){    //save the weapon bonus' to file:
    Cipher cipher;
    cipher.userDataDeliminationRead(3, username);
}

void Weapons::saveWeaponData(string username){    //save the weapon bonus' to file:
    Cipher cipher;
    cipher.userDataDeliminationWrite(6, username, to_string(iron), to_string(wood), to_string(gems), to_string(feet), to_string(fruit), to_string(brains));
}

Weapons::~Weapons() //Weapon class destructor
{
}