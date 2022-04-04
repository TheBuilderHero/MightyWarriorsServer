#include <string>
#include <cmath>    //Kyle
#include <iostream> //can remove this later when increaseXP() is fully integrated

#include "Battle.h"
#include "Enemies.h"

using namespace std;

string Battle::getEnemyBattleStats(int enemyRandomChoice, int level, string statChoice){ //set the enemy battle stats based on the level and statChoice which can be [health, armor, magicResistance, physicalDamage, magicDamage, agility, stealth]
    //This code is intended to be used for each individual stat from health to stealth by the different inputs of level and enemyRandomChoice's value
    Enemies enemy;
    //level needs to be implimented later down the road
    if (statChoice == "health") {
        return to_string(enemy.enemyChoice(enemyRandomChoice, 1));
    } else if (statChoice == "armor") {
        return to_string(enemy.enemyChoice(enemyRandomChoice, 2));
    } else if (statChoice == "magicResistance") {
        return to_string(enemy.enemyChoice(enemyRandomChoice, 3));
    } else if (statChoice == "physicalDamage") {
        return to_string(enemy.enemyChoice(enemyRandomChoice, 4));
    } else if (statChoice == "magicDamage") {
        return to_string(enemy.enemyChoice(enemyRandomChoice, 5));
    } else if (statChoice == "agility") {
        return to_string(enemy.enemyChoice(enemyRandomChoice, 6));
    } else if (statChoice == "stealth") {
        return to_string(enemy.enemyChoice(enemyRandomChoice, 7));
    } else {
        return "0";
    }
    return "0";
}
void Battle::setPlayerBattleStats(std::string name, int level, int health, int armor, int magicResistance, int magicDamage, int agility, int physicalDamage){ //set the player battle stats
    //code for setting the players battle stats - This will pull the stats from the Players stat file on battle start
    //we will also need to get the weapon the player is using to know about the extra damage
}
int Battle::doQOption(std::string race){ //this will be the main damage ability - output is damage amount in type int
    //code for q
    return 1;
}
int Battle::doWOption(std::string race){ //this will be the main utility ability - output is dmage amount in type int
    //code for w
    return 1;
}
int Battle::doEOption(std::string race){ //this will be the main dodge or block ability - output is damage amount in type int
    //code for e
    return 1;
}
int Battle::doROption(std::string race){ //this will be the ultimate ability - output is damage amount in type int
    //code for r
    return 1;
}
//end battle proccess
//kyle -->
double Battle::increaseXP(int playerLevel, double playerCurrentXP){//std::string enemyName, int level, int difficulty){ // we need to incorperate the inputs "enemyName", "level", and "difficulty" into the the following code
    //code for the xp en enemy will give
    int levels = 100; //total number of levels
    int firstLevel = 500; //amount of XP needed for progression from level 1 to 2
    int lastLevel = 1000000;  //amount of xp needed to make it from level 99 to the max level 100
    int totalXPRemainingForNextLevel = 0; //set this in the for loop
    int newPlayerCurrentXP = 0; //this will set the new XP amount witch the user has obtained

    double B = log((double)lastLevel / firstLevel) / (levels - 1);
    double A = (double)firstLevel / (exp(B) - 1.0);

    for (int i = 1; i <= levels; i++){ //run through all the levels and calculate the amount of xp needed to get to the next level.
        int oldXP = round(A * exp(B * (i - 1)));
        int newXP = round(A * exp(B * i));
        int totalXPNeededForNextLevel = (newXP - oldXP); //this gives us the amount of XP needed for the current level
        totalXPRemainingForNextLevel = totalXPNeededForNextLevel - playerCurrentXP;  //this gives us the XP needed for the next level
        newPlayerCurrentXP = totalXPNeededForNextLevel - totalXPRemainingForNextLevel; //this will give the amount of XP which the user now has
        std::cout << i << " " << (newXP - oldXP) << std::endl;
        if (i == playerLevel) { // if the user's level is the same as the current loops level then we check the user's XP amounts against it
            if (newPlayerCurrentXP >= totalXPNeededForNextLevel) { // if the user's XP is greater than or equal to the XP needed for the next level then we run the code for leveling the Player up.
                //code for leveling Player up
            } else {
                return newPlayerCurrentXP; //return the remaining amount of xp needed for the user to level up from the current level
            }
        }
    }

    return newPlayerCurrentXP;
}
void Battle::enemyDrops(std::string enemyName, int level, int difficulty){
    //code for the drops which a enemy gives
}