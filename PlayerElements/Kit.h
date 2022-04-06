
#pragma once

class Kit{
    public:
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