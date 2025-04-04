#include <string>

#pragma once

class Battle{//This class will have all the functions needed for the algorythms needed to complete a battle from start to finish.
    private:
    int MAX_GROUP_SIZE = 10;
    const float DEFENSE_RATIO = .50; //this is the percent of armor that equates to the amount of damage points reduced
    const float BLOCK_REDUCTION_VALUE = .10;
    int randomizer = 0;
    //bool enemyBlocking = false; //isEnemyBlocking does not use this as of now
    //need to modify so that we can return values instead of this:
    std::string listOfEnemies[10]; //this is used for the enemies within a group - lists all their names
    std::string attackType; //this will be sent to the client to properly deal psychic, magic, or physical damage
    
    public:
    std::string getEnemyBattleStats(int enemyRandomChoice, int level, std::string statChoice); //set the enemy battle stats //return a value of type int but converted to a string
    void loadPlayerBattleStats(std::string name, int level, int health, int armor, int magicResistance, int magicDamage, int agility, int physicalDamage); //set the player battle stats
    //(depending on race) These abilities will have different effects and damages.  So we need to take some input for race
    int determineOption(std::string username, int selectedOption, int enemyChoice, int weapon); //from info sent from client we will determine the ability/option used. 
    int doQOption(std::string username, std::string attackMagicOrPhysical, int enemyChoice); //this will be the main damage ability - output is damage amount in type int
    int doWOption(std::string username, std::string attackMagicOrPhysical, int enemyChoice); //this will be the main utility ability - output is dmage amount in type int
    int doEOption(std::string username, std::string attackMagicOrPhysical, int enemyChoice); //this will be the main dodge or block ability - output is damage amount in type int
    int doROption(std::string username, std::string attackMagicOrPhysical, int enemyChoice); //this will be the ultimate ability - output is damage amount in type int
    void enemyGroups();
    //enemy attacks:
    int determineEnemyAttackOption(std::string username, int enemyChoice, std::string playerBlocking, int randomHelper = 0);
    int doEnemyOption1(std::string username, std::string attackMagicOrPhysical, int enemyChoice, std::string playerBlocking);
    int doEnemyOption2(std::string username, std::string attackMagicOrPhysical, int enemyChoice, std::string playerBlocking);
    int doEnemyOption3(std::string username, std::string attackMagicOrPhysical, int enemyChoice, std::string playerBlocking);
    int doEnemyOption4(std::string username, std::string attackMagicOrPhysical, int enemyChoice, std::string playerBlocking);
    bool isEnemyBlocking();
    float getBLOCK_REDUCTION_VALUE() { return BLOCK_REDUCTION_VALUE; }

    //end battle proccess
    double increaseXP(std::string username, double playerXPIncrease);// this can return the total amount of xp needed for the next level
    void enemyDrops(std::string enemyName, int level, int difficulty);

    std::string getAttackType(){ return attackType; }
};