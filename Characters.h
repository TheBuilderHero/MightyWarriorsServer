#include <iostream>
#include <string>


#pragma once

class Characters {
    private:
        std::string name; // in the case of Enemies we will give them names - for players it will be their username
        std::string race; // is one of the following: human - elf - dino - dryad - ghost
        
        //these probably need to be made private:
        int baseHealth, baseArmor, baseMagicResistance, baseMagicDamage, baseAgility, basePhysicalDamage, baseStealth, baseStamina, baseMana, baseMind; //base stats
        //every time you make a physical or magical attack it effects the stamina or mana (magical is mana). This means that your attacks will be less consistant the lower these stats become.
        
        int level; // What level the Character is currently at, XP will only be declared for the player so that they can level up.  Enemies do not need XP.
    public:
        


        //The following are the race constants:
        const std::string RACE_HUMAN = "human", RACE_ELF = "elf", RACE_DINO = "dino", RACE_DRYAD = "dryad", RACE_GHOST = "ghost"
        , RACE_MOP = "mop"; //these are the values stored in every uesr file so to know their chosen race
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
        void mop(std::string username);

        //return commands for stat variables:
        int getBaseHealth() { return baseHealth; }
        int getBaseArmor() { return baseArmor; }
        int getBaseMagicResistance() { return baseMagicResistance; }
        int getBaseMagicDamage() { return baseMagicDamage; }
        int getBaseAgility() { return baseAgility; }
        int getBasePhysicalDamage() { return basePhysicalDamage; }
        int getBaseStealth() { return baseStealth; }
        int getBaseStamina() { return baseStamina; }
        int getBaseMana() { return baseMana; }
        int getBaseMind() { return baseMind; }
        int getLevel() { return level; }

        //set commands for stat variables:
        void setBaseHealth(int newValue) { baseHealth = newValue; }
        void setBaseArmor(int newValue) { baseArmor = newValue; }
        void setBaseMagicResistance(int newValue) { baseMagicResistance = newValue; }
        void setBaseMagicDamage(int newValue) { baseMagicDamage = newValue; }
        void setBaseAgility(int newValue) { baseAgility = newValue; }
        void setBasePhysicalDamage(int newValue) { basePhysicalDamage = newValue; }
        void setBaseStealth(int newValue) { baseStealth = newValue; }
        void setBaseStamina(int newValue) { baseStamina = newValue; }
        void setBaseMana(int newValue) { baseMana = newValue; }
        void setBaseMind(int newValue) { baseMind = newValue; }
        void setLevel(int newValue) { level = newValue; }
};