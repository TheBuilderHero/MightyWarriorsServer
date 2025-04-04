#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

//for threading:
#include <future>
#include <chrono>
#include <thread>
#include <iomanip>

#include "Enemies.h"
#include "Players.h"
#include "Characters.h"
#include "Cipher.h"
#include "Battle.h"
#include "PlayerElements/Kit.h"
#include "PlayerElements/Weapons.h"
#include "NPCData/NPC.h"
#include "globalVariables.h"


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
string delimiter = Delim.getDelimiterLayer1(); //a character that marks the beginning or end of a unit of data which is declared in the Cipher Class

string playerStartingX = "1";
string playerStartingY = "10";

void dostuff(int); /* function prototype */
void premessageSendLengthVerification(int socket, int MessageLength);
void sendToClient(int socket, string message);
void setupNPCData();
void runUsernameRequestResetDelay();

void runUsernameRequestResetDelay(){

}

void initializeAllElements(){
    setupNPCData();
    std::cout << "Initiallizing NPCs: ";
    for (int i = 0; i < 7; i ++) std::cout << to_string(npcs.at(i).getNpcID()) << " ";
    std::cout << endl;
    //Working to add dialogue into memory
    //This outputs all the npc's dialogue:
    /*
    for (int i = 0; i < npcs.size(); i++) {
        for(int i2 = 0; i2 < npcs.at(i).getDialoguePartCount(); i2++){
            for(int i3 = 0; i3 < npcs.at(i).getDialogueCount(i2); i3++){
                std::cout << npcs.at(i).getDialogue(i2, i3) << endl;
            }
        }
    }
    */
    //This specifically outputs the lines a certain NPC for both case 1 and 2 (or index 0 and 1)
    /*
    std::cout << "size: " << npcs.at(0).getDialogueCount(0) << endl;
    std::cout << "size: " << npcs.at(0).getDialogueCount(1) << endl;
    for(int i = 0; i < npcs.at(0).getDialogueCount(0); i++){
        std::cout << npcs.at(0).getDialogue(0, i) << endl;
    }
    for(int i = 0; i < npcs.at(0).getDialogueCount(1); i++){
        std::cout << npcs.at(0).getDialogue(1, i) << endl;
    }

    std::cout << endl;
    */
}

