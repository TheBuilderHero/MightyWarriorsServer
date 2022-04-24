// added these files for the weapon class

#include "Weapons.h"
#include "../Cipher.h"

using namespace std;

Weapons::Weapons(int weaponChoice) 
{
    switch(weaponChoice){
        case 1: 
            weaponType = "Sword";
            physicalDamage = 20;
            magicDamage = 0;
            psychicDamage = 0;
            accuracy = 5; //maybe out of 10
            break;
        case 2: 
            weaponType = "Bow";
            physicalDamage = 12;
            magicDamage = 0;
            psychicDamage = 0;
            accuracy = 4; 
            break;
        case 3: 
            weaponType = "Dagger";
            physicalDamage = 12;
            magicDamage = 0;
            psychicDamage = 0;
            accuracy = 6; 
            break;
         case 4: 
            weaponType = "Fire Rune";
            physicalDamage = 3;
            magicDamage = 18;
            psychicDamage = 0;
            accuracy = 8;
            break;
        case 5: 
            weaponType = "Wind Rune";
            physicalDamage = 6;
            magicDamage = 14;
            psychicDamage = 0;
            accuracy = 9;
            break;
        case 6: 
            weaponType = "Ice Spike";
            physicalDamage = 16;
            magicDamage = 36;
            psychicDamage = 0;
            accuracy = 2;
            break;
        case 7: 
            weaponType = "Black Book";
            physicalDamage = 8;
            magicDamage = 8;
            psychicDamage = 5;
            accuracy = 10;
            break;
        default:
        break;
    }
}

int Weapons::getPlayerWeapon(std::string username){
   /* Cipher code;
    code.userDataDeliminationRead(2, username); //Dakota please help me write weapon data to the user file
    return code.getItem(3); */
    return 1;
}

Weapons::~Weapons() //Weapon class destructor
{
}