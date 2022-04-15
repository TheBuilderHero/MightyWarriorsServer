#include <string>
#include "Characters.h"

#pragma once

class Enemies : Characters {
    private:
        const int MUTANT_ELF = 1, VOID_CAT = 2, HIGHWAY_ROBBER = 3, ORC_ENEMY = 4, SASQUATCH_ENEMY = 5, SKUNK_ENEMY = 6, MUTANT_SKUNK = 7, GIANT_RACCOON = 8, 
        EVIL_WIZARD = 9, WITCH_ENEMY = 10, MUTANT_GHOST = 11, WERE_WOLF = 12; //these are identifiers
        int enemyNum;
        std::string displayName;
        double xpDrop;
    public:
        int enemyChoiceGetStat(int enemyChoice, int returnType = 0, int enemyLevel = 1); //returns amount of health/armor/magicResistance/etc...
        std::string getEnemyName(int enemyChoice);
        int getEnemyPickedFromName(std::string enemyName);
        void mutantElf();
        void voidCat();
        void highwayRobber();
        void orc();
        void sasquatch();
        void skunk();
        void mutantSkunk();
        void giantRaccoon();
        void evilWizard();
        void witch();
        void mutantGhost();
        void wereWolf();
};