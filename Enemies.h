#include <string>
#pragma once

using namespace std;

class Enemies {
    public:
        string name;
        int level;
        double baseHealth;
        double baseArmor;
        double baseMagicResistance;
        double baseDamage;
        void mutantElf();
};