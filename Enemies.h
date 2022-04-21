#include <string>
#include "Characters.h"
#include "PlayerElements/Kit.h"

#pragma once

class Enemies : Characters {
    private:
        
        const int MUTANT_ELF = 1, VOID_CAT = 2, HIGHWAY_ROBBER = 3, ORC_ENEMY = 4, SASQUATCH_ENEMY = 5, SKUNK_ENEMY = 6, MUTANT_SKUNK = 7, GIANT_RACCOON = 8, 
        EVIL_WIZARD = 9, WITCH_ENEMY = 10, MUTANT_GHOST = 11, WERE_WOLF = 12; //these are identifiers
        int enemyNum;
        std::string displayName;
        double xpDrop;

        //these constants take after the ones we use in the Kit class:
        Kit kitInit;
        const std::string DAMAGETYPE_MAGIC = kitInit.getDAMAGETYPE_MAGIC(), DAMAGETYPE_PHYSICAL = kitInit.getDAMAGETYPE_PHYSICAL(), DAMAGETYPE_TRUE = kitInit.getDAMAGETYPE_TRUE();
    public:
        int enemyChoiceGetStat(int enemyChoice, int returnType = 0, int enemyLevel = 1); //returns amount of health/armor/magicResistance/etc...
        std::string getEnemyName(int enemyChoice);
        double getXPDrop(int enemyChoice, int enemyLevel);
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

        //get the type of damage constant:
        std::string getDAMAGETYPE_MAGIC() { return DAMAGETYPE_MAGIC; }
        std::string getDAMAGETYPE_PHYSICAL() { return DAMAGETYPE_PHYSICAL; }
        std::string getDAMAGETYPE_TRUE() { return DAMAGETYPE_TRUE; }
};