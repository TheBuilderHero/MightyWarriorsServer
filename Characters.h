#include <iostream>
#include <string>


#pragma once

class Characters {
    public:
        std::string name; // in the case of Enemies we will give them names - for players it will be their username
        std::string race; // is one of the following: Human - Elf - Dino - Dryad - Ghost 
        double baseHealth, baseArmor, baseMagicResistance, baseMagicDamage, baseAgility, basePhysicalDamage; //base stats
        int level; // What level the Character is currently at, XP will only be declared for the player so that they can level up.  Enemies do not need XP.
        
        struct weapon{
            std::string weaponName;
            double weaponDamageMin; // the  lowest value of the weapons damage
            double weaponDamageMax;// the highest value of the weapons damage
        };

        void Human(std::string username) {  //Kyle
            name = username;
            race = "Human";
            baseHealth = 100;
            baseArmor = 10;
            baseMagicResistance = 5;
            baseMagicDamage = 1;
            baseAgility = 10;
            basePhysicalDamage = 5;
            level = 0;
        }
        //moved increaseXP to battle.cpp

};