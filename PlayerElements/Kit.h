#include <string>

#pragma once

class Kit{
    private:
    const std::string KIT_TANK = "tank", KIT_ASSASIN = "assasin", KIT_ARCHER = "archer", KIT_MAGE = "mage", KIT_NINJA = "ninja";
    std::string kit = KIT_TANK;
    int kitHealth = 40, kitPhysicalDamage = 10, kitArmor = 2, kitMagicDamage = 5, kitMagicResistance = 5, kitAgility = 0, kitStealth = 0; //does not have any
    
    public:
    std::string getPlayerKit(std::string username, int kitChoice);
    void pullKitStats(std::string race, std::string username);
    void tank();
    void assasin();
    void archer();
    void mage();
    void ninja();
};