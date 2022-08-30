#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Enemies.h"
#include "Players.h"
#include "Characters.h"
#include "Cipher.h"
#include "Battle.h"
#include "PlayerElements/Kit.h"
#include "PlayerElements/Weapons.h"

//Make sure that game sersion is changed along with client or go to the version check function and allow for older versions of the client. (We must make sure to be acceptable in functionality)
//********************************************
//             Server Version
//********************************************
const int ServerVersion     = 1;
const int ServerMajorBuild  = 0;
const int ServerMinorBuild  = 0;
const int ServerPatch       = 0;
//********************************************
//         Required Client Version
//********************************************
const int gameVersion     = 1;
const int gameMajorBuild  = 0;
const int gameMinorBuild  = 0;
const int gamePatch       = 0;
//********************************************

using namespace std;
Cipher Delim; //just for the use of the delimiter.
string delimiter = Delim.getDelimiter(); //a character that marks the beginning or end of a unit of data which is declared in the Cipher Class
void dostuff(int); /* function prototype */
void premessageSendLengthVerification(int socket, int MessageLength);
void sendToClient(int socket, string message);


void error(const char* msg){//this function is called for an error and used to exit the program
    perror(msg);
    exit(1);
}

int userLogon(string usernameE, string passwordE) { //This code pulls the passwords out of the .act file so that we can compare them with the password entered by the user.
    
    string username, password;
    string logonContent;
    ifstream logon;
    logon.open("./userdata/" + usernameE + "/" + usernameE + ".act"); //open file to read content
    logon >> logonContent;
    logon.close();
    string token, output;
    int loopPass = 0;
    size_t pos = 0; // position variable for removing the delimiters to view the message
    while ((pos = logonContent.find(delimiter)) != std::string::npos) { //removing the delimiters to view each variable
        token = logonContent.substr(0, pos);
        output = token;
        logonContent.erase(0, pos + delimiter.length());
            
        switch (loopPass){
            case 1: //first item after delimiter
                if (output.length() > 0) username = output; //assign username variable
                break;
            case 2://second item after delimiter
                if (output.length() > 0) password = output; //assign password variable
                break;
        }
        loopPass++;
    }

    if (username == usernameE){ // test the logon info entered from the user against what is saved to the file. // 1 for working logon and pass, 0 for invalid
        if (password == passwordE){
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }

}

void requestActions(int socket, char messageFromClient[]) { //This function takes a socket and the message from the user and then performs an action based on the variable typeOfRequest which is contained in the message from th user.
    Kit kit;
    Cipher code;
    Characters characters;
    Players players;
    Battle battle;
    Enemies enemy;
    ifstream testUsername;
    string returnMessage = "0"; //this is hard setting the function to always say that the username does not exist if no other value is setup.
    string message = code.decipher(messageFromClient);
    int n;
    std::string level;//used in case 15
    
    //output the message recieved from the user to the consol.
    printf("V1.1-Here is the message from the User: %s\n", messageFromClient);

    //testing to see what action the user is requesting by switching between cases of typeOfRequest
    int request;
    try{
        request = stoi(code.getTypeOfRequest());
    } catch(std::invalid_argument){
        cout << "failed main: \"switch (request)\" in requestActions()" << endl;
    }
    switch (request) {
        case 1:{//check new users entered username against list of usernames to make sure it is unique
            message = code.decipher(messageFromClient); //unpack the message from the user
            testUsername.open("./userdata/" + code.getUsername() + "/" + code.getUsername() + ".dat"); //opens file to check if it exists
            if (testUsername) { // test user is true if it does exist and false if is does not // this means that when it exists you can not user that username
                testUsername.close();// closing opened file
                returnMessage = "0"; //not valid username - already in use
                returnMessage = code.cipher("1", returnMessage); //deliminates return message
                sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                
            } else {
                returnMessage = "1";  //valid username - not in use
                returnMessage = code.cipher("1", returnMessage); // deliminates return message
                sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                
            }
            break;
        }
        case 2:{//this is the user creation type
            code.userDataDeliminationWrite(1, code.getUsername(), code.getItem(3));

            break;
        }
        case 3:{//check logon info to confirm user identity - user logon
            int ableToLogon;
            ableToLogon = userLogon(code.getUsername(), code.getItem(3));
            returnMessage = code.cipher("3", to_string(ableToLogon));
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 4:{//change password
            code.userDataDeliminationWrite(2, code.getUsername(), code.getItem(3));
            break;
        }
        case 5:{//write the user stats to file
            code.userDataDeliminationWrite(3, code.getUsername(), code.getItem(3), code.getItem(4), code.getItem(5), code.getItem(6), code.getItem(7), code.getItem(8), code.getItem(9), code.getItem(10), code.getItem(11), code.getItem(12), code.getItem(13));
            returnMessage = code.cipher("4", "wasAbleToSave");
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 6:{//Making this read all user info form file  ---------------------------//try to read to user's stats from file - need to get this fully setup.
            code.userDataDeliminationRead(1, code.getUsername()); //sets the items3 - 6 to the current stat values
            characters.pullRaceStats(players.getPlayerRace(code.getUsername()), code.getUsername());//set the stats of the Player for the race in their file
            //trying some junk
            string health = players.getHealthStat(code.getUsername());
            string armor = players.getArmorStat(code.getUsername());
            string magicResist = players.getMagicResistanceStat(code.getUsername());
            string physicalDam = players.getPhysicalDamageStat(code.getUsername(), true);
            string magicDam = players.getMagicDamageStat(code.getUsername(), true);
            string agility = players.getAgilityStat(code.getUsername());
            string stealth = players.getStealthStat(code.getUsername());
            string stamina = players.getStaminaStat(code.getUsername());
            string naturalEnergy = players.getManaStat(code.getUsername());
            string mind = players.getMindStat(code.getUsername());
            string psychicDam = players.getPsychicDamageStat(code.getUsername(), true);

            //set the proper stat values for the input of the base stats (This is used in the following long statment)
            returnMessage = code.cipher("5", health, armor, magicResist, physicalDam, magicDam, agility, stealth, stamina, naturalEnergy, mind, psychicDam); // This very long input put into simple terms calculates stats by adding base to bonus then spitting it out as a string for Health, armor, magicResistance, physicalDamage, MagicDamage, Agility
            //cout << "Return message write successful\n";
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 7:{//read the enemy stats for battle
            int enemyNumPicked, enemyLevel;
            srand (time(NULL)); //initialize random seed
            int test1,enemyNum;
            try{
                test1 = stoi(code.getItem(3));
                enemyNum = stoi(code.getItem(4));
            } catch(std::invalid_argument){
                cout << "failed \"case 7:{//read the enemy stats for battle\"" << endl;
            }
            
            if(test1 == 1){
                if(enemyNum == 0){
                    enemyNumPicked = 2;
                }else{
                    enemyNumPicked = enemyNum + 90;
                }
            }else if(test1 == 2){
                enemyNumPicked = 13;
            }else{
                enemyNumPicked = rand() % 12 + 1;     //in the range 1 to 12 //this is the type of enemy which you will fight
            }
            enemyLevel = 1; //level of boss
            returnMessage = code.cipher("5", enemy.getEnemyName(enemyNumPicked), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "health"), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "armor"), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "magicResistance"), 
            battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "physicalDamage"), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "magicDamage"), to_string(enemyNumPicked), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "mind")); //get all the values for the enemy to be sent to the client (Change 1 later so that it depends on input from client)
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 8:{ //user race, kit, and weapon selection and write to file
            // using code.getItem(3) from the client (which is raceChoice) and code.getItem(4) (which is kitChoice) we will determine the race which the user selected which is the reutrn of getPlayerRace
            int tempWeaponChoice;
            int tempRaceChoice;
            int tempKitChoice;
            try{
                tempWeaponChoice = stoi(code.getItem(5));
                tempRaceChoice = stoi(code.getItem(3));
                tempKitChoice = stoi(code.getItem(4));
            } catch(std::invalid_argument){
                cout << "failed \"case 8:{ //user race, kit, and weapon selection and write to file\"" << endl;
            }
            Weapons weapons(code.getUsername(), true);
            weapons.setPlayerWeapon(tempWeaponChoice);
            weapons.~Weapons(); //call destructor to save weapon data
            code.userDataDeliminationWrite(1, code.getUsername(), players.getPlayerRace(code.getUsername(), tempRaceChoice), kit.getPlayerKit(code.getUsername(), tempKitChoice)); //write that race to file
            //instead of kit.kit we need to take code.getItem(4) and determine what kit they chose and input that.
            break;
            }
        case 9:{//this takes the input of battle attacks to then reply with the damage amount.
            int selectedOption;
            try{
                selectedOption = stoi(code.getItem(4));
            } catch(std::invalid_argument){
                cout << "failed \"case 9:{//this takes the input of battle attacks to then reply with the damage amount.\"" << endl;
            }
            returnMessage = code.cipher("4", to_string(battle.determineOption(code.getUsername(), selectedOption, enemy.getEnemyPickedFromName(code.getItem(3))))); //get the damage for one of the abilites and cipher return message.
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 10:{//enemy attacks
            int enemyDamage = battle.determineEnemyAttackOption(code.getUsername(), enemy.getEnemyPickedFromName(code.getItem(3)), code.getItem(4));//moved outside of message else attackType won't be initialized
            returnMessage = code.cipher("5", to_string(enemyDamage), battle.getAttackType()); //get the damage for the enemy and cipher return message.
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 11:{//check if enemy is blocking next attack
            returnMessage = code.cipher("5", to_string(battle.isEnemyBlocking()), to_string(battle.getBLOCK_REDUCTION_VALUE())); //get the damage for one of the abilites and cipher return message.
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 12:{//send the user the abilities which correspond to thier damage types (e.g. their Q does magic, their E does phycial)
            returnMessage = code.cipher("5", kit.getRaceDamageTypeForAbility(code.getUsername(), 'q'), kit.getRaceDamageTypeForAbility(code.getUsername(), 'w'), 
            kit.getRaceDamageTypeForAbility(code.getUsername(), 'e'), kit.getRaceDamageTypeForAbility(code.getUsername(), 'r')); //send back the damage type per ability with the order q, w, e, r
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 13:{ //sends the players race, kit, level, and weapon
            Weapons weapons(code.getUsername());
            returnMessage = code.cipher("5", players.getPlayerRace(code.getUsername()), kit.getPlayerKit(code.getUsername()), weapons.getWeaponName()); //
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 14:{//updates the players level and XP
            //currently using the players level for the enemy's level for XP since they should be the same
            //cout << code.getItem(3) << "\n";
            int enemyChoice;
            try{
                enemyChoice = stoi(code.getItem(3));
            } catch(std::invalid_argument){
                cout << "failed \"case 14:{//updates the players level and XP\"" << endl;
            }
            //cout << enemy.getXPDrop(enemyChoice) << "\n";
            battle.increaseXP(code.getUsername(), enemy.getXPDrop(enemyChoice)); //hardset the enemies level to 1 since at this moment there is no level change for enemies
            returnMessage = code.cipher("4", to_string(players.getLevel(code.getUsername())));
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 15:{//returns player Level, current XP, and total needed xp for next level
            level = to_string(players.getLevel(code.getUsername())); //this is done to avoid issues with the increaseXP function breaking the update stats function on the client side
            returnMessage = code.cipher("5", level, to_string(players.getXP(code.getUsername())), to_string(battle.increaseXP(code.getUsername(), 0)));
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1); //send message back to the client
            
            break;
        }
        case 16:{//update user stats
            code.userDataDeliminationWrite(5, code.getUsername(), code.getItem(3), code.getItem(4), code.getItem(5), code.getItem(6), code.getItem(7), code.getItem(8), code.getItem(9), code.getItem(10), code.getItem(11), code.getItem(12), code.getItem(13));
            returnMessage = code.cipher("4", "wasAbleToSave");
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 17:{//update location data
            code.userDataDeliminationWrite(7, code.getUsername(), code.getItem(2));
            returnMessage = code.cipher("4", "wasAbleToSave");
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 18:{//get user's location
            code.userDataDeliminationRead(4, code.getUsername());
            returnMessage = code.cipher("4", code.getItem(2));
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 19:{//update quest info
            code.userDataDeliminationWrite(8, code.getUsername(), code.getItem(2), code.getItem(3)); //first number is the quest number, then second one is the progess number
            returnMessage = code.cipher("4", "wasAbleToSave");
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 20:{//get quest progress info
            code.userDataDeliminationRead(5, code.getUsername()); //first number is the quest number, then second one is the progess number
            returnMessage = code.cipher("5", code.getItem(2), code.getItem(3), code.getItem(4), code.getItem(5), code.getItem(6), code.getItem(7), code.getItem(8), code.getItem(9), code.getItem(10));
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 21:{ //sends the player's race, kit, level, weapon, and ability types
            Weapons weapons(code.getUsername());
            level = to_string(players.getLevel(code.getUsername()));
            //One insanely long statement to get a return message
            returnMessage = code.cipher("5", players.getPlayerRace(code.getUsername()), kit.getPlayerKit(code.getUsername()), weapons.getWeaponName(), 
            level, to_string(players.getXP(code.getUsername())), to_string(battle.increaseXP(code.getUsername(), 0)), 
            kit.getRaceDamageTypeForAbility(code.getUsername(), 'q'), kit.getRaceDamageTypeForAbility(code.getUsername(), 'w'), 
            kit.getRaceDamageTypeForAbility(code.getUsername(), 'e'), kit.getRaceDamageTypeForAbility(code.getUsername(), 'r'));
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 22:{//test sending all the subCiphers
            //There seems to be some issues with SubDeciphering:
            //code.decipher(messageFromClient, true); //gives us all the values (including subCipher)

            // Add code for all data sent to server for saving.

            //test message to client:
            returnMessage = code.cipher("6", code.subCipher("2test1","2test2","2test3","2test4","2test5","2test6","2test7","2test8","2test9","2test10","2test11","2test12","2test13","2test14","2test15","2test16","2test17","2test18","2test19","2test20","2test21","2test22")/**/, code.subCipher("3test1","3test2","3test3","3test4","3test5","3test6","3test7","3test8","3test9","3test10","3test11","3test12","3test13","3test14","3test15","3test16","3test17","3test18","3test19","3test20","3test21","3test22"), code.subCipher("4test1","4test2","4test3","4test4","4test5","4test6","4test7","4test8","4test9","4test10","4test11","4test12","4test13","4test14","4test15","4test16","4test17","4test18","4test19","4test20","4test21","4test22"), code.subCipher("5test1","5test2","5test3","5test4","5test5","5test6","5test7","5test8","5test9","5test10","5test11","5test12","5test13","5test14","5test15","5test16","5test17","5test18","5test19","5test20","5test21","5test22"), code.subCipher("6test1","6test2","6test3","6test4","6test5","6test6","6test7","6test8","6test9","6test10","6test11","6test12","6test13","6test14","6test15","6test16","6test17","6test18","6test19","6test20","6test21","6test22"), code.subCipher("7test1","7test2","7test3","7test4","7test5","7test6","7test7","7test8","7test9","7test10","7test11","7test12","7test13","7test14","7test15","7test16","7test17","7test18","7test19","7test20","7test21","7test22"), code.subCipher("8test1","8test2","8test3","8test4","8test5","8test6","8test7","8test8","8test9","8test10","8test11","8test12","8test13","8test14","8test15","8test16","8test17","8test18","8test19","8test20","8test21","8test22"), code.subCipher("9test1","9test2","9test3","9test4","9test5","9test6","9test7","9test8","9test9","9test10","9test11","9test12","9test13","9test14","9test15","9test16","9test17","9test18","9test19","9test20","9test21","9test22"), code.subCipher("10test1","10test2","10test3","10test4","10test5","10test6","10test7","10test8","10test9","10test10","10test11","10test12","10test13","10test14","10test15","10test16","10test17","10test18","10test19","10test20","10test21","10test22"), code.subCipher("11test1","11test2","11test3","11test4","11test5","11test6","11test7","11test8","11test9","11test10","11test11","11test12","11test13","11test14","11test15","11test16","11test17","11test18","11test19","11test20","11test21","11test22"), code.subCipher("12test1","12test2","12test3","12test4","12test5","12test6","12test7","12test8","12test9","12test10","12test11","12test12","12test13","12test14","12test15","12test16","12test17","12test18","12test19","12test20","12test21","12test22"), code.subCipher("13test1","13test2","13test3","13test4","13test5","13test6","13test7","13test8","13test9","13test10","13test11","13test12","13test13","13test14","13test15","13test16","13test17","13test18","13test19","13test20","13test21","13test22"), code.subCipher("14test1","14test2","14test3","14test4","14test5","14test6","14test7","14test8","14test9","14test10","14test11","14test12","14test13","14test14","14test15","14test16","14test17","14test18","14test19","14test20","14test21","14test22"), code.subCipher("15test1","15test2","15test3","15test4","15test5","15test6","15test7","15test8","15test9","15test10","15test11","15test12","15test13","15test14","15test15","15test16","15test17","15test18","15test19","15test20","15test21","15test22"), code.subCipher("16test1","16test2","16test3","16test4","16test5","16test6","16test7","16test8","16test9","16test10","16test11","16test12","16test13","16test14","16test15","16test16","16test17","16test18","16test19","16test20","16test21","16test22"), code.subCipher("17test1","17test2","17test3","17test4","17test5","17test6","17test7","17test8","17test9","17test10","17test11","17test12","17test13","17test14","17test15","17test16","17test17","17test18","17test19","17test20","17test21","17test22"), code.subCipher("18test1","18test2","18test3","18test4","18test5","18test6","18test7","18test8","18test9","18test10","18test11","18test12","18test13","18test14","18test15","18test16","18test17","18test18","18test19","18test20","18test21","18test22"), code.subCipher("19test1","19test2","19test3","19test4","19test5","19test6","19test7","19test8","19test9","19test10","19test11","19test12","19test13","19test14","19test15","19test16","19test17","19test18","19test19","19test20","19test21","19test22"), code.subCipher("20test1","20test2","20test3","20test4","20test5","20test6","20test7","20test8","20test9","20test10","20test11","20test12","20test13","20test14","20test15","20test16","20test17","20test18","20test19","20test20","20test21","20test22"), code.subCipher("21test1","21test2","21test3","21test4","21test5","21test6","21test7","21test8","21test9","21test10","21test11","21test12","21test13","21test14","21test15","21test16","21test17","21test18","21test19","21test20","21test21","21test22"), code.subCipher("22test1","22test2","22test3","22test4","22test5","22test6","22test7","22test8","22test9","22test10","22test11","22test12","22test13","22test14","22test15","22test16","22test17","22test18","22test19","22test20","22test21","22test22")/**/);

            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 23:{ //Load all player data
            //Load Player Stats:*******************************************************************************************************
            code.userDataDeliminationRead(1, code.getUsername()); //sets the items3 - 6 to the current stat values
            characters.pullRaceStats(players.getPlayerRace(code.getUsername()), code.getUsername());//set the stats of the Player for the race in their file
            //trying some junk
            string health = players.getHealthStat(code.getUsername());
            string armor = players.getArmorStat(code.getUsername());
            string magicResist = players.getMagicResistanceStat(code.getUsername());
            string physicalDam = players.getPhysicalDamageStat(code.getUsername(), true);
            string magicDam = players.getMagicDamageStat(code.getUsername(), true);
            string agility = players.getAgilityStat(code.getUsername());
            string stealth = players.getStealthStat(code.getUsername());
            string stamina = players.getStaminaStat(code.getUsername());
            string naturalEnergy = players.getManaStat(code.getUsername());
            string mind = players.getMindStat(code.getUsername());
            string psychicDam = players.getPsychicDamageStat(code.getUsername(), true);

            //get player location data************************************************************************************************
            code.userDataDeliminationRead(4, code.getUsername());
            string playerLocation = code.getItem(2);

            //sends the player's race, kit, level, weapon, and ability types***********************************************************
            Weapons weapons(code.getUsername());
            level = to_string(players.getLevel(code.getUsername()));
            //One insanely long statement to get a return message
            string race = players.getPlayerRace(code.getUsername());
            string playersKit = kit.getPlayerKit(code.getUsername());
            string weapon = weapons.getWeaponName();
            // level is needed before XP but after weapons 
            string PlayerXP = to_string(players.getXP(code.getUsername()));
            string NeededXP = to_string(battle.increaseXP(code.getUsername(), 0));
            string damageTypeQ = kit.getRaceDamageTypeForAbility(code.getUsername(), 'q');
            string damageTypeW = kit.getRaceDamageTypeForAbility(code.getUsername(), 'w');
            string damageTypeE = kit.getRaceDamageTypeForAbility(code.getUsername(), 'e');
            string damageTypeR = kit.getRaceDamageTypeForAbility(code.getUsername(), 'r');

            //current Quest Progress****************************************************************************************************
            code.userDataDeliminationRead(5, code.getUsername());//first number is the quest number, then second one is the progess number
            //need to add a function which determines the current quest that the user is working to complete and has not complete.
            /*
            
            please add here... then set that value to the variables below

            */
            string Questnumber = code.getItem(2);
            string QuestProgress = code.getItem(3);

            returnMessage = code.cipher("6", code.subCipher(health, armor, magicResist, physicalDam, magicDam, agility, stealth, stamina, naturalEnergy, mind, psychicDam, playerLocation, race, playersKit, weapon, level, PlayerXP, NeededXP, damageTypeQ, damageTypeW, damageTypeE, damageTypeR), code.subCipher(Questnumber, QuestProgress)); // This very long input put into simple terms calculates stats by adding base to bonus then spitting it out as a string for Health, armor, magicResistance, physicalDamage, MagicDamage, Agility
            
            sendToClient(socket, returnMessage);//send message back to the client
            break;
        }
        case 24:{ //save all player data
            //update user stats******************************************************************************
            code.userDataDeliminationWrite(5, code.getUsername(), code.getItem(3), code.getItem(4), code.getItem(5), code.getItem(6), code.getItem(7), code.getItem(8), code.getItem(9), code.getItem(10), code.getItem(11), code.getItem(12), code.getItem(13));
            returnMessage = code.cipher("4", "wasAbleToSave");
            sendToClient(socket, returnMessage);//send message back to the client
            //updates the players level and XP*****************************************************************
            //currently using the players level for the enemy's level for XP since they should be the same
            int enemyChoice;
            try{
                enemyChoice = stoi(code.getItem(3));
            } catch(std::invalid_argument){
                cout << "failed \"case 14:{//updates the players level and XP\"" << endl;
            }
            battle.increaseXP(code.getUsername(), enemy.getXPDrop(enemyChoice)); //hardset the enemies level to 1 since at this moment there is no level change for enemies
            returnMessage = code.cipher("4", to_string(players.getLevel(code.getUsername())));
            sendToClient(socket, returnMessage);//send message back to the client
            //update location data*******************************************************************************
            code.userDataDeliminationWrite(7, code.getUsername(), code.getItem(2));
            returnMessage = code.cipher("4", "wasAbleToSave");
            sendToClient(socket, returnMessage);//send message back to the client
            //update quest info***********************************************************************************
            code.userDataDeliminationWrite(8, code.getUsername(), code.getItem(2), code.getItem(3)); //first number is the quest number, then second one is the progess number
            returnMessage = code.cipher("4", "wasAbleToSave");
            sendToClient(socket, returnMessage);//send message back to the client
            

            break;
        }
        case 0:{//check for version compatibility - This is done before using can continue to create account or logon
            int gameVersionClient, gameMajorBuildClient, gameMinorBuildClient, gamePatchClient; //client game versions which we are going to test against the server's version
            try{
                gameVersionClient = stoi(code.getItem(3));
                gameMajorBuildClient = stoi(code.getItem(4));
                gameMinorBuildClient = stoi(code.getItem(5));
                gamePatchClient = stoi(code.getItem(6));
            } catch (std::invalid_argument){
                cout << "failed \"case 7:{//read the enemy stats for battle\"" << endl;
            }
            
            if (gameVersion == gameVersionClient){ //these nested if statements check to makte sure that the client version the user is using is the same as the valid client version on the server.
                if(gameMajorBuild == gameMajorBuildClient){
                    if (gameMinorBuild == gameMinorBuildClient){
                        if (gamePatch == gamePatchClient){
                            //then the version is current and can be used - return true
                            returnMessage = code.cipher("0", "true"); //send current version to client
                            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                            
                        } else {//then the version is NOT current and cannot be used - return false
                            returnMessage = code.cipher("0", "false"); //send current version to client
                            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                            
                        }
                    } else {//then the version is NOT current and cannot be used - return false
                        returnMessage = code.cipher("0", "false"); //send current version to client
                        sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                        
                    }
                } else {//then the version is NOT current and cannot be used - return false
                    returnMessage = code.cipher("0", "false"); //send current version to client
                    sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                    
                }
            } else {//then the version is NOT current and cannot be used - return false
                returnMessage = code.cipher("0", "false"); //send current version to client
                sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                
            }
            break;
        }
    }
    cout << "Return Message from Server: " << returnMessage << endl;
}

//this function takes an input of port when starting the run process of the program
void communicate(int argc, char* argv[]) { // the job of this function is to indefinitily accept incomming messages and send a message in response to them
    int sockfd, newsockfd, portno, pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char*)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr*)&serv_addr,
        sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    while (1) {
        newsockfd = accept(sockfd,
            (struct sockaddr*)&cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        pid = fork();
        if (pid < 0)
            error("ERROR on fork");
        if (pid == 0) {
            close(sockfd);
            dostuff(newsockfd);
            exit(0);
        }
        else close(newsockfd);
    } /* end of while */
    close(sockfd); /* we never get here */
}

/******** DOSTUFF() *********************
 There is a separate instance of this function
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
void dostuff(int sock) {
    int n;
    char buffer[8192]; //buffer size for recieving data from client
    bzero(buffer, 8192);
    //n = read(sock, buffer, 8192);
    int lengthOfMessage;
    n = recv(sock, buffer, 8192, 0); //MSG_WAITALL flag waits for whole message but will not work since 8192 is not the exact amount
    string s = buffer;// change the message into a string
    string token, output;
    int loopPass = 0;
    size_t pos = 0; // position variable for removing the delimiters to view the message
    if ((pos = s.find(delimiter)) != std::string::npos) { //this gets the number that is on the front of the message. This number is the length of the next message to be sent.
        token = s.substr(0, pos);
        output = token;
        s.erase(0, pos);
        //cout << n << endl;
        //cout << output << endl;
        try{
            lengthOfMessage = stoi(output); //convert the output to int so we can use it as length
        } catch(invalid_argument){
            cout << "void dostuff(int sock) { [specifically length check failed]" << endl;
        }
    }
    n = write(sock, output.c_str(), output.length()+1);//send confimation message back to the client (We know the length of the message which is about to be sent)
    if (n < 0) error("ERROR writing to socket");
    n = recv(sock, buffer, lengthOfMessage, MSG_WAITALL);
    if (n < 0) error("ERROR reading from socket");
    //cout << n << endl;


    //test message from user to see if it is within the function of requestActions
    requestActions(sock, buffer);
}

void premessageSendLengthVerification(int sock, int MessageLength){
    int n;
    char buffer[4096]; //buffer size for recieving data from client
    bzero(buffer, 4096);
    int sendResult = send(sock, (to_string(MessageLength + 1)  + "~").c_str(), (to_string(MessageLength + 1)  + "~").size() + 1, 0); //first is used to get length info
    n = recv(sock, buffer, 4096, 0); //wait to hear back from the client that this was recieved.
    if (n < 0) error("ERROR reading from socket");
    if (n > 0) {
        stringstream ssConvert;
        string responseVerified;
        ssConvert << buffer;
        responseVerified = ssConvert.str();
        //was for testing:
        //cout << "Recv: " << responseVerified << endl;
    }
}

void sendToClient(int socket, string message){ //this function is the standard messaging function which sends a message back to the client.
    int n;
    //Premessage verification:
    premessageSendLengthVerification(socket, message.length());
    n = write(socket, message.c_str(), message.length()+1);//send message back to the client
    if (n < 0) error("ERROR writing to socket");
}


//main function of the source.cpp file
int main(int argc, char* argv[]){
    cout << "Server Successfully Running..." << endl << "Press \"ctrl + c\" to stop the running program\nServer Version: " << to_string(ServerVersion) << "." << to_string(ServerMajorBuild) << "." << to_string(ServerMinorBuild) << "." << to_string(ServerPatch) << endl; //I use this line to make sure the server is running and test the compiles
    //Richard enter your test code below:

    communicate(argc, argv); //Start the servers function
    return 0; /* we never get here */
    //Test coder3 account github submit.
}