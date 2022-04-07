#include <string>
#include "Characters.h"

#pragma once

class Enemies : Characters {
    public:
        double xpDrop;
        int enemyChoice(int enemyChoice, int returnType, int enemyLevel = 1); //returns amount of health/armor/magicResistance/etc...
        void mutantElf();
        void voidCat();
};