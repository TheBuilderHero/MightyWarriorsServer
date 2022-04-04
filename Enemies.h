#include <string>
#include "Characters.h"

#pragma once

class Enemies : Characters {
    public:
        double xpDrop;
        int enemyChoice(int enemyChoice, int returnType); //returns amount of health/armor/magicResistance/etc...
        void mutantElf();
};