#include <string>

#pragma once

class Kit{
    private:
    const std::string KIT_TANK = "tank", KIT_ASSASIN = "assasin", KIT_ARCHER = "archer", KIT_MAGE = "mage", KIT_NINJA = "ninja", KIT_MENTALIST = "mentalist";
    std::string kit = KIT_TANK;
    int kitHealth = 40, kitPhysicalDamage = 10, kitArmor = 2, kitMagicDamage = 5, kitMagicResistance = 5, kitAgility = 0, kitStealth = 0, kitMind = 0, kitPsychicDamage = 0; //does not have any
    const std::string DAMAGETYPE_MAGIC = "Magic", DAMAGETYPE_PHYSICAL = "Physical", DAMAGETYPE_PSYCHIC = "Psychic", DAMAGETYPE_TRUE = "True";
    std::string qAbilityDamageType, wAbilityDamageType, eAbilityDamageType, rAbilityDamageType;
    
    public:
    std::string getPlayerKit(std::string username, int kitChoice); //this helps with the inital account setup.
    std::string getPlayerKit(std::string username); //overidden for the sake of getting the players kit after setting it.
    void pullKitStats(std::string race, std::string username);
    void pullKitStats(std::string username);

    //get the individual stats:
    int getHealth(){ return kitHealth; }
    int getPhysicalDamage(){ return kitPhysicalDamage; }
    int getArmor(){ return kitArmor; }
    int getMagicDamage(){ return kitMagicDamage; }
    int getMagicResistance (){ return kitMagicResistance; }
    int getAgility(){ return kitAgility; }
    int getStealth(){ return kitStealth; }
    int getMind() { return kitMind; }
    int getPsychicDamage(){ return kitPsychicDamage; }

    std::string getRaceDamageTypeForAbility(std::string username, char abilityLetter);//this function returns the type of damage a user inflicts based on their kit
    void tank();
    void assasin();
    void archer();
    void mage();
    void ninja();
    void mentalist();

    std::string getDAMAGETYPE_MAGIC(){ return DAMAGETYPE_MAGIC; }
    std::string getDAMAGETYPE_PHYSICAL(){ return DAMAGETYPE_PHYSICAL; }
    std::string getDAMAGETYPE_PSYCHIC(){ return DAMAGETYPE_PSYCHIC; }
    std::string getDAMAGETYPE_TRUE(){ return DAMAGETYPE_TRUE; }
};