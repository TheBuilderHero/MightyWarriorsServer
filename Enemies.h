#include <string>
#include "Characters.h"

#pragma once

class Enemies : Characters {
    public:
        std::string displayName;
        double xpDrop;
        int enemyChoiceGetStat(int enemyChoice, int returnType = 0, int enemyLevel = 1); //returns amount of health/armor/magicResistance/etc...
        std::string getEnemyName(int enemyChoice);
        void mutantElf();
        void voidCat();
};