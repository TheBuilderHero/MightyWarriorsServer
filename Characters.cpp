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
    baseStealth = 5;
    level = 0;
}

void Characters::Elf(string username) {
    name = username;
    race = "Elf";
    baseHealth = 100;
    baseArmor = 5;
    baseMagicResistance = 10;
    baseMagicDamage = 15;
    baseAgility = 25;
    basePhysicalDamage = 5;
    baseStealth = 10;
    level = 0;
}

void Characters::Dino(string username) {
    name = username;
    race = "Dino";
    baseHealth = 100;
    baseArmor = 15;
    baseMagicResistance = 5;
    baseMagicDamage = 20;
    baseAgility = 8;
    basePhysicalDamage = 15;
    baseStealth = 1;
    level = 0;
}

void Characters::Dryad(string username) {
    name = username;
    race = "Dryad";
    baseHealth = 100;
    baseArmor = 5;
    baseMagicResistance = 20;
    baseMagicDamage = 20;
    baseAgility = 20;
    basePhysicalDamage = 5;
    baseStealth = 10;
    level = 0;
}

void Characters::Ghost(string username) {
    name = username;
    race = "Ghost";
    baseHealth = 100;
    baseArmor = 2;
    baseMagicResistance = 20;
    baseMagicDamage = 20;
    baseAgility = 15;
    basePhysicalDamage = 5;
    baseStealth = 30;
    level = 0;
}