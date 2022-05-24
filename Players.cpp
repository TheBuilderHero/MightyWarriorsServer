#include <iostream>
#include <string>
#include <fstream>

#include "Players.h"
#include "Cipher.h"
#include "PlayerElements/Kit.h"
#include "PlayerElements/Weapons.h"

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
    Kit kit;
    kit.pullKitStats(username);
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalHealthValue = characters.getBaseHealth() /*+ stoi(code.getItem(2))*/ + kit.getHealth();
    return to_string(totalHealthValue);
}
string Players::getPhysicalDamageStat(std::string username, bool outputMinAndMaxString){ //this funciton calculates to total Physical Damage stat of a user and makes it into a string to be sent to the client
    if (outputMinAndMaxString){ //outputs a string showing the min to max damage a player can hit for 
        Characters characters;
        Cipher code;
        Players players;
        Kit kit;
        kit.pullKitStats(username);
        Weapons weapon(username);
        code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int totalPhysicalDamageValue = characters.getBasePhysicalDamage() + stoi(code.getItem(5)) + kit.getPhysicalDamage();
        return (to_string(totalPhysicalDamageValue + weapon.getPhysicalDamageMin()) + " - " + to_string(totalPhysicalDamageValue + weapon.getPhysicalDamageMax()));
    } else { 
        Characters characters;
        Cipher code;
        Players players;
        Kit kit;
        kit.pullKitStats(username);
        Weapons weapon(username);
        code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int totalPhysicalDamageValue = characters.getBasePhysicalDamage() + stoi(code.getItem(5)) + kit.getPhysicalDamage() + weapon.getPhysicalDamage();
        return to_string(totalPhysicalDamageValue);
    }
    
}
string Players::getMagicDamageStat(std::string username, bool outputMinAndMaxString){ //this funciton calculates to total Magic Damage stat of a user and makes it into a string to be sent to the client
    if (outputMinAndMaxString){ //outputs a string showing the min to max damage a player can hit for 
        Characters characters;
        Cipher code;
        Players players;
        Kit kit;
        kit.pullKitStats(username);
        Weapons weapon(username);
        code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        int statMagicDamage = stoi(code.getItem(6));
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int totalMagicDamageValue = characters.getBaseMagicDamage() + statMagicDamage + kit.getMagicDamage();
        return (to_string(totalMagicDamageValue + weapon.getMagicDamageMin()) + " - " + to_string(totalMagicDamageValue + weapon.getMagicDamageMax()));
    } else {
        Characters characters;
        Cipher code;
        Players players;
        Kit kit;
        kit.pullKitStats(username);
        Weapons weapon(username);
        code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        int statMagicDamage = stoi(code.getItem(6));
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int totalMagicDamageValue = characters.getBaseMagicDamage() + statMagicDamage + kit.getMagicDamage() + weapon.getMagicDamage();
        return to_string(totalMagicDamageValue);
    }
}
string Players::getArmorStat(std::string username, int baseArmor, int bonusArmor){//this funciton calculates to total Armor stat of a user and makes it into a string to be sent to the client
    int totalArmorValue = baseArmor + bonusArmor;
    return to_string(totalArmorValue);
}
string Players::getArmorStat(std::string username){ //this funciton calculates to total Armor stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher code;
    Players players;
    Kit kit;
    kit.pullKitStats(username);
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalArmorValue = characters.getBaseArmor() + stoi(code.getItem(3)) + kit.getArmor();
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
    Kit kit;
    kit.pullKitStats(username);
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalMagicResistanceValue = characters.getBaseMagicResistance() + stoi(code.getItem(4)) + kit.getMagicResistance();
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
    Kit kit;
    kit.pullKitStats(username);
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalAgilityValue = characters.getBaseAgility() + stoi(code.getItem(7)) + kit.getAgility();
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
    Kit kit;
    kit.pullKitStats(username);
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalStealthValue = characters.getBaseStealth() + stoi(code.getItem(8)) + kit.getStealth();
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
    Kit kit;
    kit.pullKitStats(username);
    code.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int totalStaminaValue = characters.getBaseStamina() + stoi(code.getItem(9));
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
    int totalManaValue = characters.getBaseMana() + stoi(code.getItem(10));
    return to_string(totalManaValue);
}
int Players::getLevel(string username){//pulls level from user's file to return
    int playerLevel;
    Cipher code;
    code.userDataDeliminationRead(2, username); 
    return playerLevel = stoi(code.getItem(4));
}
double Players::getXP(string username){
    double playerCurrentXP;
    Cipher code;
    code.userDataDeliminationRead(2, username); //pulls XP from user's file to return
    return playerCurrentXP = stoi(code.getItem(5));
}
void Players::levelUp(string username, int &playerLevel, double newXPAmount){
    Cipher code;
    Players player;
    Kit kit;
    //since we are re-writing the file we need the following:
    string playerRace = player.getPlayerRace(username); //get the players kit
    string playerKit = kit.getPlayerKit(username); //get the players race
    playerLevel++; //increase player level by one
    code.userDataDeliminationWrite(4, username, playerRace, playerKit, to_string(playerLevel), to_string(newXPAmount));
}
void Players::updateXPAmount(string username, int playerLevel, double newXPAmount){
    Players player;
    Kit kit;
    Cipher code;
    //since we are re-writing the file we need the following:
    string playerRace = player.getPlayerRace(username); //get the players kit
    string playerKit = kit.getPlayerKit(username); //get the players race
    code.userDataDeliminationWrite(4, username, playerRace, playerKit, to_string(playerLevel), to_string(newXPAmount)); //save the new XP amount along with resaving race, kit, level
}