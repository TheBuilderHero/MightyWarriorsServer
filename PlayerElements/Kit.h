#include <string>

#pragma once

class Kit{
    private:
    const std::string KIT_TANK = "tank", KIT_ASSASIN = "assasin", KIT_ARCHER = "archer", KIT_MAGE = "mage", KIT_NINJA = "ninja";
    std::string kit = KIT_TANK;
    int kitHealth = 40, kitPhysicalDamage = 10, kitArmor = 2, kitMagicDamage = 5, kitMagicResistance = 5, kitAgility = 0, kitStealth = 0; //does not have any
    const std::string DAMAGETYPE_MAGIC = "magic", DAMAGETYPE_PHYSICAL = "physical", DAMAGETYPE_TRUE = "true";
    std::string qAbilityDamageType, wAbilityDamageType, eAbilityDamageType, rAbilityDamageType;
    
    public:
    std::string getPlayerKit(std::string username, int kitChoice); //this helps with the inital account setup.
    std::string getPlayerKit(std::string username); //overidden for the sake of getting the players kit after setting it.
    void pullKitStats(std::string race, std::string username);
    std::string getRaceDamageTypeForAbility(std::string username, char abilityLetter);//this function returns the type of damage a user inflicts based on their kit
    void tank();
    void assasin();
    void archer();
    void mage();
    void ninja();
};