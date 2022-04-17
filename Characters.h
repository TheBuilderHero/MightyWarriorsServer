#include <iostream>
#include <string>


#pragma once

class Characters {
    private:
        std::string name; // in the case of Enemies we will give them names - for players it will be their username
        std::string race; // is one of the following: human - elf - dino - dryad - ghost
        
    public:
        //these probably need to be made private:
        int baseHealth, baseArmor, baseMagicResistance, baseMagicDamage, baseAgility, basePhysicalDamage, baseStealth, baseStamina, baseMana; //base stats
        //every time you make a physical or magical attack it effects the stamina or mana (magical is mana). This means that your attacks will be less consistant the lower these stats become.
        
        int level; // What level the Character is currently at, XP will only be declared for the player so that they can level up.  Enemies do not need XP.


        //The following are the race constants:
        const std::string RACE_HUMAN = "human", RACE_ELF = "elf", RACE_DINO = "dino", RACE_DRYAD = "dryad", RACE_GHOST = "ghost"; //these are the values stored in every uesr file so to know their chosen race
        struct weapon{
            std::string weaponName;
            int weaponDamageMin; // the  lowest value of the weapons damage
            int weaponDamageMax;// the highest value of the weapons damage
        };
        void pullRaceStats(std::string race, std::string username); // this function is for getting the stats of 
        void human(std::string username);
        void elf(std::string username);
        void dino(std::string username);
        void dryad(std::string username);
        void ghost(std::string username);
};