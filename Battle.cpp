#include <string>
#include <cmath>    //Kyle
#include <iostream> //can remove this later when increaseXP() is fully integrated

#include "Battle.h"
#include "Enemies.h"
#include "Characters.h"
#include "Players.h"
#include "Cipher.h"
#include "PlayerElements/Kit.h"


using namespace std;

string Battle::getEnemyBattleStats(int enemyRandomChoice, int level, string statChoice){ //set the enemy battle stats based on the level and statChoice which can be [health, armor, magicResistance, physicalDamage, magicDamage, agility, stealth]
    //This code is intended to be used for each individual stat from health to stealth by the different inputs of level and enemyRandomChoice's value
    Enemies enemy;
    //level needs to be implimented later down the road
    if (statChoice == "health") {
        return to_string(enemy.enemyChoiceGetStat(enemyRandomChoice, 1, level));
    } else if (statChoice == "armor") {
        return to_string(enemy.enemyChoiceGetStat(enemyRandomChoice, 2, level));
    } else if (statChoice == "magicResistance") {
        return to_string(enemy.enemyChoiceGetStat(enemyRandomChoice, 3, level));
    } else if (statChoice == "physicalDamage") {
        return to_string(enemy.enemyChoiceGetStat(enemyRandomChoice, 4, level));
    } else if (statChoice == "magicDamage") {
        return to_string(enemy.enemyChoiceGetStat(enemyRandomChoice, 5, level));
    } else if (statChoice == "agility") {
        return to_string(enemy.enemyChoiceGetStat(enemyRandomChoice, 6, level));
    } else if (statChoice == "stealth") {
        return to_string(enemy.enemyChoiceGetStat(enemyRandomChoice, 7, level));
    } else if (statChoice == "mind") {
        return to_string(enemy.enemyChoiceGetStat(enemyRandomChoice, 8, level));
    } else if (statChoice == "pyschicDamage") {
        return to_string(enemy.enemyChoiceGetStat(enemyRandomChoice, 9, level));
    } else {
        return "0";
    }
    return "0";
}
void Battle::loadPlayerBattleStats(std::string name, int level, int health, int armor, int magicResistance, int magicDamage, int agility, int physicalDamage){ //set the player battle stats
    //code for setting the players battle stats - This will pull the stats from the Players stat file on battle start
    //we will also need to get the weapon the player is using to know about the extra damage
}
int Battle::determineOption(string username, int selectedOption, int enemyChoice, int weapon){ //this function is used to determine the ability/attack option to perform
    Kit kit;
    switch(selectedOption){ //based on this value they either pressed Q(1), W(2), E(3), or R(4)
        case 1:
            return doQOption(username, kit.getRaceDamageTypeForAbility(username, 'q'), enemyChoice);
            break;
        case 2:
            return doWOption(username, kit.getRaceDamageTypeForAbility(username, 'w'), enemyChoice);
            break;
        case 3:
            return doEOption(username, kit.getRaceDamageTypeForAbility(username, 'e'), enemyChoice);
            break;
        case 4:
            return doROption(username, kit.getRaceDamageTypeForAbility(username, 'r'), enemyChoice);
            break;
    }
    return 0; //This should never be reached
}
int Battle::doQOption(string username, string attackMagicOrPhysical, int enemyChoice){ //this will be the main damage ability - output is damage amount in type int
    //this should take into account wether it is magic or physical
    Players players;
    Cipher code;
    Enemies enemy;
    Kit kit;
    double qDamage = 0;
    //pull in the player attack stats
    double physicalDamage;
    double magicDamage;
    double psychicDamage;
    try{
        physicalDamage = stoi(players.getPhysicalDamageStat(username));
        magicDamage = stoi(players.getMagicDamageStat(username));
        psychicDamage = stoi(players.getPsychicDamageStat(username));
    } catch(std::invalid_argument){
        cout << "failed: Battle::doQOption" << endl;
    }
    
    //pull in the enemy defense stats
    int enemyLevel = players.getLevel(username);
    double armor = enemy.enemyChoiceGetStat(enemyChoice, 2, enemyLevel); //based on the players level
    double magicResistance = enemy.enemyChoiceGetStat(enemyChoice, 3, enemyLevel);

    //calculate the amount of damage based on the attack multiplied by the defense percentage of the defense from the enemy
    if (attackMagicOrPhysical == kit.getDAMAGETYPE_PHYSICAL()) qDamage = physicalDamage -= (armor * DEFENSE_RATIO);
    if (attackMagicOrPhysical == kit.getDAMAGETYPE_MAGIC()) qDamage = magicDamage -= (magicResistance * DEFENSE_RATIO);
    if (attackMagicOrPhysical == kit.getDAMAGETYPE_PSYCHIC()) qDamage = psychicDamage;

    if(qDamage < 0) qDamage = 0; //this prevents attacks with negative values

    //return the damage done by Q rounded to a whole number
    return round(qDamage);
}
int Battle::doWOption(string username, string attackMagicOrPhysical, int enemyChoice){ //this will be the main utility ability - output is dmage amount in type int
    //code for w - duplicate of Q
    //this should take into account wether it is magic or physical
    Players players;
    Cipher code;
    Enemies enemy;
    Kit kit;
    double wDamage = 0;
    //pull in the player attack stats
    double physicalDamage;
    double magicDamage;
    double psychicDamage;
    try{
        physicalDamage = stoi(players.getPhysicalDamageStat(username));
        magicDamage = stoi(players.getMagicDamageStat(username));
        psychicDamage = stoi(players.getPsychicDamageStat(username));
    } catch (std::invalid_argument){
        cout << "failed: Battle::doWOption" << endl;
    }
    
    //pull in the enemy defense stats
    int enemyLevel = players.getLevel(username);
    double armor = enemy.enemyChoiceGetStat(enemyChoice, 2,enemyLevel);
    double magicResistance = enemy.enemyChoiceGetStat(enemyChoice, 3,enemyLevel);

    //calculate the amount of damage based on the attack multiplied by the defense percentage of the defense from the enemy
    if (attackMagicOrPhysical == kit.getDAMAGETYPE_PHYSICAL()) wDamage = physicalDamage -= (armor/DEFENSE_RATIO);
    if (attackMagicOrPhysical == kit.getDAMAGETYPE_MAGIC()) wDamage = magicDamage -= (magicResistance/DEFENSE_RATIO);
    if (attackMagicOrPhysical == kit.getDAMAGETYPE_PSYCHIC()) wDamage = psychicDamage;

    if(wDamage < 0) wDamage = 0; //this prevents attacks with negative values

    //return the damage done by Q rounded to a whole number
    return round(wDamage);
}
int Battle::doEOption(string username, string attackMagicOrPhysical, int enemyChoice){ //this will be the main dodge or block ability - output is damage amount in type int
    //code for e - duplicate of Q
    //this should take into account wether it is magic or physical
    Players players;
    Cipher code;
    Enemies enemy;
    Kit kit;
    double eDamage = 0;
    //pull in the player attack stats
    double physicalDamage;
    double magicDamage;
    double psychicDamage;
    try{
        physicalDamage = stoi(players.getPhysicalDamageStat(username));
        magicDamage = stoi(players.getMagicDamageStat(username));
        psychicDamage = stoi(players.getPsychicDamageStat(username));
    } catch(std::invalid_argument){
        cout << "failed: Battle::doEOption" << endl;
    }
    
    //pull in the enemy defense stats
    int enemyLevel = players.getLevel(username);
    double armor = enemy.enemyChoiceGetStat(enemyChoice, 2,enemyLevel);
    double magicResistance = enemy.enemyChoiceGetStat(enemyChoice, 3, enemyLevel);

    //calculate the amount of damage based on the attack multiplied by the defense percentage of the defense from the enemy
    if (attackMagicOrPhysical == kit.getDAMAGETYPE_PHYSICAL()) eDamage = physicalDamage -= (armor * DEFENSE_RATIO);
    if (attackMagicOrPhysical == kit.getDAMAGETYPE_MAGIC()) eDamage = magicDamage -= (magicResistance * DEFENSE_RATIO);
    if (attackMagicOrPhysical == kit.getDAMAGETYPE_PSYCHIC()) eDamage = psychicDamage;

    if(eDamage < 0) eDamage = 0; //this prevents attacks with negative values

    //return the damage done by Q rounded to a whole number
    return round(eDamage);
}
int Battle::doROption(string username, string attackMagicOrPhysical, int enemyChoice){ //this will be the ultimate ability - output is damage amount in type int
    //code for r
    //this should take into account wether it is magic or physical just like Q
    Players players;
    Cipher code;
    Enemies enemy;
    Kit kit;
    double rDamage = 0;
    //pull in the player attack stats
    double physicalDamage;
    double magicDamage;
    double psychicDamage;
    try{
        physicalDamage = stoi(players.getPhysicalDamageStat(username));
        magicDamage = stoi(players.getMagicDamageStat(username));
        psychicDamage = stoi(players.getPsychicDamageStat(username));
    } catch(std::invalid_argument){
        cout << "failed: Battle::doROption" << endl;
    }
    
    //pull in the enemy defense stats
    int enemyLevel = players.getLevel(username);
    double armor = enemy.enemyChoiceGetStat(enemyChoice, 2, enemyLevel);
    double magicResistance = enemy.enemyChoiceGetStat(enemyChoice, 3, enemyLevel);

    //calculate the amount of damage based on the attack multiplied by the defense percentage of the defense from the enemy
    if (attackMagicOrPhysical == kit.getDAMAGETYPE_PHYSICAL()) rDamage = physicalDamage -= (armor * DEFENSE_RATIO);
    if (attackMagicOrPhysical == kit.getDAMAGETYPE_MAGIC()) rDamage = magicDamage -= (magicResistance * DEFENSE_RATIO);
    if (attackMagicOrPhysical == kit.getDAMAGETYPE_PSYCHIC()) rDamage = psychicDamage;

    if(rDamage < 0) rDamage = 0; //this prevents attacks with negative values

    //The Damage of R is buffed by a factor of 5 after the subtraction of armor/magic resistance calculations since it is the ultimate ability
    //return the damage done by Q rounded to a whole number
    return round(rDamage * 5);
}
void Battle::enemyGroups(){
    Enemies enemy;
    string bossEnemy; // stores the boss character of the group
    srand (time(NULL)); 
    string randomEnemyName = enemy.getEnemyName(rand() % 12 + 1); //Accessing all avaliable enemy types
    int numberOfEnemies = rand() % 7 + 1; // Random number of enemies between 1 and 7
    // Not sure what this is:
    //EnemyGroup enemyEncounter = new EnemyGroup(randomEnemyName);
    //maybe this will work instead:
    //listOfEnemies[numberOfEnemies + 1]; // add 1 for the boss
    
    if (numberOfEnemies > 4){ // If there are more than 4 enemies in a group, a normal potato will spawn
        bossEnemy = enemy.getEnemyName(13);
    }
    
    if (numberOfEnemies < 4){ // If there are less than 4 enemies in a group, a giant raccoon will spawn
        bossEnemy = enemy.getEnemyName(8);
    }
    
    //place all enemies in the array:
    int count = 0;
    while(count != (numberOfEnemies)){
        listOfEnemies[count] = randomEnemyName;
        count++;
    }
    listOfEnemies[numberOfEnemies + 1] = bossEnemy; // add 1 for the boss

    //maybe modify this later to use struct and typedef
    //return listOfEnemies;
}
//Enemy attack functions:
int Battle::determineEnemyAttackOption(string username, int enemyChoice, string playerBlocking, int randomHelper){
    Enemies enemy;
    //get random number 1 - 4 for the different attack options
    srand (time(NULL)); //seed random number based on time
    randomizer = randomHelper;
    int option = (rand()-randomizer) % 4 + 1; //random number
    int damage;

    switch (option){ //the random number is used to pick the type of attack which will be done
    //right now all the below do the same thing with a different damage type.  We will need to update them to each have a unigue function.
    case 1: //magical attack
        damage = doEnemyOption1(username, enemy.getDAMAGETYPE_PSYCHIC(), enemyChoice, playerBlocking);
        attackType = enemy.getDAMAGETYPE_PSYCHIC();
        break;
    case 2: //physical attack
        damage = doEnemyOption2(username, enemy.getDAMAGETYPE_PHYSICAL(), enemyChoice, playerBlocking);
        attackType = enemy.getDAMAGETYPE_PHYSICAL();
        break;
    case 3://magical attack
        damage = doEnemyOption3(username, enemy.getDAMAGETYPE_MAGIC(), enemyChoice, playerBlocking);
        attackType = enemy.getDAMAGETYPE_MAGIC();
        break;
    case 4: //physical attack
        damage = doEnemyOption4(username, enemy.getDAMAGETYPE_PHYSICAL(), enemyChoice, playerBlocking);
        attackType = enemy.getDAMAGETYPE_PHYSICAL();
        break;
    
    default:
        return 0; //this should never happen
        break;
    }
    
    return damage;
}
int Battle::doEnemyOption1(string username, string attackMagicOrPhysical, int enemyChoice, string playerBlocking){ //one of the enemies options for attacking the player
    //this should take into account wether it is magic or physical
    Players players;
    Cipher code;
    Enemies enemy;
    double option1Damage = 0;
    //pull in the enemy attack stats
    int enemyLevel = players.getLevel(username);
    double physicalDamage = enemy.enemyChoiceGetStat(enemyChoice, 4, enemyLevel);
    double magicDamage = enemy.enemyChoiceGetStat(enemyChoice, 5, enemyLevel);
    double psychicDamage = enemy.enemyChoiceGetStat(enemyChoice, 9, enemyLevel);
    
    //pull in the player defense stats
    double armor;
    double magicResistance;
    try{
        armor = stoi(players.getArmorStat(username));
        magicResistance = stoi(players.getMagicResistanceStat(username));
    } catch(std::invalid_argument) {
        cout << "failed: Battle::doEnemyOption1" << endl;
    }
    

    //calculate the amount of damage based on the attack multiplied by the defense percentage of the defense from the player's stats
    if (attackMagicOrPhysical == enemy.getDAMAGETYPE_PHYSICAL()) option1Damage = physicalDamage - (armor * DEFENSE_RATIO);
    if (attackMagicOrPhysical == enemy.getDAMAGETYPE_MAGIC()) option1Damage = magicDamage - (magicResistance * DEFENSE_RATIO);
    if (attackMagicOrPhysical == enemy.getDAMAGETYPE_PSYCHIC()) option1Damage = psychicDamage;

    //add random amount of damage from 10 - 30:
    srand (time(NULL)); //seed random number based on time
    if(attackMagicOrPhysical == enemy.getDAMAGETYPE_PSYCHIC()){
        option1Damage += (rand()-randomizer) % 5; 
    }else{
        option1Damage += (rand()-randomizer) % (30 + 1) + 10; //add random value
    }

    //check if player was blocking - If yes, we do 75% damage //1 being true
    if (playerBlocking == "1") option1Damage *= BLOCK_REDUCTION_VALUE; 

    if(option1Damage < 0) option1Damage = 0; //this prevents attacks with negative values

    //return the damage done by this option rounded to a whole number
    return round(option1Damage);
}
int Battle::doEnemyOption2(string username, string attackMagicOrPhysical, int enemyChoice, string playerBlocking){ //one of the enemies options for attacking the player
    //this should take into account wether it is magic or physical
    Players players;
    Cipher code;
    Enemies enemy;
    double option2Damage = 0;
    //pull in the enemy attack stats
    int enemyLevel = players.getLevel(username);
    double physicalDamage = enemy.enemyChoiceGetStat(enemyChoice, 4, enemyLevel);
    double magicDamage = enemy.enemyChoiceGetStat(enemyChoice, 5, enemyLevel);
    double psychicDamage = enemy.enemyChoiceGetStat(enemyChoice, 9, enemyLevel);
    
    //pull in the player defense stats
    double armor;
    double magicResistance;
    try{
        armor = stoi(players.getArmorStat(username));
        magicResistance = stoi(players.getMagicResistanceStat(username));
    } catch(std::invalid_argument) {
        cout << "failed: Battle::doEnemyOption2" << endl;
    }

    //calculate the amount of damage based on the attack multiplied by the defense percentage of the defense from the player's stats
    if (attackMagicOrPhysical == enemy.getDAMAGETYPE_PHYSICAL()) option2Damage = physicalDamage - (armor * DEFENSE_RATIO);
    if (attackMagicOrPhysical == enemy.getDAMAGETYPE_MAGIC()) option2Damage = magicDamage - (magicResistance * DEFENSE_RATIO);
    if (attackMagicOrPhysical == enemy.getDAMAGETYPE_PSYCHIC()) option2Damage = psychicDamage;

    //add random amount of damage from 10 - 30:
    srand (time(NULL)); //seed random number based on time
    if(attackMagicOrPhysical == enemy.getDAMAGETYPE_PSYCHIC()){
        option2Damage += (rand()-randomizer) % 5; 
    }else{
        option2Damage += (rand()-randomizer) % (30 + 1) + 10; //add random value
    }

    //check if player was blocking - If yes, we do 75% damage //1 being true
    if (playerBlocking == "1") option2Damage *= BLOCK_REDUCTION_VALUE; 

    if(option2Damage < 0) option2Damage = 0; //this prevents attacks with negative values

    //return the damage done by this option rounded to a whole number
    return round(option2Damage);
}
int Battle::doEnemyOption3(string username, string attackMagicOrPhysical, int enemyChoice, string playerBlocking){ //one of the enemies options for attacking the player
    //this should take into account wether it is magic or physical
    Players players;
    Cipher code;
    Enemies enemy;
    double option3Damage = 0;
    //pull in the enemy attack stats
    int enemyLevel = players.getLevel(username);
    double physicalDamage = enemy.enemyChoiceGetStat(enemyChoice, 4, enemyLevel);
    double magicDamage = enemy.enemyChoiceGetStat(enemyChoice, 5, enemyLevel);
    double psychicDamage = enemy.enemyChoiceGetStat(enemyChoice, 9, enemyLevel);
    
    //pull in the player defense stats
    double armor;
    double magicResistance;
    try{
        armor = stoi(players.getArmorStat(username));
        magicResistance = stoi(players.getMagicResistanceStat(username));
    } catch(std::invalid_argument) {
        cout << "failed: Battle::doEnemyOption3" << endl;
    }

    //calculate the amount of damage based on the attack multiplied by the defense percentage of the defense from the player's stats
    if (attackMagicOrPhysical == enemy.getDAMAGETYPE_PHYSICAL()) option3Damage = physicalDamage - (armor * DEFENSE_RATIO);
    if (attackMagicOrPhysical == enemy.getDAMAGETYPE_MAGIC()) option3Damage = magicDamage - (magicResistance * DEFENSE_RATIO);
    if (attackMagicOrPhysical == enemy.getDAMAGETYPE_PSYCHIC()) option3Damage = psychicDamage;

    //add random amount of damage from 10 - 30:
    srand (time(NULL)); //seed random number based on time
    if(attackMagicOrPhysical == enemy.getDAMAGETYPE_PSYCHIC()){
        option3Damage += (rand()-randomizer) % 5; 
    }else{
        option3Damage += (rand()-randomizer) % (30 + 1) + 10; //add random value
    }

    //check if player was blocking - If yes, we do 75% damage //1 being true
    if (playerBlocking == "1") option3Damage *= BLOCK_REDUCTION_VALUE; 

    if(option3Damage < 0) option3Damage = 0; //this prevents attacks with negative values

    //return the damage done by this option rounded to a whole number
    return round(option3Damage);
}
int Battle::doEnemyOption4(string username, string attackMagicOrPhysical, int enemyChoice, string playerBlocking){ //one of the enemies options for attacking the player
    //this should take into account wether it is magic or physical
    Players players;
    Cipher code;
    Enemies enemy;
    double option4Damage = 0;
    //pull in the enemy attack stats
    int enemyLevel = players.getLevel(username);
    double physicalDamage = enemy.enemyChoiceGetStat(enemyChoice, 4, enemyLevel);
    double magicDamage = enemy.enemyChoiceGetStat(enemyChoice, 5, enemyLevel);
    double psychicDamage = enemy.enemyChoiceGetStat(enemyChoice, 9, enemyLevel);
    
    //pull in the player defense stats
    double armor;
    double magicResistance;
    try{
        armor = stoi(players.getArmorStat(username));
        magicResistance = stoi(players.getMagicResistanceStat(username));
    } catch(std::invalid_argument) {
        cout << "failed: Battle::doEnemyOption4" << endl;
    }

    //calculate the amount of damage based on the attack multiplied by the defense percentage of the defense from the player's stats
    if (attackMagicOrPhysical == enemy.getDAMAGETYPE_PHYSICAL()) option4Damage = physicalDamage - (armor * DEFENSE_RATIO);
    if (attackMagicOrPhysical == enemy.getDAMAGETYPE_MAGIC()) option4Damage = magicDamage - (magicResistance * DEFENSE_RATIO);
    if (attackMagicOrPhysical == enemy.getDAMAGETYPE_PSYCHIC()) option4Damage = psychicDamage;

    //add random amount of damage from 10 - 30:
    srand (time(NULL)); //seed random number based on time
    if(attackMagicOrPhysical == enemy.getDAMAGETYPE_PSYCHIC()){
        option4Damage += (rand()-randomizer) % 5; 
    }else{
        option4Damage += (rand()-randomizer) % (30 + 1) + 10; //add random value
    }

    //check if player was blocking - If yes, we do 75% damage //1 being true
    if (playerBlocking == "1") option4Damage *= BLOCK_REDUCTION_VALUE; 

    if(option4Damage < 0) option4Damage = 0; //this prevents attacks with negative values

    //return the damage done by this option rounded to a whole number
    return round(option4Damage);
}

