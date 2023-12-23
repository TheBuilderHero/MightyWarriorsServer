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
    //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    vector<pair<int,string>> readVector;
    tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
    //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int fileHealth_max;
    try{
        fileHealth_max = stoi(readVector.at(2).second); //this AT(#) corrseponds to the order in which they are pulled from the file
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getHealthStat()\"" << endl;
        fileHealth_max = -1000; //signal issue.
    }
    int totalHealthValue = characters.getBaseHealth() + fileHealth_max + kit.getHealth();
    return to_string(totalHealthValue);
}
string Players::getCurrentHealthStat(std::string username){ //this funciton calculates to total Health stat of a user and makes it into a string to be sent to the client
    Characters characters;
    Cipher tempCode;
    Players players;
    //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    vector<pair<int,string>> readVector;
    tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
    //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
    int fileHealth_current;
    try{
        fileHealth_current = stoi(readVector.at(1).second); //this AT(#) corrseponds to the order in which they are pulled from the file
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getCurrentHealthStat()\"" << endl;
        fileHealth_current = -1000; //signal issue.
    }
    int totalHealthValue = fileHealth_current;
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
        //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        vector<pair<int,string>> readVector;
        tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int filedamage_min;
        int filedamage_max;
        try{
            filedamage_min = stoi(readVector.at(5).second); //this AT(#) corrseponds to the order in which they are pulled from the file
            filedamage_max = stoi(readVector.at(6).second); //this AT(#) corrseponds to the order in which they are pulled from the file
        } catch(std::invalid_argument){
            cout << "failed stoi \"string Players::getPhysicalDamageStat()\"" << endl;
            filedamage_min = -1000; //signal issue.
            filedamage_max = -1000; //signal issue.
        }
        int totalPhysicalDamageValue_min = characters.getBasePhysicalDamage() + filedamage_min + kit.getPhysicalDamage();
        int totalPhysicalDamageValue_max = characters.getBasePhysicalDamage() + filedamage_max + kit.getPhysicalDamage();
        cout << "PhysicalDamage" << endl;
        cout << "total min: " << totalPhysicalDamageValue_min << endl;
        cout << "total max: " << totalPhysicalDamageValue_max << endl;
        cout << "weapon min: " << weapon.getPhysicalDamageMin() << endl;
        cout << "weapon max: " << weapon.getPhysicalDamageMax() << endl;
        return (to_string(totalPhysicalDamageValue_min + weapon.getPhysicalDamageMin()) + " - " + to_string(totalPhysicalDamageValue_max + weapon.getPhysicalDamageMax()));
    } else { 
        Characters characters;
        Cipher tempCode;
        Players players;
        Kit kit;
        kit.pullKitStats(username);
        Weapons weapon(username);
        //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        vector<pair<int,string>> readVector;
        tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int filedamage;
        try{
            filedamage = stoi(readVector.at(5).second); //this AT(#) corrseponds to the order in which they are pulled from the file
        } catch(std::invalid_argument){
            cout << "failed stoi \"string Players::getPhysicalDamageStat()\"" << endl;
            filedamage = -1000; //signal issue.
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
        //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        vector<pair<int,string>> readVector;
        tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
        int statMagicDamage_min;
        int statMagicDamage_max;
        try{
            statMagicDamage_min = stoi(readVector.at(7).second); //this AT(#) corrseponds to the order in which they are pulled from the file
            statMagicDamage_max = stoi(readVector.at(8).second); //this AT(#) corrseponds to the order in which they are pulled from the file

        } catch(std::invalid_argument){
            cout << "failed stoi \"string Players::getMagicDamageStat()\"" << endl;
            statMagicDamage_min = -1000;
            statMagicDamage_max = -1000;
        }
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int totalMagicDamageValue_min = characters.getBaseMagicDamage() + statMagicDamage_min + kit.getMagicDamage();
        int totalMagicDamageValue_max = characters.getBaseMagicDamage() + statMagicDamage_max + kit.getMagicDamage();
        cout << "MagicDamage" << endl;
        cout << "total min: " << totalMagicDamageValue_min << endl;
        cout << "total max: " << totalMagicDamageValue_max << endl;
        cout << "weapon min: " << weapon.getMagicDamageMin() << endl;
        cout << "weapon max: " << weapon.getMagicDamageMax() << endl;
        return (to_string(totalMagicDamageValue_min + weapon.getMagicDamageMin()) + " - " + to_string(totalMagicDamageValue_max + weapon.getMagicDamageMax()));
    } else {
        Characters characters;
        Cipher tempCode;
        Players players;
        Kit kit;
        kit.pullKitStats(username);
        Weapons weapon(username);
        //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        vector<pair<int,string>> readVector;
        tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
        int statMagicDamage;
        try{
            statMagicDamage = stoi(readVector.at(7).second); //this AT(#) corrseponds to the order in which they are pulled from the file
        } catch(std::invalid_argument){
            cout << "failed stoi \"string Players::getMagicDamageStat()\"" << endl;
            statMagicDamage = -1000; //signal issue.
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
        //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        vector<pair<int,string>> readVector;
        tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
        int statPsychicDamage_min;
        int statPsychicDamage_max;
        try{
            statPsychicDamage_min = stoi(readVector.at(15).second); //this AT(#) corrseponds to the order in which they are pulled from the file
            statPsychicDamage_max = stoi(readVector.at(16).second); //this AT(#) corrseponds to the order in which they are pulled from the file
        } catch(std::invalid_argument){
            cout << "failed stoi \"string Players::getPyschicDamageStat()\"" << endl;
            statPsychicDamage_min = -1000; //signal issue.
            statPsychicDamage_max = -1000; //signal issue.
        }
        characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
        int totalPsychicDamageValue_min = characters.getBasePsychicDamage() + statPsychicDamage_min + kit.getPsychicDamage();
        int totalPsychicDamageValue_max = characters.getBasePsychicDamage() + statPsychicDamage_max + kit.getPsychicDamage();
        cout << "PsychicDamage" << endl;
        cout << "total min: " << totalPsychicDamageValue_min << endl;
        cout << "total max: " << totalPsychicDamageValue_max << endl;
        cout << "weapon min: " << weapon.getPsychicDamageMin() << endl;
        cout << "weapon max: " << weapon.getPsychicDamageMax() << endl;
        return (to_string(totalPsychicDamageValue_min + weapon.getPsychicDamageMin()) + " - " + to_string(totalPsychicDamageValue_max + weapon.getPsychicDamageMax()));
    } else {
        Characters characters;
        Cipher tempCode;
        Players players;
        Kit kit;
        kit.pullKitStats(username);
        Weapons weapon(username);
        //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
        vector<pair<int,string>> readVector;
        tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
        int statPsychicDamage;
        try{
            statPsychicDamage = stoi(readVector.at(15).second); //this AT(#) corrseponds to the order in which they are pulled from the file
        } catch(std::invalid_argument){
            cout << "failed stoi \"string Players::getPyschicDamageStat()\"" << endl;
            statPsychicDamage = -1000; //signal issue.
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
    //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    vector<pair<int,string>> readVector;
    tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statArmor;
    try{
        statArmor = stoi(readVector.at(3).second); //this AT(#) corrseponds to the order in which they are pulled from the file
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getArmorStat()\"" << endl;
        statArmor = -1000; //signal issue.
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
    //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    vector<pair<int,string>> readVector;
    tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statMRFile;
    try{
        statMRFile = stoi(readVector.at(4).second); //this AT(#) corrseponds to the order in which they are pulled from the file
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getMagicResistanceStat()\"" << endl;
        statMRFile = -1000; //signal issue.
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
    //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    vector<pair<int,string>> readVector;
    tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statAgilityFile;
    try{
        statAgilityFile = stoi(readVector.at(9).second); //this AT(#) corrseponds to the order in which they are pulled from the file
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getMagicResistanceStat()\"" << endl;
        statAgilityFile = -1000; //signal issue.
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
    //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    vector<pair<int,string>> readVector;
    tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statStealthFile;
    try{
        statStealthFile = stoi(readVector.at(10).second); //this AT(#) corrseponds to the order in which they are pulled from the file
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getStealthStat()\"" << endl;
        statStealthFile = -1000; //signal issue.
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
    //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    vector<pair<int,string>> readVector;
    tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statStaminaFile;
    try{
        statStaminaFile = stoi(readVector.at(11).second); //this AT(#) corrseponds to the order in which they are pulled from the file
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getStaminaStat()\"" << endl;
        statStaminaFile  = -1000; //signal issue.
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
    //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    vector<pair<int,string>> readVector;
    tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statManaFile;
    try{
        statManaFile = stoi(readVector.at(12).second); //this AT(#) corrseponds to the order in which they are pulled from the file
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getMagicResistanceStat()\"" << endl;
        statManaFile = -1000; //signal issue.
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
    //tempCode.userDataDeliminationRead(1, username); //sets the item# to the current stat values
    vector<pair<int,string>> readVector;
    tempCode.readFromFile(tempCode.STAT_DATA, username, readVector);
        //FILE DATA:  +=+ username 0 +=+ current health 1 +=+ max health 2 +=+ armor 3 +=+ magic resistance 4 +=+ Physical Damage min 5 +=+ Physical Damage max 6 +=+ Magic Damage min 7 +=+ Magic Damage max 8 +=+ Agility 9 +=+ Stealth 10 +=+ Stamina 11 +=+ Natuaral Energy 12 +=+ current Mind 13 +=+ max Mind 14 +=+ psychic damage min 15 +=+ psychic damage max 16
    characters.pullRaceStats(players.getPlayerRace(username), username);//set the stats of the Player for the race in their file
    int statMindFile;
    try{
        statMindFile = stoi(readVector.at(14).second); //this AT(#) corrseponds to the order in which they are pulled from the file
    } catch(std::invalid_argument){
        cout << "failed stoi \"string Players::getMindStat()\"" << endl;
        statMindFile = -1000; //signal issue.
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
        level = -1000; //signal issue.
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
        xP = -1000; //signal issue.
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