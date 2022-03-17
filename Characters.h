#include <iostream>
#include <string>

#pragma once

using namespace std;

class Characters {
    public:
        string name; // in the case of Enemies we will give them names - for players it will be their username
        string race; // is one of the following: Human - Elf - Dino - Dryad - Ghost 
        double baseHealth, baseArmor, baseMagicResistance, baseAbility, baseAgility, baseDamage; //base stats
        int level; // What level the Character is currently at, XP will only be declared for the player so that they can level up.  Enemies do not need XP.
        
        struct weapon{
            string weaponName;
            double weaponDamageLow; // the  lowest value of the weapons damage
            double weaponDamageHigh;// the highest value of the weapons damage
        };

};