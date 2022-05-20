#include <iostream>
#include <string>

#include "Characters.h"

#pragma once

class Players : Characters { //defining the player and all their caracteristics and items
    public:
        std::string getPlayerRace(std::string username); //return the string name of the players race
        std::string getPlayerRace(std::string username, int raceChoice); //used to determine the race chosen by client during account creation

        std::string getHealthStat(std::string username, int baseHealth, int bonusHealth); //returns total health stat for player with input of base and bonus health.
        std::string getHealthStat(std::string username); //returns total health stat for player with input of base and bonus health.

        std::string getPhysicalDamageStat(std::string username, int basePhysicalDamage, int bonusPhysicalDamage);//returns total PhysicalDamage stat for player with input of base and bonus PhysicalDamage.
        std::string getPhysicalDamageStat(std::string username);

        std::string getMagicDamageStat(std::string username, int baseMagicDamage, int bonusMagicDamage);//returns total MagicDamage stat for player with input of base and bonus MagicDamage.
        std::string getMagicDamageStat(std::string username);

        std::string getArmorStat(std::string username, int baseArmor, int bonusArmor);//returns total Armor stat for player with input of base and bonus Armor.
        std::string getArmorStat(std::string username);//returns total Armor stat for player with input of base and bonus Armor.

        std::string getMagicResistanceStat(std::string username, int baseMagicResistance, int bonusMagicResistance);//returns total MagicResistance stat for player with input of base and bonus MagicResistance.
        std::string getMagicResistanceStat(std::string username);//returns total MagicResistance stat for player with input of base and bonus MagicResistance.

        std::string getAgilityStat(std::string username, int baseAgility, int bonusAgility);//returns total Agility stat for player with input of base and bonus Agility.
        std::string getAgilityStat(std::string username);

        std::string getStealthStat(std::string username, int baseStealth, int bonusStealth);//this funciton calculates to total Stealth stat of a user and makes it into a string to be sent to the client
        std::string getStealthStat(std::string username);

        std::string getStaminaStat(std::string username, int baseStamina, int bonusStamina);//this funciton calculates to total Stamina stat of a user and makes it into a string to be sent to the client
        std::string getStaminaStat(std::string username);

        std::string getManaStat(std::string username, int baseMana, int bonusMana);//this funciton calculates to total Mana stat of a user and makes it into a string to be sent to the client
        std::string getManaStat(std::string username);

        int getPlayerWeapon(std::string username, int tempWeaponChoice);

        int getLevel(std::string username);
        double getXP(std::string username);
        void levelUp(std::string username, int &playerLevel, double newXP);
        void updateXPAmount(std::string username, int playerLevel, double newXPAmount);
};