#include <iostream>
#include <string>
#include <fstream>

#include "Players.h"
#include "Cipher.h"

using namespace std;

std::string Players::getPlayerRace(std::string username, int raceChoice){ //returns the user's race
    switch (raceChoice)
    {
    case 1: //human selected
        return RACE_HUMAN;
        break;
    case 2: //Ghost selected
        return RACE_GHOST;
        break;
    case 3: //Dino Selected
        return RACE_DINO;
        break;
    case 4: //Elf selected
        return RACE_ELF;
        break;
    case 5: //Dryad selected
        return RACE_DRYAD;
        break;
    default:
        return RACE_HUMAN;
        break;
    }
}
std::string Players::getPlayerRace(std::string username){ //returns the user's race
    Cipher code;
    ifstream raceInfo;
    code.userDataDeliminationRead(2, username);
    return code.getItem(2);
}
string Players::getHealthStat(std::string username, int baseHealth, int bonusHealth){ //this funciton calculates to total health stat of a user and makes it into a string to be sent to the client
    int totalHealthValue = baseHealth + bonusHealth;
    return to_string(totalHealthValue);
}
string Players::getHealthStat(std::string username){ //this funciton calculates to total Health stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher code;
    Players players;
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalHealthValue = characters.baseHealth + stoi(code.getItem(2));
    return to_string(totalHealthValue);
}
string Players::getPhysicalDamageStat(std::string username, int basePhysicalDamage, int bonusPhysicalDamage){ //this funciton calculates to total Physical Damage stat of a user and makes it into a string to be sent to the client
    //need to replace this function with the overload of this below. Request action uses this one when it should use the other.
    int totalPhysicalDamageValue = basePhysicalDamage + bonusPhysicalDamage;
    return to_string(totalPhysicalDamageValue);
}
string Players::getPhysicalDamageStat(std::string username){ //this funciton calculates to total Physical Damage stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher code;
    Players players;
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalPhysicalDamageValue = characters.basePhysicalDamage + stoi(code.getItem(5));
    return to_string(totalPhysicalDamageValue);
}
string Players::getMagicDamageStat(std::string username, int baseMagicDamage, int bonusMagicDamage){ //this funciton calculates to total MagicDamage stat of a user and makes it into a string to be sent to the client
    //need to replace this function with the overload of this below. Request action uses this one when it should use the other.
    int totalMagicDamageValue = baseMagicDamage + bonusMagicDamage;
    return to_string(totalMagicDamageValue);
}
string Players::getMagicDamageStat(std::string username){ //this funciton calculates to total Magic Damage stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher code;
    Players players;
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalMagicDamageValue = characters.baseMagicDamage + stoi(code.getItem(6));
    return to_string(totalMagicDamageValue);
}
string Players::getArmorStat(std::string username, int baseArmor, int bonusArmor){//this funciton calculates to total Armor stat of a user and makes it into a string to be sent to the client
    int totalArmorValue = baseArmor + bonusArmor;
    return to_string(totalArmorValue);
}
string Players::getArmorStat(std::string username){ //this funciton calculates to total Armor stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher code;
    Players players;
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalArmorValue = characters.baseArmor + stoi(code.getItem(3));
    return to_string(totalArmorValue);
}
string Players::getMagicResistanceStat(std::string username, int baseMagicResistance, int bonusMagicResistance){//this funciton calculates to total MagicResistance stat of a user and makes it into a string to be sent to the client
    int totalMagicResistanceValue = baseMagicResistance + bonusMagicResistance;
    return to_string(totalMagicResistanceValue);
}
string Players::getMagicResistanceStat(std::string username){ //this funciton calculates to total MagicResistance stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher code;
    Players players;
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalMagicResistanceValue = characters.baseMagicResistance + stoi(code.getItem(4));
    return to_string(totalMagicResistanceValue);
}
string Players::getAgilityStat(std::string username, int baseAgility, int bonusAgility){//this funciton calculates to total Agility stat of a user and makes it into a string to be sent to the client
    int totalAgilityValue = baseAgility + bonusAgility;
    return to_string(totalAgilityValue);
}
string Players::getAgilityStat(std::string username){//this funciton calculates to total Agility stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher code;
    Players players;
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalAgilityValue = characters.baseAgility + stoi(code.getItem(7));
    return to_string(totalAgilityValue);
}
string Players::getStealthStat(std::string username, int baseStealth, int bonusStealth){//this funciton calculates to total Stealth stat of a user and makes it into a string to be sent to the client
    int totalStealthValue = baseStealth + bonusStealth;
    return to_string(totalStealthValue);
}
string Players::getStealthStat(std::string username){//this funciton calculates to total Stealth stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher code;
    Players players;
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalStealthValue = characters.baseStealth + stoi(code.getItem(8));
    return to_string(totalStealthValue);
}
string Players::getStaminaStat(std::string username, int baseStamina, int bonusStamina){//this funciton calculates to total Stamina stat of a user and makes it into a string to be sent to the client
    int totalStaminaValue = baseStamina + bonusStamina;
    return to_string(totalStaminaValue);
}
string Players::getStaminaStat(std::string username){//this funciton calculates to total Stamina stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher code;
    Players players;
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalStaminaValue = characters.baseStamina + stoi(code.getItem(9));
    return to_string(totalStaminaValue);
}
string Players::getManaStat(std::string username, int baseMana, int bonusMana){//this funciton calculates to total Mana stat of a user and makes it into a string to be sent to the client
    int totalManaValue = baseMana + bonusMana;
    return to_string(totalManaValue);
}
string Players::getManaStat(std::string username){//this funciton calculates to total Mana stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher code;
    Players players;
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalManaValue = characters.baseMana + stoi(code.getItem(10));
    return to_string(totalManaValue);
}