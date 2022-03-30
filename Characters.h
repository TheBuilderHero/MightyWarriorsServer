#include <iostream>
#include <string>
#include <cmath>    //Kyle

#pragma once

class Characters {
    public:
        std::string name; // in the case of Enemies we will give them names - for players it will be their username
        std::string race; // is one of the following: Human - Elf - Dino - Dryad - Ghost 
        double baseHealth, baseArmor, baseMagicResistance, baseAbility, baseAgility, baseDamage; //base stats
        int level; // What level the Character is currently at, XP will only be declared for the player so that they can level up.  Enemies do not need XP.
        
        struct weapon{
            std::string weaponName;
            double weaponDamageLow; // the  lowest value of the weapons damage
            double weaponDamageHigh;// the highest value of the weapons damage
        };

        void Human() {  //Kyle
            name = username;
            race = "Human";
            baseHealth = 100;
            baseArmor = 10;
            baseMagicResistence = 5;
            baseAbility = 1
            baseAgility = 10
            baseDamage = 5;
            level = 0;
        }

        void increaseXP(){  //Kyle
            int levels = 100;
            int firstLevel = 500;
            int lastLevel = 1000000;

            double B = log((double)lastLevel / firstLevel) / (levels - 1);
            double A = (double)firstLevel / (exp(B) - 1.0);

            for (int i = 1; i <= levels; i++){
                int oldXP = round(A * exp(B * (i - 1)));
                int newXP = round(A * exp(B * i));
                std::cout << i << " " << (newXP - oldXP) << std::endl;
            }
        }

};