bool Battle::isEnemyBlocking(){  //Check if the enemy is blocking this next attack: //replies randomly with a 1 in 5 chance of yes
    bool block = false; //initalize local variable
    //get random number 1 - 5 for a 1 in 5 chance of the enemy blocking
    srand (time(NULL)); //seed random number based on time
    int option = rand() % 5 + 1; //random number
    
    if(option == 1) block = true; //the number has to be 1 for the enemy to be blocking

    //return if the enemy is blocking or not
    return block;
}

//end battle proccess
//kyle -->
double Battle::increaseXP(string username, double playerXPIncrease){//std::string enemyName, int level, int difficulty){ // we need to incorperate the inputs "enemyName", "level", and "difficulty" into the the following code
    //code for the xp en enemy will give
    int levels = 100; //total number of levels
    int firstLevel = 500; //amount of XP needed for progression from level 1 to 2
    int lastLevel = 1000000;  //amount of xp needed to make it from level 99 to the max level 100
    int totalXPRemainingForNextLevel = 0; //set this in the for loop
    int newPlayerCurrentXP = 0; //this will set the new XP amount witch the user has obtained
    bool levelUp = false;

    //pull player XP and level from file
    double playerCurrentXP;
    int playerLevel;
    int totalXPNeededForNextLevel = 0;
    Players player;
    playerCurrentXP = player.getXP(username);
    playerLevel = player.getLevel(username);

    double B = log((double)lastLevel / firstLevel) / (levels - 1);
    double A = (double)firstLevel / (exp(B) - 1.0);

    for (int i = 1; i <= levels; i++){ //run through all the levels and calculate the amount of xp needed to get to the next level.
        int oldXP = round(A * exp(B * (i - 1)));
        int newXP = round(A * exp(B * i));

        totalXPNeededForNextLevel = (newXP - oldXP); //this gives us the amount of XP needed for the current level
        totalXPRemainingForNextLevel = totalXPNeededForNextLevel - playerCurrentXP;  //this gives us the XP needed for the next level
        totalXPRemainingForNextLevel -= playerXPIncrease; //subtract the xp gained from the remaining XP needed for the next level giving us the new remaining XP
        //only run this the first time through
        if(!levelUp) newPlayerCurrentXP = totalXPNeededForNextLevel - totalXPRemainingForNextLevel; //this will give the amount of XP which the user now has

        //uncomment the following two for troubleshooting player level and xp.//
        //std::cout << i << " " << totalXPNeededForNextLevel << std::endl; 
        //cout << newPlayerCurrentXP << endl;
        if (i == playerLevel) { // if the user's level is the same as the current loops level then we check the user's XP amounts against it
            if (newPlayerCurrentXP >= totalXPNeededForNextLevel) { // if the user's XP is greater than or equal to the XP needed for the next level then we run the code for leveling the Player up.
                //newPlayerCurrentXP >= totalXPNeededForNextLevel
                //code for leveling Player up
                levelUp = true;
                newPlayerCurrentXP -= totalXPNeededForNextLevel; //subtract the XP it took to get to the next level.
                player.levelUp(username, playerLevel, newPlayerCurrentXP);
                return totalXPNeededForNextLevel; //return the total amount of xp needed for the user to level up from the current level
            } else {//otherwise just store their new xp amount (newPlayerCurrentXP)
                player.updateXPAmount(username, playerLevel, newPlayerCurrentXP);
                return totalXPNeededForNextLevel; //return the total amount of xp needed for the user to level up from the current level
            }
        }
    }
    return totalXPNeededForNextLevel; //return the total amount of xp needed for the user to level up from the current level
}
void Battle::enemyDrops(std::string enemyName, int level, int difficulty){
    //code for the drops which a enemy gives
}