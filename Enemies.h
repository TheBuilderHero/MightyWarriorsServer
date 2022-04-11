#include <string>
#include "Characters.h"

#pragma once

class Enemies : Characters {
    public:
        const int MUTANT_ELF = 1, VOID_CAT = 2; //these are identifiers
        int enemyNum;
        std::string displayName;
        double xpDrop;
        int enemyChoiceGetStat(int enemyChoice, int returnType = 0, int enemyLevel = 1); //returns amount of health/armor/magicResistance/etc...
        std::string getEnemyName(int enemyChoice);
        int getEnemyPickedFromName(std::string enemyName);
        void mutantElf();
        void voidCat();
};