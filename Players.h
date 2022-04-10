#include <iostream>
#include <string>

#include "Characters.h"

#pragma once

class Players : Characters { //defining the player and all their caracteristics and items
    public:
        std::string getPlayerRace(std::string username); //return the string name of the players race
        std::string getPlayerRace(std::string username, int raceChoice); //used to determine the race chosen by client during account creation

        std::string getHealthStat(std::string username, int baseHealth, int bonusHealth);
        std::string getPhysicalDamageStat(std::string username, int basePhysicalDamage, int bonusPhysicalDamage);
        std::string getPhysicalDamageStat(std::string username);
        std::string getMagicDamageStat(std::string username, int baseMagicDamage, int bonusMagicDamage);
        std::string getMagicDamageStat(std::string username);
        std::string getArmorStat(std::string username, int baseArmor, int bonusArmor);
        std::string getMagicResistanceStat(std::string username, int baseMagicResistance, int bonusMagicResistance);
        std::string getAgilityStat(std::string username, int baseAgility, int bonusAgility);
        std::string getStealthStat(std::string username, int baseStealth, int bonusStealth);//this funciton calculates to total Stealth stat of a user and makes it into a string to be sent to the client
        std::string getStaminaStat(std::string username, int baseStamina, int bonusStamina);//this funciton calculates to total Stamina stat of a user and makes it into a string to be sent to the client
        std::string getManaStat(std::string username, int baseMana, int bonusMana);//this funciton calculates to total Mana stat of a user and makes it into a string to be sent to the client
};