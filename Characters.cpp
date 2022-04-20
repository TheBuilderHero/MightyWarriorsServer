#include <iostream>

#include "Characters.h"
#include "Cipher.h"

using namespace std;

void Characters::pullRaceStats(string race, string username){//sets the stats in the character class for the specific race of the player
    if(race == RACE_HUMAN) human(username);
    if(race == RACE_ELF) elf(username);
    if(race == RACE_DINO) dino(username);
    if(race == RACE_DRYAD) dryad(username);
    if(race == RACE_GHOST) ghost(username);
}


void Characters::human(string username) {  //Kyle
    name = username;
    race = RACE_HUMAN;
    baseHealth = 100;
    baseArmor = 10;
    baseMagicResistance = 5;
    baseMagicDamage = 1;
    baseAgility = 10;
    basePhysicalDamage = 5;
    baseStealth = 5;
    baseStamina = 0;
    baseMana = 0;
    level = 0;
}

void Characters::elf(string username) {
    name = username;
    race = RACE_ELF;
    baseHealth = 100;
    baseArmor = 5;
    baseMagicResistance = 10;
    baseMagicDamage = 15;
    baseAgility = 25;
    basePhysicalDamage = 5;
    baseStealth = 10;
    baseStamina = 0;
    baseMana = 0;
    level = 0;
}

void Characters::dino(string username) {
    name = username;
    race = RACE_DINO;
    baseHealth = 100;
    baseArmor = 15;
    baseMagicResistance = 5;
    baseMagicDamage = 20;
    baseAgility = 8;
    basePhysicalDamage = 15;
    baseStealth = 1;
    baseStamina = 0;
    baseMana = 0;
    level = 0;
}

void Characters::dryad(string username) {
    name = username;
    race = RACE_DRYAD;
    baseHealth = 100;
    baseArmor = 5;
    baseMagicResistance = 20;
    baseMagicDamage = 20;
    baseAgility = 20;
    basePhysicalDamage = 5;
    baseStealth = 10;
    baseStamina = 0;
    baseMana = 0;
    level = 0;
}

void Characters::ghost(string username) {
    name = username;
    race = RACE_GHOST;
    baseHealth = 100;
    baseArmor = 2;
    baseMagicResistance = 20;
    baseMagicDamage = 20;
    baseAgility = 15;
    basePhysicalDamage = 5;
    baseStealth = 30;
    baseStamina = 0;
    baseMana = 0;
    level = 0;
}