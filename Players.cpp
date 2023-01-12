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
    case 100: //mop slelected
        return RACE_MOP;
        break;
    default:
        return RACE_HUMAN;
        break;
    }
}
std::string Players::getPlayerRace(std::string username){ //returns the user's race
    Cipher tempCode;
    ifstream raceInfo;
    tempCode.userDataDeliminationRead(2, username);
    return tempCode.getItem(2);
}
string Players::getHealthStat(std::string username, int baseHealth, int bonusHealth){ //this funciton calculates to total health stat of a user and makes it into a string to be sent to the client
    int totalHealthValue = baseHealth + bonusHealth;
    return to_string(totalHealthValue);
}
string Players::getHealthStat(std::string username){ //this funciton calculates to total Health stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher tempCode;
    Players players;
    Kit kit;
    kit.pullKitStats(username);
    tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int fileHealth;
    try{
        fileHealth = stoi(tempCode.getItem(2));
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getHealthStat()\"" << endl;
    }
    int totalHealthValue = characters.getBaseHealth() + fileHealth + kit.getHealth();
    return to_string(totalHealthValue);
}
string Players::getPhysicalDamageStat(std::string username, bool outputMinAndMaxString){ //this funciton calculates to total Physical Damage stat of a user and makes it into a string to be sent to the client
    if (outputMinAndMaxString){ //outputs a string showing the min to max damage a player can hit for 
        Characters characters;
        Cipher tempCode;
        Players players;
        Kit kit;
        kit.pullKitStats(username);        
        Weapons weapon(username, false);
        tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int filedamage;
        try{
            filedamage = stoi(tempCode.getItem(5));
        } catch(std::invalid_argument){
            cout << "failed stoi \"string Players::getPhysicalDamageStat()\"" << endl;
        }
        int totalPhysicalDamageValue = characters.getBasePhysicalDamage() + filedamage + kit.getPhysicalDamage();
        cout << "PhysicalDamage" << endl;
        cout << "total: " << totalPhysicalDamageValue << endl;
        cout << "weapon min: " << weapon.getPhysicalDamageMin() << endl;
        cout << "weapon max: " << weapon.getPhysicalDamageMax() << endl;
        return (to_string(totalPhysicalDamageValue + weapon.getPhysicalDamageMin()) + " - " + to_string(totalPhysicalDamageValue + weapon.getPhysicalDamageMax()));
    } else { 
        Characters characters;
        Cipher tempCode;
        Players players;
        Kit kit;
        kit.pullKitStats(username);
        Weapons weapon(username);
        tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int filedamage;
        try{
            filedamage = stoi(tempCode.getItem(5));
        } catch(std::invalid_argument){
            cout << "failed stoi \"string Players::getPhysicalDamageStat()\"" << endl;
        }
        int totalPhysicalDamageValue = characters.getBasePhysicalDamage() + filedamage + kit.getPhysicalDamage() + weapon.getPhysicalDamage();
        return to_string(totalPhysicalDamageValue);
    }
    
}
string Players::getMagicDamageStat(std::string username, bool outputMinAndMaxString){ //this funciton calculates to total Magic Damage stat of a user and makes it into a string to be sent to the client
    if (outputMinAndMaxString){ //outputs a string showing the min to max damage a player can hit for 
        Characters characters;
        Cipher tempCode;
        Players players;
        Kit kit;
        kit.pullKitStats(username);
        Weapons weapon(username, false);
        tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        int statMagicDamage;
        try{
            statMagicDamage = stoi(tempCode.getItem(6));
        } catch(std::invalid_argument){
            cout << "failed stoi \"string Players::getMagicDamageStat()\"" << endl;
        }
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int totalMagicDamageValue = characters.getBaseMagicDamage() + statMagicDamage + kit.getMagicDamage();
        cout << "MagicDamage" << endl;
        cout << "total: " << totalMagicDamageValue << endl;
        cout << "weapon min: " << weapon.getMagicDamageMin() << endl;
        cout << "weapon max: " << weapon.getMagicDamageMax() << endl;
        return (to_string(totalMagicDamageValue + weapon.getMagicDamageMin()) + " - " + to_string(totalMagicDamageValue + weapon.getMagicDamageMax()));
    } else {
        Characters characters;
        Cipher tempCode;
        Players players;
        Kit kit;
        kit.pullKitStats(username);
        Weapons weapon(username);
        tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        int statMagicDamage;
        try{
            statMagicDamage = stoi(tempCode.getItem(6));
        } catch(std::invalid_argument){
            cout << "failed stoi \"string Players::getMagicDamageStat()\"" << endl;
        }
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int totalMagicDamageValue = characters.getBaseMagicDamage() + statMagicDamage + kit.getMagicDamage() + weapon.getMagicDamage();
        return to_string(totalMagicDamageValue);
    }
}
string Players::getPsychicDamageStat(std::string username, bool outputMinAndMaxString){ //this funciton calculates to total Magic Damage stat of a user and makes it into a string to be sent to the client
    if (outputMinAndMaxString){ //outputs a string showing the min to max damage a player can hit for 
        Characters characters;
        Cipher tempCode;
        Players players;
        Kit kit;
        kit.pullKitStats(username);
        Weapons weapon(username, false);
        tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        int statPsychicDamage;
        try{
            statPsychicDamage = stoi(tempCode.getItem(12));
        } catch(std::invalid_argument){
            cout << "failed stoi \"string Players::getPyschicDamageStat()\"" << endl;
            statPsychicDamage = 0;
        }
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int totalPsychicDamageValue = characters.getBasePsychicDamage() + statPsychicDamage + kit.getPsychicDamage();
        cout << "PsychicDamage" << endl;
        cout << "total: " << totalPsychicDamageValue << endl;
        cout << "weapon min: " << weapon.getPsychicDamageMin() << endl;
        cout << "weapon max: " << weapon.getPsychicDamageMax() << endl;
        return (to_string(totalPsychicDamageValue + weapon.getPsychicDamageMin()) + " - " + to_string(totalPsychicDamageValue + weapon.getPsychicDamageMax()));
    } else {
        Characters characters;
        Cipher tempCode;
        Players players;
        Kit kit;
        kit.pullKitStats(username);
        Weapons weapon(username);
        tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        int statPsychicDamage;
        try{
            statPsychicDamage = stoi(tempCode.getItem(12));
        } catch(std::invalid_argument){
            cout << "failed stoi \"string Players::getPyschicDamageStat()\"" << endl;
            statPsychicDamage = 0;
        }
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int totalPsychicDamageValue = characters.getBasePsychicDamage() + statPsychicDamage + kit.getPsychicDamage() + weapon.getPsychicDamage();
        return to_string(totalPsychicDamageValue);
    }
}
string Players::getArmorStat(std::string username, int baseArmor, int bonusArmor){//this funciton calculates to total Armor stat of a user and makes it into a string to be sent to the client
    int totalArmorValue = baseArmor + bonusArmor;
    return to_string(totalArmorValue);
}
string Players::getArmorStat(std::string username){ //this funciton calculates to total Armor stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher tempCode;
    Players players;
    Kit kit;
    kit.pullKitStats(username);
    tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statArmor;
    try{
        statArmor = stoi(tempCode.getItem(3));
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getArmorStat()\"" << endl;
    }
    int totalArmorValue = characters.getBaseArmor() + statArmor + kit.getArmor();
    return to_string(totalArmorValue);
}
string Players::getMagicResistanceStat(std::string username, int baseMagicResistance, int bonusMagicResistance){//this funciton calculates to total MagicResistance stat of a user and makes it into a string to be sent to the client
    int totalMagicResistanceValue = baseMagicResistance + bonusMagicResistance;
    return to_string(totalMagicResistanceValue);
}
string Players::getMagicResistanceStat(std::string username){ //this funciton calculates to total MagicResistance stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher tempCode;
    Players players;
    Kit kit;
    kit.pullKitStats(username);
    tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statMRFile;
    try{
        statMRFile = stoi(tempCode.getItem(4));
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getMagicResistanceStat()\"" << endl;
    }
    int totalMagicResistanceValue = characters.getBaseMagicResistance() + statMRFile + kit.getMagicResistance();
    return to_string(totalMagicResistanceValue);
}
string Players::getAgilityStat(std::string username, int baseAgility, int bonusAgility){//this funciton calculates to total Agility stat of a user and makes it into a string to be sent to the client
    int totalAgilityValue = baseAgility + bonusAgility;
    return to_string(totalAgilityValue);
}
string Players::getAgilityStat(std::string username){//this funciton calculates to total Agility stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher tempCode;
    Players players;
    Kit kit;
    kit.pullKitStats(username);
    tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statAgilityFile;
    try{
        statAgilityFile = stoi(tempCode.getItem(7));
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getMagicResistanceStat()\"" << endl;
    }
    int totalAgilityValue = characters.getBaseAgility() + statAgilityFile + kit.getAgility();
    return to_string(totalAgilityValue);
}
string Players::getStealthStat(std::string username, int baseStealth, int bonusStealth){//this funciton calculates to total Stealth stat of a user and makes it into a string to be sent to the client
    int totalStealthValue = baseStealth + bonusStealth;
    return to_string(totalStealthValue);
}
string Players::getStealthStat(std::string username){//this funciton calculates to total Stealth stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher tempCode;
    Players players;
    Kit kit;
    kit.pullKitStats(username);
    tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statStealthFile;
    try{
        statStealthFile = stoi(tempCode.getItem(8));
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getStealthStat()\"" << endl;
    }
    int totalStealthValue = characters.getBaseStealth() + statStealthFile + kit.getStealth();
    return to_string(totalStealthValue);
}
string Players::getStaminaStat(std::string username, int baseStamina, int bonusStamina){//this funciton calculates to total Stamina stat of a user and makes it into a string to be sent to the client
    int totalStaminaValue = baseStamina + bonusStamina;
    return to_string(totalStaminaValue);
}
string Players::getStaminaStat(std::string username){//this funciton calculates to total Stamina stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher tempCode;
    Players players;
    Kit kit;
    kit.pullKitStats(username);
    tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statStaminaFile;
    try{
        statStaminaFile = stoi(tempCode.getItem(9));
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getStaminaStat()\"" << endl;
    }
    int totalStaminaValue = characters.getBaseStamina() + statStaminaFile;
    return to_string(totalStaminaValue);
}
string Players::getNaturalEnergyStat(std::string username, int baseMana, int bonusMana){//this funciton calculates to total NaturalEnergy stat of a user and makes it into a string to be sent to the client
    int totalManaValue = baseMana + bonusMana;
    return to_string(totalManaValue);
}
string Players::getNaturalEnergyStat(std::string username){//this funciton calculates to total NaturalEnergy stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher tempCode;
    Players players;
    tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statManaFile;
    try{
        statManaFile = stoi(tempCode.getItem(10));
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getMagicResistanceStat()\"" << endl;
    }
    int totalManaValue = characters.getBaseMana() + statManaFile;
    return to_string(totalManaValue);
}
string Players::getMindStat(std::string username, int baseMind, int bonusMind){//this funciton calculates to total NaturalEnergy stat of a user and makes it into a string to be sent to the client
    int totalMindValue = baseMind + bonusMind;
    return to_string(totalMindValue);
}
string Players::getMindStat(std::string username){//this funciton calculates to total NaturalEnergy stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher tempCode;
    Players players;
    tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statMindFile;
    try{
        statMindFile = stoi(tempCode.getItem(11));
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getMindStat()\"" << endl;
        statMindFile = 0;
    }
    int totalMindValue = characters.getBaseMind() + statMindFile;
    return to_string(totalMindValue);
}
int Players::getLevel(string username){//pulls level from user's file to return
    int playerLevel;
    Cipher tempCode;
    tempCode.userDataDeliminationRead(2, username);
    int level;
    try{
        level = stoi(tempCode.getItem(4));
    } catch(std::invalid_argument){
        cout << "failed stoi \"int Players::getLevel()\"" << endl;
    }
    return playerLevel = level;
}
double Players::getXP(string username){
    double playerCurrentXP;
    Cipher tempCode;
    tempCode.userDataDeliminationRead(2, username); //pulls XP from user's file to return
    int xP;
    try{
        xP = stoi(tempCode.getItem(5));
    } catch(std::invalid_argument){
        cout << "failed stoi \"double Players::getXP()\"" << endl;
    }
    return playerCurrentXP = xP;
}
void Players::levelUp(string username, int &playerLevel, double newXPAmount){
    Cipher tempCode;
    Players player;
    Kit kit;
    //since we are re-writing the file we need the following:
    string playerRace = player.getPlayerRace(username); //get the players kit
    string playerKit = kit.getPlayerKit(username); //get the players race
    playerLevel++; //increase player level by one
    tempCode.userDataDeliminationWrite(4, username, playerRace, playerKit, to_string(playerLevel), to_string(newXPAmount));
}
void Players::updateXPAmount(string username, int playerLevel, double newXPAmount){
    Players player;
    Kit kit;
    Cipher tempCode;
    //since we are re-writing the file we need the following:
    string playerRace = player.getPlayerRace(username); //get the players kit
    string playerKit = kit.getPlayerKit(username); //get the players race
    tempCode.userDataDeliminationWrite(4, username, playerRace, playerKit, to_string(playerLevel), to_string(newXPAmount)); //save the new XP amount along with resaving race, kit, level
}