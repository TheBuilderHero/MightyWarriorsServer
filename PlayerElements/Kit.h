#include <string>

#pragma once

class Kit{
    public:
    std::string KIT_TANK = "tank", KIT_ASSASIN = "assasin", KIT_ARCHER = "archer", KIT_MAGE = "mage", KIT_NINJA = "ninja";
    std::string kit = KIT_TANK;
    int kitHealth = 40;
    int kitPhysicalDamage = 10;
    int kitArmor = 2;
    int kitMagicDamage = 5;
    int kitMagicResistance = 5;
    int kitAgility = 0; //does not have any
    int kitStealth = 0; //does not have any
    void tank();
    void assasin();
    void archer();
    void wizard();
    void ninja();
};