void setupNPCData(){ //THIS fuction sets up all the NPC's for the user to interact with
    //
    // Declare the NPC's in the game
    //
    
    //Enter these inputs: ("Name of the NPC", location on Map X, location on Map Y, In Landmark X, In Landmark Y)
    NPC npc1("Yol", 8,9,0,0);
    NPC npc2("Ggino", 8,9,1,0);
    NPC npc3("Inya", 8,9,2,0);
    NPC npc4("Nabban", 8,9,3,0);
    NPC npc5("Zeltrolt", 8,9,4,0);
    NPC npc6("Huldennii", 8,9,5,0);
    NPC npc7("Ronni Seaburger", 8,9,6,0);
    NPC npc8("Your Mom", 8,9,7,0);

    npcs.push_back(npc1);
    npcs.push_back(npc2);
    npcs.push_back(npc3);
    npcs.push_back(npc4);
    npcs.push_back(npc5);
    npcs.push_back(npc6);
    npcs.push_back(npc7);
    npcs.push_back(npc8);
}


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

    //this is threading code:
    int some_value = 123;
    auto const tb = std::chrono::system_clock::now();
    auto Time = [&]{
        return std::chrono::duration_cast<std::chrono::duration<double>>(
            std::chrono::system_clock::now() - tb).count();
    };
    
    //output the message recieved from the user to the consol.
    printf("V1.1-Here is the message from the User: %s\n", messageFromClient);

    //testing to see what action the user is requesting by switching between cases of typeOfRequest
    int request;
    try{
        request = stoi(code.getTypeOfRequest());
    } catch(std::invalid_argument){
        std::cout << "failed main: \"switch (request)\" in requestActions()" << endl;
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
            code.decipher(messageFromClient);
            code.userDataDeliminationWrite(9, code.getUsername(), code.getItem(3));
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
            string naturalEnergy = players.getNaturalEnergyStat(code.getUsername());
            string mind = players.getMindStat(code.getUsername());
            string psychicDam = players.getPsychicDamageStat(code.getUsername(), true);

            //set the proper stat values for the input of the base stats (This is used in the following long statment)
            returnMessage = code.cipher("5", health, armor, magicResist, physicalDam, magicDam, agility, stealth, stamina, naturalEnergy, mind, psychicDam); // This very long input put into simple terms calculates stats by adding base to bonus then spitting it out as a string for Health, armor, magicResistance, physicalDamage, MagicDamage, Agility
            //std::cout << "Return message write successful\n";
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
                std::cout << "failed \"case 7:{//read the enemy stats for battle\"" << endl;
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
            battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "physicalDamage"), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "magicDamage"), to_string(enemyNumPicked), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "mind"), to_string(enemy.getXPDrop(enemyNumPicked))); //get all the values for the enemy to be sent to the client (Change 1 later so that it depends on input from client)
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
                std::cout << "failed \"case 8:{ //user race, kit, and weapon selection and write to file\"" << endl;
            }
            Weapons weapons(code.getUsername(), true);
            weapons.setPlayerWeapon(tempWeaponChoice);
            weapons.~Weapons(); //call destructor to save weapon data
            code.userDataDeliminationWrite(1, code.getUsername(), players.getPlayerRace(code.getUsername(), tempRaceChoice), kit.getPlayerKit(code.getUsername(), tempKitChoice)); //write that race to file
            //Initialize player inventory
            code.userDataDeliminationWrite(9, code.getUsername(), (to_string(tempWeaponChoice) + "=0=0=0=0=0=0=0=0=0=0=0=0=0="));
            //instead of kit.kit we need to take code.getItem(4) and determine what kit they chose and input that.
            break;
            }
        case 9:{//this takes the input of battle attacks to then reply with the damage amount.
            int selectedOption;
            try{
                selectedOption = stoi(code.getItem(4));
            } catch(std::invalid_argument){
                std::cout << "failed \"case 9:{//this takes the input of battle attacks to then reply with the damage amount.\"" << endl;
            }
            returnMessage = code.cipher("5", to_string(battle.determineOption(code.getUsername(), selectedOption, enemy.getEnemyPickedFromName(code.getItem(3)), stoi(code.getItem(5)))), to_string(battle.isEnemyBlocking()), to_string(battle.getBLOCK_REDUCTION_VALUE())); //get the damage for one of the abilites and cipher return message.
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
            //std::cout << code.getItem(3) << "\n";
            int enemyChoice;
            try{
                enemyChoice = stoi(code.getItem(3));
            } catch(std::invalid_argument){
                std::cout << "failed \"case 14:{//updates the players level and XP\"" << endl;
            }
            //std::cout << enemy.getXPDrop(enemyChoice) << "\n";
            if(enemyChoice == -1){
                battle.increaseXP(code.getUsername(), stoi(code.getItem(4)));
            }else
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
            code.userDataDeliminationWrite(7, code.getUsername(), code.getItem(2), code.getItem(3));
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
            string naturalEnergy = players.getNaturalEnergyStat(code.getUsername());
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

            //Get inventory
            code.userDataDeliminationRead(6, code.getUsername());
            string inventoryString = code.getItem(2);

            returnMessage = code.cipher("6", code.subCipher(health, armor, magicResist, physicalDam, magicDam, agility, stealth, stamina, naturalEnergy, mind, psychicDam, playerLocation, race, playersKit, weapon, level, PlayerXP, NeededXP, damageTypeQ, damageTypeW, damageTypeE, damageTypeR), code.subCipher(Questnumber, QuestProgress), code.subCipher(inventoryString)); // This very long input put into simple terms calculates stats by adding base to bonus then spitting it out as a string for Health, armor, magicResistance, physicalDamage, MagicDamage, Agility
            
            sendToClient(socket, returnMessage);//send message back to the client
            break;
        }
        case 24:{ //save all player data
            //update user stats******************************************************************************
            code.subDecipher(code.getItem(3), 3); //all stats converted to sub cipher saves
            code.userDataDeliminationWrite(5, code.getUsername(), code.getItem(3,1), code.getItem(3,2), code.getItem(3,3), code.getItem(3,4), code.getItem(3,5), code.getItem(3,6), code.getItem(3,7), code.getItem(3,8), code.getItem(3,9), code.getItem(3,10), code.getItem(3,11));

            //updates the players level and XP*********************************************************************************
            code.userDataDeliminationWrite(4, code.getUsername(), "", "", code.getItem(3,12), code.getItem(3,13));

            //update location data*******************************************************************************
            code.userDataDeliminationWrite(7, code.getUsername(), code.getItem(3,14), code.getItem(3,15));

            //update inventory
            code.decipher(messageFromClient);
            code.userDataDeliminationWrite(9, code.getUsername(), code.getItem(4));

            /* //more needed to be done with this since there is more than one quest on the map. There will be close to possibly 100ish at least
            //update quest info***********************************************************************************
            code.userDataDeliminationWrite(8, code.getUsername(), code.getItem(2), code.getItem(3)); //first number is the quest number, then second one is the progess number
            */
            // Maybe working quest save code:
            //code.dataDeliminationWrite(code.QUEST_DATA, ) //this will not work... Need to make vector send for client to server.


            /* Still working to build the rest of the complete Data save code.

            returnMessage = code.cipher("4", "wasAbleToSave");
            sendToClient(socket, returnMessage);//send message back to the client

            int enemyChoice;
            try{
                enemyChoice = stoi(code.getItem(3));
            } catch(std::invalid_argument){
                std::cout << "failed \"case 14:{//updates the players level and XP\"" << endl;
            }
            battle.increaseXP(code.getUsername(), enemy.getXPDrop(enemyChoice)); //hardset the enemies level to 1 since at this moment there is no level change for enemies

            */
            

            break;
        }
        case 25:{//Get info for enemy groups
            srand(time(NULL));
            int enemyNumPicked, enemyLevel = 1, numberOfEnemies = stoi(code.getItem(5)); 
            vector<string> enemies(20);//most enemies we will have in a fight
            for(int i = 0; i < numberOfEnemies; i++){
                if(code.getItem(3) == "1"){
                    if(code.getItem(4) == "0"){
                        enemyNumPicked = 2;
                    }else{
                        enemyNumPicked = stoi(code.getItem(4)) + 90;
                    }
                }else if(code.getItem(6) == "1"){
                    enemyNumPicked = 13;
                }else{
                    enemyNumPicked = rand() % 12 + 1;
                }
                enemies.at(i) = code.subCipher(enemy.getEnemyName(enemyNumPicked), to_string(enemyNumPicked), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "health"), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "mind"), to_string(enemy.getXPDrop(enemyNumPicked)));//name, number, health, mind, XP
            }
            returnMessage = code.cipher("6", enemies.at(0), enemies.at(1), enemies.at(2), enemies.at(3), enemies.at(4), enemies.at(5), enemies.at(6), enemies.at(7), enemies.at(8),
            enemies.at(9), enemies.at(10), enemies.at(11), enemies.at(12), enemies.at(13), enemies.at(14), enemies.at(15), enemies.at(16), enemies.at(17), enemies.at(18), enemies.at(19));
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            break;
        }
        case 26:{//Group Enemy Attacks
            int numberOfEnemies = stoi(code.getItem(5));
            vector<int> randomizer(21);
            vector<int> enemyDamage(20);//most enemies we will have in a fight
            vector<string> enemyAttack(20);//most enemies we will have in a fight
            code.subDecipher(code.getItem(3), 0);
            srand(time(NULL));
            for(int i = 0; i < numberOfEnemies + 1; i++){
                randomizer.at(i) = rand()%100;

                //std::cout << "Here's a random number: " << randomizer.at(i) << endl;
            }
            for(int i = 0; i < numberOfEnemies; i++){
                enemyDamage.at(i) = battle.determineEnemyAttackOption(code.getUsername(), stoi(code.getItem(0, i+1)), code.getItem(4), randomizer.at(i+1));
                enemyAttack.at(i) = code.subCipher(to_string(enemyDamage.at(i)), battle.getAttackType());
            }
            
            returnMessage = code.cipher("6", enemyAttack.at(0), enemyAttack.at(1), enemyAttack.at(2), enemyAttack.at(3), enemyAttack.at(4), enemyAttack.at(5), enemyAttack.at(6), enemyAttack.at(7), enemyAttack.at(8), enemyAttack.at(9),
            enemyAttack.at(10), enemyAttack.at(11), enemyAttack.at(12), enemyAttack.at(13), enemyAttack.at(14), enemyAttack.at(15), enemyAttack.at(16), enemyAttack.at(17), enemyAttack.at(18), enemyAttack.at(19)); //get the damage for the enemy and cipher return message.
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            
            break;
        }
        case 27:{ //sending all dialogue data


            //output all info for the NPCS to message vector to be sent to client
            code.vectorDeliminateLayer1Head(code.VECTOR_SEND);
            code.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(code.DIALOGUE_INFO); //send type
            code.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer();// need to use Layer1OpenNewInput again since we are changing layers
            for (int i = 0; i < npcs.size(); i++) {
                code.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(npcs.at(i).getName());
                code.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(npcs.at(i).getAssignedMapX()));
                code.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(npcs.at(i).getAssignedMapY()));
                code.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(npcs.at(i).getAssignedLandmarkX()));
                code.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(npcs.at(i).getAssignedLandmarkY()));
                code.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer();
                //all dialogue for NPC i:
                for(int i2 = 0; i2 < npcs.at(i).getDialoguePartCount(); i2++){    
                    code.vectorDeliminateLayer3OpenNewInputOrSwitchDownLayer();
                    for(int i3 = 0; i3 < npcs.at(i).getDialogueCount(i2); i3++){
                        code.vectorDeliminateLayer4OpenNewInputOrSwitchDownLayer(npcs.at(i).getDialogue(i2, i3));
                        //code.vectorDeliminateBody(npcs.at(i).getDialogue(i2, i3));
                    }
                    code.vectorDeliminateLayer4EndInput();
                }
                if (npcs.at(i).getDialoguePartCount() == 0) code.vectorDeliminateLayer3OpenNewInputOrSwitchDownLayer(); //make sure the sub delimination is always enclosed even when no text
                code.vectorDeliminateLayer3EndInput();
            }
            code.vectorDeliminateLayer2EndInput();
            code.vectorDeliminateLayer1EndInput();

            //reset returnMessage message = ""
            returnMessage = "";
            for(int i = 0; i < code.getMESSAGESize(); i++){
                returnMessage += code.getMESSAGE(i);
            }
            
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client


            /*
            static vector<pair<string, int>> sentPosition(1, make_pair(code.getUsername(), 0));
            auto it = find_if(sentPosition.begin(), sentPosition.end(), [&code](const std::pair<std::string, int>& element){ return element.first == code.getUsername();} );
            if (it != sentPosition.end()){ //found the user
                //User already exists in the vector

                //determine where they are currently at with sending over all dialogue and pick up where we left off with sending over the rest of the dialogue

                //The proccess will be as follows
                    //Proccess:

                    //Check if user has requested dialogue before within the past minute or maybe 30 seconds or less
                        //YES?
                            //Since we have already sent data to this user we need to start where we left off.

                        //NO?
                            //start new send session of the character dialogue
                            //pack dialogue into send function
                            //send dialogue with leading number to tell it how many items of dialogue is being received.
                                //This will also include names of characters who are saying the dialogue
                                //Then we save the current step to the vector sentPosition and attach that to the name of the user
            } else {
                //User does not exist in the vector
                sentPosition.emplace_back(code.getUsername(), 0); //add user to the vector
                
                //should not need to do this: //test to make sure the vector is not full
                //int MAX_SEND_SIZE = 462;
                //int posx, posy, posz;

                
                


                //set delay to remove user from vector if they have not updated data in long enough amount of time.
                //Follow up on this for timeout:
                /*
                int tempValue = 0;
                auto res = std::async(std::launch::async, [&]{
                std::this_thread::sleep_for(std::chrono::seconds(60));
                if(tempValue == 0) std::cout << "Doing Delayed Task... at "<< Time() << " sec, value " << some_value << std::endl;
                });
                
               
            }*/
            break;
        }
        case 28:{ //Load all player data and send using new vector function 
            Cipher codeVector;
            std::string tempUsername = code.getUsername();
            codeVector.vectorDeliminateLayer1Head(codeVector.VECTOR_SEND);

            //Load Player Stats:*******************************************************************************************************

            //read the stats data from file:
            codeVector.userDataDeliminationRead(1, tempUsername); //sets the items3 - 6 to the current stat values
            characters.pullRaceStats(players.getPlayerRace(tempUsername), tempUsername);//set the stats of the Player for the race in their file
            //add the stats data to message:
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.STAT_INFO); //next input iem
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(); //use this if moving down to new lower layer
            //moved to data layer 2
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(players.getHealthStat(tempUsername));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(players.getArmorStat(tempUsername));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(players.getMagicResistanceStat(tempUsername));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(players.getPhysicalDamageStat(tempUsername, true));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(players.getMagicDamageStat(tempUsername, true));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(players.getAgilityStat(tempUsername));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(players.getStealthStat(tempUsername));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(players.getNaturalEnergyStat(tempUsername));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(players.getMindStat(tempUsername));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(players.getPsychicDamageStat(tempUsername, true));
            codeVector.vectorDeliminateLayer2EndInput();
            //move back up to layer 1
            //get player location data************************************************************************************************
            //read the location data from file
            codeVector.userDataDeliminationRead(4, tempUsername);
            //add the location data to message:
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.LOCATION_INFO); //send type
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer();
            string mapX = codeVector.getItem(2);
            string mapY = codeVector.getItem(3);
            if (mapX != "0" && mapX != "0") {
                codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(mapX); //X
                codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(mapY); //Y
            } else {
                codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(playerStartingX); //X
                codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(playerStartingY); //Y
            }
            codeVector.vectorDeliminateLayer2EndInput();
            //move back up to layer 1
            //sends the player's race, kit and, weapon**********************************************************************************************
            //read the weapons data from file
            Weapons weapons(tempUsername);
            level = to_string(players.getLevel(tempUsername));// level is needed before XP but after weapons due to some sort of ordering thing
            //add the race, kit and, weapon data to message:
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.RACE_KIT_WEAPON_INFO); //send type
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer();
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(players.getPlayerRace(tempUsername));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(kit.getPlayerKit(tempUsername));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(weapons.getWeaponName());
            codeVector.vectorDeliminateLayer2EndInput();
            //move back up to layer 1
            //sends the player's Level and XP info***********************************************************
                //read the level and xp data from file
                // level is needed before XP but after weapons due to some sort of ordering thing 
            //add the Level and XP info data to message:
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.LEVEL_XP_INFO); //send type
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer();
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(level);
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(players.getXP(tempUsername))); //current xp
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(to_string(battle.increaseXP(tempUsername, 0))); //xp till next level
            codeVector.vectorDeliminateLayer2EndInput();
            //move back up to layer 1
            //sends the player's ability type info***********************************************************
            //do not need to read the ability type info from a file
            //add the Level and XP info data to message:
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.ABILITY_TYPES_INFO); //send type
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer();
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(kit.getRaceDamageTypeForAbility(tempUsername, 'q'));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(kit.getRaceDamageTypeForAbility(tempUsername, 'w'));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(kit.getRaceDamageTypeForAbility(tempUsername, 'e'));
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(kit.getRaceDamageTypeForAbility(tempUsername, 'r'));
            codeVector.vectorDeliminateLayer2EndInput();
            //move back up to layer 1
            //current Quest Progress****************************************************************************************************
            //read the quest progress data from file
            codeVector.userDataDeliminationRead(5, tempUsername);//first number is the quest number, then second one is the progess number
            //need to add a function which determines the current quest that the user is working to complete and has not complete.
            
            //please add here... then set that value to the variables below
            
            //add the Quest Progress info data to message:
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.QUEST_PROGRESS); //send type
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer();
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(codeVector.getItem(2)); //quest number
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(codeVector.getItem(3)); //quest progress
            codeVector.vectorDeliminateLayer2EndInput();
            //move back up to layer 1
            //Inventory Information****************************************************************************************************
            //read the Inventory data from file
            codeVector.userDataDeliminationRead(6, tempUsername);
            //add the Inventory data to message:
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(codeVector.INVENTORY_INFO); //send type
            codeVector.vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(); //to lower layer
            codeVector.vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(codeVector.getItem(2)); //inventory data
            codeVector.vectorDeliminateLayer2EndInput();
            //moved back up to layer 1
            //end vector:
            codeVector.vectorDeliminateLayer1EndInput();

            //reset returnMessage message = ""
            returnMessage = "";
            //add all items in MESSAGE vector to return message to client
            for(int i = 0; i < codeVector.getMESSAGESize(); i++){
                returnMessage += codeVector.getMESSAGE(i);
            }
            
            sendToClient(socket, returnMessage);// returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            break;
        }
        case 29: { //recive vector data from client

            try {
                //std::cout << "Vector Message from Client was Properly Received..." << endl;
                std::cout << "Need to impliment decision making code to do with the data what needs to be done." << endl;

                //CODE IMPLIMENTATION for decision making:
                
                Cipher codeRVector;

                //Originally first made reques to server: //std::string serverData = sendToServer(codeRVector.getDelimiterLayer1()+convertRequestIDEnumToString(requestID)+codeRVector.getDelimiterLayer1()+player.getUsername()+codeRVector.getDelimiterLayer1());
                //Set the serverData has been swapped with clientData:
                string clientData = messageFromClient;
                string token;
                size_t posLayer1 = 0; // position variable for removing the delimiters to view the message
                vector<string> layer1;
                //cout << "STarting Phase 1 interations:" << endl;
                //remove the server send value first before processing the rest of the data:
                posLayer1 = clientData.find(codeRVector.getDelimiterLayer1());
                clientData.erase(0, posLayer1 + codeRVector.getDelimiterLayer1().length());
                posLayer1 = clientData.find(codeRVector.getDelimiterLayer1());
                string sendValue = clientData.substr(0, posLayer1);
                //also get the username from the information:
                posLayer1 = clientData.find(codeRVector.getDelimiterLayer1());
                clientData.erase(0, posLayer1 + codeRVector.getDelimiterLayer1().length());
                posLayer1 = clientData.find(codeRVector.getDelimiterLayer1());
                //set username:
                codeRVector.setUsername(clientData.substr(0, posLayer1));
                //remove leading delimiter:
                posLayer1 = clientData.find(codeRVector.getDelimiterLayer1());
                clientData.erase(0, posLayer1 + codeRVector.getDelimiterLayer1().length());

                //Put all the rest of the data in layer1 vector:
                while ((posLayer1 = clientData.find(codeRVector.getDelimiterLayer1())) != std::string::npos) {
                    token = clientData.substr(0, posLayer1);
                    layer1.emplace_back(token);
                    clientData.erase(0, posLayer1 + codeRVector.getDelimiterLayer1().length());
                    //cout << token << endl; //was for troubleshooting to determine the data coming from the server in each layer 1 section
                }
                bool lastLoopWasDIALOGUE_INFO = false;
                bool lastLoopWasSTAT_INFO = false;
                bool lastLoopWasENEMY_INFO= false;
                bool lastLoopWasLOCATION_INFO= false;
                bool lastLoopWasRACE_KIT_WEAPON_INFO= false;
                bool lastLoopWasQUEST_PROGRESS= false;
                bool lastLoopWasINVENTORY_INFO= false;
                bool lastLoopWasABILITY_TYPES_INFO= false;
                bool lastLoopWasLEVEL_XP_INFO= false;
                
                for(int i = 0; i < layer1.size(); i++){
                    //also more testing output:
                    //cout << "Loop #" << i << endl;
                    //cout << "Loop Info: " << layer1.at(i) << endl;
                    //complete

                    //Can Probably remove the dialogue send :
                    /*
                    size_t posLayer2DIALOGUE_INFO = 0; // position variable for removing the delimiters to view the message
                    vector<string> layer2DIALOGUE_INFO;
                    if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.DIALOGUE_INFO && !lastLoopWasDIALOGUE_INFO){
                        lastLoopWasDIALOGUE_INFO = true;
                        continue;
                    } else if (lastLoopWasDIALOGUE_INFO){

                        //then we create all the NPCs with the data from the current deliminations
                        bool secondLoopLayer2 = false;
                        lastLoopWasDIALOGUE_INFO = false;
                        //remove the first delimiter at the start or the layer2DIALOGUE_INFO information:
                        if ((posLayer2DIALOGUE_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2DIALOGUE_INFO + codeRVector.getDelimiterLayer2().length());
                        //then run through all the other data and add it to the vector: 
                        while ((posLayer2DIALOGUE_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) {
                            token = layer1.at(i).substr(0, posLayer2DIALOGUE_INFO);
                            layer2DIALOGUE_INFO.emplace_back(token);
                            layer1.at(i).erase(0, posLayer2DIALOGUE_INFO + codeRVector.getDelimiterLayer2().length());
                        }
                        string npcName = "";
                        string npcMapX = "";
                        string npcMapY = "";
                        string npcLandmarkX = "";
                        string npcLandmarkY = "";
                        //cout << "STarting Phase 4 interations:" << endl;
                        //cout << "size of layer 2: " << layer2DIALOGUE_INFO.size() << endl;
                        //for every chracter recived we run through determining their conversations:
                        for(int i2 = 0; i2 < layer2DIALOGUE_INFO.size(); i2++){
                            //set name of character since the first iteration will be the name of the character:
                            //then increment the current vector position to access the character's location
                            npcName = layer2DIALOGUE_INFO.at(i2++);
                            
                            //set location of character since the second iteration will be the assigned location of the character:
                            //then increment the current vector position to access the character's multple missions of clientData
                            npcMapX = layer2DIALOGUE_INFO.at(i2++); //mapX
                            npcMapY = layer2DIALOGUE_INFO.at(i2++); //mapY
                            npcLandmarkX = layer2DIALOGUE_INFO.at(i2++); //landmarkX
                            npcLandmarkY = layer2DIALOGUE_INFO.at(i2++); //landmarkY
                            
                            try{//create the NPCs:
                                string lines = layer2DIALOGUE_INFO.at(i2);
                                //trying to find issue to some error
                                npcs.emplace_back(npcName,stoi(npcMapX),stoi(npcMapY),stoi(npcLandmarkX),stoi(npcLandmarkY),lines);
                            }
                            catch(invalid_argument){                
                                cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.DIALOGUE_INFO && !lastLoopWasDIALOGUE_INFO)" << endl;
                            }
                        }
                    }
                    */



                    
                    size_t posLayer2STAT_INFO = 0; // position variable for removing the delimiters to view the message
                    vector<string> layer2STAT_INFO;
                    if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.STAT_INFO && !lastLoopWasSTAT_INFO){
                        lastLoopWasSTAT_INFO = true;
                        continue;
                    } else if (lastLoopWasSTAT_INFO){
                        lastLoopWasSTAT_INFO = false;
                        //remove the first delimiter at the start or the layer2 information:
                        if ((posLayer2STAT_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2STAT_INFO + codeRVector.getDelimiterLayer2().length());
                        
                        //then run through all the data and add it to the layer 2 vector: 
                        while ((posLayer2STAT_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) {
                            token = layer1.at(i).substr(0, posLayer2STAT_INFO);
                            layer2STAT_INFO.emplace_back(token);
                            layer1.at(i).erase(0, posLayer2STAT_INFO + codeRVector.getDelimiterLayer2().length());
                        }
                        //now we have the player's stats arranged in order in the vector: health, armor, magicresistance, physicaldamage (min and max), magicdamage (min and max), agility, stealth, NaturalEnergy, mind and, psychicdamage (min and max)

                        //Se now we can save all the player's stats to file as follows:
                        int positionForSTAT_INFO = 0;
                        try{
                            vector<pair<int,string>> statVec;
                            statVec.emplace_back(0,codeRVector.getUsername());
                            string healthTemp = layer2STAT_INFO.at(positionForSTAT_INFO);
                            statVec.emplace_back(1,healthTemp);
                            string maxHealthTemp = layer2STAT_INFO.at(positionForSTAT_INFO++);//same as the min health //later we will likely switch it to a current health option.
                            statVec.emplace_back(2,maxHealthTemp);
                            string armorTemp = layer2STAT_INFO.at(positionForSTAT_INFO++);
                            statVec.emplace_back(3,armorTemp);
                            string magicResistTemp = layer2STAT_INFO.at(positionForSTAT_INFO++);
                            statVec.emplace_back(4,magicResistTemp);
                            //find the seperator and pull the values out of it for the min and max:
                            string tempPhysicalDamageString = layer2STAT_INFO.at(positionForSTAT_INFO++);
                            size_t pos1 = tempPhysicalDamageString.find(codeRVector.getDelimiterMinMax());
                            string physicalDamageMinTemp = tempPhysicalDamageString.substr(0, pos1);
                            statVec.emplace_back(5,physicalDamageMinTemp);
                            tempPhysicalDamageString.erase(0, pos1 + codeRVector.getDelimiterMinMax().length());
                            string physicalDamageMaxTemp = tempPhysicalDamageString;
                            statVec.emplace_back(6,physicalDamageMaxTemp);
                            //find the seperator and pull the values out of it for the min and max:
                            string tempMagicDamageString = layer2STAT_INFO.at(positionForSTAT_INFO++);
                            pos1 = tempMagicDamageString.find(codeRVector.getDelimiterMinMax());
                            string magicDamageMinTemp = tempMagicDamageString.substr(0, pos1);
                            statVec.emplace_back(7,magicDamageMinTemp);
                            tempMagicDamageString.erase(0, pos1 + codeRVector.getDelimiterMinMax().length());
                            string magicDamageMaxTemp = tempMagicDamageString;
                            statVec.emplace_back(8,magicDamageMaxTemp);

                            string agilityTemp = layer2STAT_INFO.at(positionForSTAT_INFO++);
                            statVec.emplace_back(9,agilityTemp);
                            string stealthTemp = layer2STAT_INFO.at(positionForSTAT_INFO++);
                            statVec.emplace_back(10,stealthTemp);
                            string staminaTemp = layer2STAT_INFO.at(positionForSTAT_INFO++);
                            statVec.emplace_back(11,staminaTemp);
                            string naturalEnergy = layer2STAT_INFO.at(positionForSTAT_INFO++);
                            statVec.emplace_back(12,naturalEnergy);
                            string mindTemp = layer2STAT_INFO.at(positionForSTAT_INFO);
                            statVec.emplace_back(13,mindTemp);
                            string maxMindTemp = layer2STAT_INFO.at(positionForSTAT_INFO++);//same as min mind //maybe need to change this latter on.
                            statVec.emplace_back(14,maxMindTemp);
                            //find the seperator and pull the values out of it for the min and max:
                            string tempPsychicDamageString = layer2STAT_INFO.at(positionForSTAT_INFO++);
                            pos1 = tempPsychicDamageString.find(codeRVector.getDelimiterMinMax());
                            string psychicDamageMinTemp = tempPsychicDamageString.substr(0, pos1);
                            statVec.emplace_back(15,psychicDamageMinTemp);
                            tempPsychicDamageString.erase(0, pos1 + codeRVector.getDelimiterMinMax().length());
                            string psychicDamageMaxTemp = tempPsychicDamageString;
                            statVec.emplace_back(16,psychicDamageMaxTemp);

                            //New function to write all the above to file:
                            //cout << "sendValue use: " << sendValue << endl;
                            //cout << "Username use: " << codeRVector.getUsername() << endl;
                            codeRVector.writeToFile(codeRVector.STAT_DATA, codeRVector.getUsername(),statVec);
                        }
                        catch(invalid_argument){
                            cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.STAT_INFO && !lastLoopWasSTAT_INFO) ARGUMENT" << endl;
                        }
                        catch(out_of_range){
                            cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.STAT_INFO && !lastLoopWasSTAT_INFO) RANGE" << endl;
                        }

                    }
                    //need to determine best way to load dynamic number of enemies:
                    if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.ENEMY_INFO && !lastLoopWasENEMY_INFO){
                        lastLoopWasENEMY_INFO = true;
                        continue;
                    } else if (lastLoopWasENEMY_INFO){
                        lastLoopWasENEMY_INFO = false;

                    }


                    //complete
                    size_t posLayer2LOCATION_INFO = 0; // position variable for removing the delimiters to view the message
                    if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.LOCATION_INFO && !lastLoopWasLOCATION_INFO){
                        lastLoopWasLOCATION_INFO = true;
                        continue;
                    } else if (lastLoopWasLOCATION_INFO){
                        lastLoopWasLOCATION_INFO = false;
                        
                        //remove the first delimiter at the start or the layer2 information:
                        if ((posLayer2LOCATION_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2LOCATION_INFO + codeRVector.getDelimiterLayer2().length());

                        try{
                            vector<pair<int,string>> tempLocation;
                            posLayer2LOCATION_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2());
                            token = layer1.at(i).substr(0, posLayer2LOCATION_INFO);
                            string x = token;
                            layer1.at(i).erase(0, posLayer2LOCATION_INFO + codeRVector.getDelimiterLayer2().length());
                            
                            posLayer2LOCATION_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2());
                            token = layer1.at(i).substr(0, posLayer2LOCATION_INFO);
                            string y = token;
                            layer1.at(i).erase(0, posLayer2LOCATION_INFO + codeRVector.getDelimiterLayer2().length());
                            tempLocation.emplace_back(1,x);
                            tempLocation.emplace_back(2,y);

                            //old from server: //player.setMapLocation(x,y);
                            codeRVector.writeToFile(codeRVector.LOCATION_DATA, codeRVector.getUsername(), tempLocation);
                        }
                        catch(invalid_argument){
                            cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.LOCATION_INFO && !lastLoopWasLOCATION_INFO)" << endl;
                        }
                        catch(out_of_range){
                            cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.LOCATION_INFO && !lastLoopWasLOCATION_INFO) RANGE" << endl;
                        }

                    }
                    // probably complete
                    size_t posLayer2RACE_KIT_WEAPON_INFO = 0; // position variable for removing the delimiters to view the message
                    try{
                        vector<string> layer2RACE_KIT_WEAPON_INFO;
                        if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.RACE_KIT_WEAPON_INFO && !lastLoopWasRACE_KIT_WEAPON_INFO){
                            lastLoopWasRACE_KIT_WEAPON_INFO = true;
                            continue;
                        } else if (lastLoopWasRACE_KIT_WEAPON_INFO){
                            lastLoopWasRACE_KIT_WEAPON_INFO = false;
                            
                            //remove the first delimiter at the start or the layer2RACE_KIT_WEAPON_INFO information:
                            if ((posLayer2RACE_KIT_WEAPON_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2RACE_KIT_WEAPON_INFO + codeRVector.getDelimiterLayer2().length());

                            //then run through all the data and add it to the layer 2 vector: 
                            while ((posLayer2RACE_KIT_WEAPON_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) {
                                token = layer1.at(i).substr(0, posLayer2RACE_KIT_WEAPON_INFO);
                                layer2RACE_KIT_WEAPON_INFO.emplace_back(token);
                                layer1.at(i).erase(0, posLayer2RACE_KIT_WEAPON_INFO + codeRVector.getDelimiterLayer2().length());
                            }
                            int positionForRACE_KIT_WEAPON_INFO = 0;
                            string race = layer2RACE_KIT_WEAPON_INFO.at(positionForRACE_KIT_WEAPON_INFO++);
                            string kit = layer2RACE_KIT_WEAPON_INFO.at(positionForRACE_KIT_WEAPON_INFO++);
                            string weapon = layer2RACE_KIT_WEAPON_INFO.at(positionForRACE_KIT_WEAPON_INFO++);
                            vector<pair<int,string>> tempVec;
                            tempVec.emplace_back(1,race);
                            tempVec.emplace_back(2,kit);
                            tempVec.emplace_back(3,weapon);
                            codeRVector.writeToFile(codeRVector.RACE_KIT_WEAPON_DATA, codeRVector.getUsername(), tempVec);
                        }

                    }
                    catch(invalid_argument){
                        cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.RACE_KIT_WEAPON_INFO && !lastLoopWasRACE_KIT_WEAPON_INFO)" << endl;
                    }
                    catch(out_of_range){
                        cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.RACE_KIT_WEAPON_INFO && !lastLoopWasRACE_KIT_WEAPON_INFO) RANGE" << endl;
                    }

                    //probably complete
                    size_t posLayer2QUEST_PROGRESS = 0; // position variable for removing the delimiters to view the message
                    try{
                        vector<string> layer2QUEST_PROGRESS;
                        if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.QUEST_PROGRESS && !lastLoopWasQUEST_PROGRESS){
                            lastLoopWasQUEST_PROGRESS = true;
                            continue;
                        } else if (lastLoopWasQUEST_PROGRESS){
                            lastLoopWasQUEST_PROGRESS = false;
                            
                            //remove the first delimiter at the start or the layer2QUEST_PROGRESS information:
                            if ((posLayer2QUEST_PROGRESS = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2QUEST_PROGRESS + codeRVector.getDelimiterLayer2().length());

                            //then run through all the data and add it to the layer 2 vector: 
                            while ((posLayer2QUEST_PROGRESS = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) {
                                token = layer1.at(i).substr(0, posLayer2QUEST_PROGRESS);
                                layer2QUEST_PROGRESS.emplace_back(token);
                                layer1.at(i).erase(0, posLayer2QUEST_PROGRESS + codeRVector.getDelimiterLayer2().length());
                            }
                            unsigned short indexQUEST_PROGRESS = 0;
                            //save to player info:
                            vector<pair<int,string>> tempVec;
                            for(int i = 0; i < layer2QUEST_PROGRESS.size(); i++){
                                //player.setQuest1Progress(stoi(layer2QUEST_PROGRESS.at(indexQUEST_PROGRESS++)),stoi(layer2QUEST_PROGRESS.at(indexQUEST_PROGRESS++))); //quest number, progress
                                //place the mission id and progress into the vector:
                                tempVec.emplace_back(stoi(layer2QUEST_PROGRESS.at(indexQUEST_PROGRESS)),layer2QUEST_PROGRESS.at(indexQUEST_PROGRESS)); //removed ++indexQUEST_PROGRESS from second argument...
                                ++indexQUEST_PROGRESS;
                            }
                            //save all to file:
                            codeRVector.writeToFile(codeRVector.QUEST_PROGRESS_DATA, codeRVector.getUsername(), tempVec);
                        }
                    }
                    catch(invalid_argument){
                        cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.QUEST_PROGRESS && !lastLoopWasQUEST_PROGRESS)" << endl;
                    }
                    catch(out_of_range){
                        cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.QUEST_PROGRESS && !lastLoopWasQUEST_PROGRESS) RANGE" << endl;
                    }

                    //probably complete
                    size_t posLayer2INVENTORY_INFO = 0; // position variable for removing the delimiters to view the message
                    try{
                        vector<string> layer2INVENTORY_INFO;
                        if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.INVENTORY_INFO && !lastLoopWasINVENTORY_INFO){
                            lastLoopWasINVENTORY_INFO = true;
                            continue;
                        } else if (lastLoopWasINVENTORY_INFO){
                            lastLoopWasINVENTORY_INFO = false;
                            
                            //remove the first delimiter at the start or the layer2INVENTORY_INFO information:
                            if ((posLayer2INVENTORY_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2INVENTORY_INFO + codeRVector.getDelimiterLayer2().length());

                            //then run through all the data and add it to the layer 2 vector: 
                            while ((posLayer2INVENTORY_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) {
                                token = layer1.at(i).substr(0, posLayer2INVENTORY_INFO);
                                layer2INVENTORY_INFO.emplace_back(token);
                                layer1.at(i).erase(0, posLayer2INVENTORY_INFO + codeRVector.getDelimiterLayer2().length());
                            }
                            unsigned short indexINVENTORY_INFO = 0;
                            //save to player info:
                            vector<pair<int,string>> tempVec;
                            for (int index = 0; index < layer2INVENTORY_INFO.size(); index++ ){
                                //adds every weapon to the inventory in the order in which they were stored in the file
                                //server: //player.setInventory(index,stoi(layer2INVENTORY_INFO.at(index)));
                                //add all items to inventory:
                                tempVec.emplace_back(index,layer2INVENTORY_INFO.at(index));
                            }
                            //save all to file:
                            codeRVector.writeToFile(codeRVector.INVENTORY_DATA, codeRVector.getUsername(), tempVec);

                        }
                    }
                    catch(invalid_argument){
                        cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.INVENTORY_INFO && !lastLoopWasINVENTORY_INFO)" << endl;
                    }
                    catch(out_of_range){
                        cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.INVENTORY_INFO && !lastLoopWasINVENTORY_INFO) RANGE" << endl;
                    }
                    //probably complete
                    size_t posLayer2ABILITY_TYPES_INFO = 0; // position variable for removing the delimiters to view the message
                    try{
                        vector<string> layer2ABILITY_TYPES_INFO;
                        if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.ABILITY_TYPES_INFO && !lastLoopWasABILITY_TYPES_INFO){
                            lastLoopWasABILITY_TYPES_INFO = true;
                            continue;
                        } else if (lastLoopWasABILITY_TYPES_INFO){
                            lastLoopWasABILITY_TYPES_INFO = false;
                            
                            //remove the first delimiter at the start or the layer2ABILITY_TYPES_INFO information:
                            if ((posLayer2ABILITY_TYPES_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2ABILITY_TYPES_INFO + codeRVector.getDelimiterLayer2().length());

                            //then run through all the data and add it to the layer 2 vector: 
                            while ((posLayer2ABILITY_TYPES_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) {
                                token = layer1.at(i).substr(0, posLayer2ABILITY_TYPES_INFO);
                                layer2ABILITY_TYPES_INFO.emplace_back(token);
                                layer1.at(i).erase(0, posLayer2ABILITY_TYPES_INFO + codeRVector.getDelimiterLayer2().length());
                            }
                            unsigned short indexABILITY_TYPES_INFO = 0;
                            //save to player info:
                            vector<pair<int,string>> tempVec;
                            tempVec.emplace_back(indexABILITY_TYPES_INFO+1, layer2ABILITY_TYPES_INFO.at(indexABILITY_TYPES_INFO++));
                            tempVec.emplace_back(indexABILITY_TYPES_INFO+1, layer2ABILITY_TYPES_INFO.at(indexABILITY_TYPES_INFO++));
                            tempVec.emplace_back(indexABILITY_TYPES_INFO+1, layer2ABILITY_TYPES_INFO.at(indexABILITY_TYPES_INFO++));
                            tempVec.emplace_back(indexABILITY_TYPES_INFO+1, layer2ABILITY_TYPES_INFO.at(indexABILITY_TYPES_INFO++));
                            codeRVector.writeToFile(codeRVector.ABILITY_TYPES_DATA, codeRVector.getUsername(), tempVec);
                        }
                    }
                    catch(invalid_argument){
                        cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.ABILITY_TYPES_INFO && !lastLoopWasABILITY_TYPES_INFO)" << endl;
                    }
                    catch(out_of_range){
                        cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.ABILITY_TYPES_INFO && !lastLoopWasABILITY_TYPES_INFO) RANGE" << endl;
                    }
                    //probably complete
                    //first level, then current xp, then xp till next level
                    size_t posLayer2LEVEL_XP_INFO = 0; // position variable for removing the delimiters to view the message
                    try{
                        vector<string> layer2LEVEL_XP_INFO;
                        if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.LEVEL_XP_INFO && !lastLoopWasLEVEL_XP_INFO){
                            lastLoopWasLEVEL_XP_INFO = true;
                            continue;
                        } else if (lastLoopWasLEVEL_XP_INFO){
                            lastLoopWasLEVEL_XP_INFO = false;
                            
                            //remove the first delimiter at the start or the layer2LEVEL_XP_INFO information:
                            if ((posLayer2LEVEL_XP_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) layer1.at(i).erase(0, posLayer2LEVEL_XP_INFO + codeRVector.getDelimiterLayer2().length());

                            //then run through all the data and add it to the layer 2 vector: 
                            while ((posLayer2LEVEL_XP_INFO = layer1.at(i).find(codeRVector.getDelimiterLayer2())) != std::string::npos) {
                                token = layer1.at(i).substr(0, posLayer2LEVEL_XP_INFO);
                                layer2LEVEL_XP_INFO.emplace_back(token);
                                layer1.at(i).erase(0, posLayer2LEVEL_XP_INFO + codeRVector.getDelimiterLayer2().length());
                            }
                            unsigned short indexLEVEL_XP_INFO = 0;
                            //save to player info:
                            vector<pair<int,string>> tempVec;
                            tempVec.emplace_back(indexLEVEL_XP_INFO+1, layer2LEVEL_XP_INFO.at(indexLEVEL_XP_INFO++));
                            tempVec.emplace_back(indexLEVEL_XP_INFO+1, layer2LEVEL_XP_INFO.at(indexLEVEL_XP_INFO++));
                            tempVec.emplace_back(indexLEVEL_XP_INFO+1, layer2LEVEL_XP_INFO.at(indexLEVEL_XP_INFO++));
                            //Cliient way:
                            //player.setLevel(stoi(layer2LEVEL_XP_INFO.at(indexLEVEL_XP_INFO++)));
                            //player.setCurrentXP(stoi(layer2LEVEL_XP_INFO.at(indexLEVEL_XP_INFO++)));
                            //player.setXPForNextLevel(stoi(layer2LEVEL_XP_INFO.at(indexLEVEL_XP_INFO++)));
                            codeRVector.writeToFile(codeRVector.LEVEL_XP_DATA, codeRVector.getUsername(), tempVec);
                        }
                    } catch(invalid_argument){
                        cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.LEVEL_XP_INFO && !lastLoopWasLEVEL_XP_INFO) ARGUMENT" << endl;
                    } catch(out_of_range){
                        cout << "Critical Failure in source.cpp -> if (codeRVector.convertToDATA_TYPE(layer1.at(i)) == codeRVector.LEVEL_XP_INFO && !lastLoopWasLEVEL_XP_INFO) RANGE" << endl;
                    }
                //output all NPC data for testing:
                //cout << "NPCS size: " << npcs.size() << endl;
                //npcs.at(0).getAllDialogue();
                }

            
            } catch(out_of_range){
                cout << "Critical Failure in source.cpp -> case 29: { //recive vector data from client --> RANGE" << endl;
            }

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
                std::cout << "failed \"case 0:{//check compatibility\"" << endl;
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
    std::cout << "Return Message from Server: " << returnMessage << endl;
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
    
    std::cout << "Server Successfully Running..." << endl << "Press \"ctrl + c\" to stop the running program\nServer Version: " << to_string(ServerVersion) << "." << to_string(ServerMajorBuild) << "." << to_string(ServerMinorBuild) << "." << to_string(ServerPatch) << endl; //I use this line to make sure the server is running and test the compiles

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
        //std::cout << n << endl;
        //std::cout << output << endl;
        try{
            lengthOfMessage = stoi(output); //convert the output to int so we can use it as length
        } catch(invalid_argument){
            std::cout << "void dostuff(int sock) { [specifically length check failed]" << endl;
        }
    }
    n = write(sock, output.c_str(), output.length()+1);//send confimation message back to the client (We know the length of the message which is about to be sent)
    if (n < 0) error("ERROR writing to socket");
    n = recv(sock, buffer, lengthOfMessage, MSG_WAITALL);
    if (n < 0) error("ERROR reading from socket");
    //std::cout << n << endl;


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
        //std::cout << "Recv: " << responseVerified << endl;
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
    //Enter your test code below: V ****

    //runUsernameRequestResetDelay();
    
    //testingSend();
    // assigning value to string s

    /*******************************************
     * Test code for testing send.
     */
    std::string s = "~29~kota~stats~=150=60=55=55 - 75=2 - 2=0=-5=0=10=0 - 0=~locationinfo~=1=10=~racekitweaponinfo~=human=tank=Sword=~levelxpinfo~=1=0=500=~questinfo~=~inventoryinfo~=0=0=0=0=0=0=0=0=0=0=0=0=~";
 
    const int length = s.length();
 
    // declaring character array (+1 for null terminator)
    char* char_array = new char[length + 1];
 
    // copying the contents of the
    // string to char array
    strcpy(char_array, s.c_str());
    requestActions(1, char_array);
    /************************************************/
    
    
    //Enter test code above ^ *****
    //This is the needed server code:
    initializeAllElements(); //Initialize Server elements 
    communicate(argc, argv); //Start the Servers function
    return 0; /* we never get here */
}

