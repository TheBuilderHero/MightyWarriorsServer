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
    switch (stoi(code.getTypeOfRequest())) {
        case 1://check new users entered username against list of usernames to make sure it is unique
            message = code.decipher(messageFromClient); //unpack the message from the user
            testUsername.open("./userdata/" + code.getUsername() + "/" + code.getUsername() + ".dat"); //opens file to check if it exists
            if (testUsername) { // test user is true if it does exist and false if is does not // this means that when it exists you can not user that username
                testUsername.close();// closing opened file
                returnMessage = "0"; //not valid username - already in use
                returnMessage = code.cipher("1", returnMessage); //deliminates return message
                n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                if (n < 0) error("ERROR writing to socket");
            } else {
                returnMessage = "1";  //valid username - not in use
                returnMessage = code.cipher("1", returnMessage); // deliminates return message
                n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                if (n < 0) error("ERROR writing to socket");
            }
            break;
        case 2://this is the user creation type
            code.userDataDeliminationWrite(1, code.getUsername(), code.getItem(3));

            break;
        case 3://check logon info to confirm user identity - user logon
            int ableToLogon;
            ableToLogon = userLogon(code.getUsername(), code.getItem(3));
            returnMessage = code.cipher("3", to_string(ableToLogon));
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 4: //change password
            code.userDataDeliminationWrite(2, code.getUsername(), code.getItem(3));
            break;
        case 5: //write the user stats to file
            code.userDataDeliminationWrite(3, code.getUsername(), code.getItem(3), code.getItem(4), code.getItem(5), code.getItem(6), code.getItem(7), code.getItem(8), code.getItem(9), code.getItem(10), code.getItem(11));
            returnMessage = code.cipher("4", "wasAbleToSave");
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 6: //Making this read all user info form file  ---------------------------//try to read to user's stats from file - need to get this fully setup.
            code.userDataDeliminationRead(1, code.getUsername()); //sets the items3 - 6 to the current stat values
            characters.pullRaceStats(players.getPlayerRace(code.getUsername()), code.getUsername());//set the stats of the Player for the race in their file
            //set the proper stat values for the input of the base stats (This is used in the following long statment)
            returnMessage = code.cipher("5", players.getHealthStat(code.getUsername()), players.getArmorStat(code.getUsername()), players.getMagicResistanceStat(code.getUsername()), players.getPhysicalDamageStat(code.getUsername(), true), players.getMagicDamageStat(code.getUsername(), true), players.getAgilityStat(code.getUsername()), players.getStealthStat(code.getUsername()), 
            players.getStaminaStat(code.getUsername()), players.getManaStat(code.getUsername())); // This very long input put into simple terms calculates stats by adding base to bonus then spitting it out as a string for Health, armor, magicResistance, physicalDamage, MagicDamage, Agility
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
            
        case 7: //read the enemy stats for battle
            int enemyNumPicked, enemyLevel;
            srand (time(NULL)); //initialize random seed
            if(stoi(code.getItem(3)) == 1){
                if(stoi(code.getItem(4)) == 0){
                    enemyNumPicked = 0;
                }else{
                    enemyNumPicked = stoi(code.getItem(4)) + 90;
                }
            }else{
                enemyNumPicked = rand() % 13 + 1;     //in the range 1 to 12 //this is the type of enemy which you will fight
            }
            enemyLevel = 1; //level of boss
            returnMessage = code.cipher("5", enemy.getEnemyName(enemyNumPicked) ,battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "health"), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "armor"), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "magicResistance"), 
            battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "physicalDamage"), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "magicDamage")); //get all the values for the enemy to be sent to the client (Change 1 later so that it depends on input from client)
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 8:{ //user race, kit, and weapon selection and write to file
            // using code.getItem(3) from the client (which is raceChoice) and code.getItem(4) (which is kitChoice) we will determine the race which the user selected which is the reutrn of getPlayerRace
            int tempWeaponChoice = stoi(code.getItem(5));
            int tempRaceChoice = stoi(code.getItem(3));
            int tempKitChoice = stoi(code.getItem(4));
            Weapons weapons(code.getUsername(), true);
            weapons.setPlayerWeapon(tempWeaponChoice);
            weapons.~Weapons(); //call destructor to save weapon data
            code.userDataDeliminationWrite(1, code.getUsername(), players.getPlayerRace(code.getUsername(), tempRaceChoice), kit.getPlayerKit(code.getUsername(), tempKitChoice)); //write that race to file
            //instead of kit.kit we need to take code.getItem(4) and determine what kit they chose and input that.
            break;
            }
        case 9: //this takes the input of battle attacks to then reply with the damage amount.
            returnMessage = code.cipher("4", to_string(battle.determineOption(code.getUsername(), stoi(code.getItem(4)), enemy.getEnemyPickedFromName(code.getItem(3))))); //get the damage for one of the abilites and cipher return message.
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 10: //enemy attacks
            returnMessage = code.cipher("4", to_string(battle.determineEnemyAttackOption(code.getUsername(), enemy.getEnemyPickedFromName(code.getItem(3)), code.getItem(4)))); //get the damage for the enemy and cipher return message.
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 11: //check if enemy is blocking next attack
            returnMessage = code.cipher("5", to_string(battle.isEnemyBlocking()), to_string(battle.getBLOCK_REDUCTION_VALUE())); //get the damage for one of the abilites and cipher return message.
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 12: //send the user the abilities which correspond to thier damage types (e.g. their Q does magic, their E does phycial)
            returnMessage = code.cipher("5", kit.getRaceDamageTypeForAbility(code.getUsername(), 'q'), kit.getRaceDamageTypeForAbility(code.getUsername(), 'w'), 
            kit.getRaceDamageTypeForAbility(code.getUsername(), 'e'), kit.getRaceDamageTypeForAbility(code.getUsername(), 'r')); //send back the damage type per ability with the order q, w, e, r
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 13:{ //sends the players race, kit, level, and weapon
            Weapons weapons(code.getUsername());
            returnMessage = code.cipher("5", players.getPlayerRace(code.getUsername()), kit.getPlayerKit(code.getUsername()), weapons.getWeaponName()); //
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
            }
        case 14: //updates the players level and XP
            //currently using the players level for the enemy's level for XP since they should be the same
            battle.increaseXP(code.getUsername(), enemy.getXPDrop(enemy.getEnemyPickedFromName(code.getItem(3)))); //hardset the enemies level to 1 since at this moment there is no level change for enemies
            returnMessage = code.cipher("4", to_string(players.getLevel(code.getUsername())));
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 15: //returns player Level, current XP, and total needed xp for next level
            level = to_string(players.getLevel(code.getUsername())); //this is done to avoid issues with the increaseXP function breaking the update stats function on the client side
            returnMessage = code.cipher("5", level, to_string(players.getXP(code.getUsername())), to_string(battle.increaseXP(code.getUsername(), 0)));
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1); //send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 16: //update user stats
            code.userDataDeliminationWrite(5, code.getUsername(), code.getItem(3), code.getItem(4), code.getItem(5), code.getItem(6), code.getItem(7), code.getItem(8), code.getItem(9), code.getItem(10), code.getItem(11));
            returnMessage = code.cipher("4", "wasAbleToSave");
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 0: //check for version compatibility - This is done before using can continue to create account or logon
            int gameVersionClient, gameMajorBuildClient, gameMinorBuildClient, gamePatchClient; //client game versions which we are going to test against the server's version
            gameVersionClient = stoi(code.getItem(3));
            gameMajorBuildClient = stoi(code.getItem(4));
            gameMinorBuildClient = stoi(code.getItem(5));
            gamePatchClient = stoi(code.getItem(6));
            if (gameVersion == gameVersionClient){ //these nested if statements check to makte sure that the client version the user is using is the same as the valid client version on the server.
                if(gameMajorBuild == gameMajorBuildClient){
                    if (gameMinorBuild == gameMinorBuildClient){
                        if (gamePatch == gamePatchClient){
                            //then the version is current and can be used - return true
                            returnMessage = code.cipher("0", "true"); //send current version to client
                            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                            if (n < 0) error("ERROR writing to socket");
                        } else {//then the version is NOT current and cannot be used - return false
                            returnMessage = code.cipher("0", "false"); //send current version to client
                            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                            if (n < 0) error("ERROR writing to socket");
                        }
                    } else {//then the version is NOT current and cannot be used - return false
                        returnMessage = code.cipher("0", "false"); //send current version to client
                        n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                        if (n < 0) error("ERROR writing to socket");
                    }
                } else {//then the version is NOT current and cannot be used - return false
                    returnMessage = code.cipher("0", "false"); //send current version to client
                    n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                    if (n < 0) error("ERROR writing to socket");
                }
            } else {//then the version is NOT current and cannot be used - return false
                returnMessage = code.cipher("0", "false"); //send current version to client
                n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
                if (n < 0) error("ERROR writing to socket");
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
    char buffer[256];
    bzero(buffer, 256);
    n = read(sock, buffer, 255);
    if (n < 0) error("ERROR reading from socket");
    //printf("Here is the message from the User: %s\n", buffer);

    //test message from user to see if it is within the function of requestActions
    requestActions(sock, buffer);
}

//main function of the source.cpp file
int main(int argc, char* argv[]){
    cout << "Server Successfully Running..." << endl << "Press \"ctrl + c\" to stop the running program\nServer Version: " << to_string(ServerVersion) << "." << to_string(ServerMajorBuild) << "." << to_string(ServerMinorBuild) << "." << to_string(ServerPatch) << endl; //I use this line to make sure the server is running and test the compiles
    //Richard enter your test code below:

    communicate(argc, argv); //Start the servers function
    return 0; /* we never get here */
    //Test coder3 account github submit.
}