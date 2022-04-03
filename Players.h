#include <iostream>
#include <string>

#include "Characters.h"

#pragma once

class Players : Characters { //defining the player and all their caracteristics and items
    public:
        std::string getHealthStat(std::string username, int baseHealth, int bonusHealth);
        std::string getPhysicalDamageStat(std::string username, int basePhysicalDamage, int bonusPhysicalDamage);
        std::string getMagicDamageStat(std::string username, int baseMagicDamage, int bonusMagicDamage);
        std::string getArmorStat(std::string username, int baseArmor, int bonusArmor);
        std::string getMagicResistanceStat(std::string username, int baseMagicResistance, int bonusMagicResistance);
        std::string getAgilityStat(std::string username, int baseAgility, int bonusAgility);
};