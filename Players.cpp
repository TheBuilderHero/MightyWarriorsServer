#include <iostream>
#include <string>

#include "Players.h"

using namespace std;

string Players::getHealthStat(std::string username, int baseHealth, int bonusHealth){ //this funciton calculates to total health stat of a user and makes it into a string to be sent to the client
    int totalHealthValue = baseHealth + bonusHealth;
    return to_string(totalHealthValue);
}
string Players::getPhysicalDamageStat(std::string username, int basePhysicalDamage, int bonusPhysicalDamage){ //this funciton calculates to total Physical Damage stat of a user and makes it into a string to be sent to the client
    int totalPhysicalDamageValue = basePhysicalDamage + bonusPhysicalDamage;
    return to_string(totalPhysicalDamageValue);
}
string Players::getMagicDamageStat(std::string username, int baseMagicDamage, int bonusMagicDamage){ //this funciton calculates to total MagicDamage stat of a user and makes it into a string to be sent to the client
    int totalMagicDamageValue = baseMagicDamage + bonusMagicDamage;
    return to_string(totalMagicDamageValue);
}
string Players::getArmorStat(std::string username, int baseArmor, int bonusArmor){//this funciton calculates to total Armor stat of a user and makes it into a string to be sent to the client
    int totalArmorValue = baseArmor + bonusArmor;
    return to_string(totalArmorValue);
}
string Players::getMagicResistanceStat(std::string username, int baseMagicResistance, int bonusMagicResistance){//this funciton calculates to total MagicResistance stat of a user and makes it into a string to be sent to the client
    int totalMagicResistanceValue = baseMagicResistance + bonusMagicResistance;
    return to_string(totalMagicResistanceValue);
}
string Players::getAgilityStat(std::string username, int baseAgility, int bonusAgility){//this funciton calculates to total Agility stat of a user and makes it into a string to be sent to the client
    int totalAgilityValue = baseAgility + bonusAgility;
    return to_string(totalAgilityValue);
}