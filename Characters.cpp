#include <iostream>
#include "Characters.h"

using namespace std;

void Characters::Human(string username) {  //Kyle
    name = username;
    race = "Human";
    baseHealth = 100;
    baseArmor = 10;
    baseMagicResistance = 5;
    baseMagicDamage = 1;
    baseAgility = 10;
    basePhysicalDamage = 5;
    level = 0;
}