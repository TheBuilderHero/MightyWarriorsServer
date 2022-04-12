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
string delimiter = "~"; //a character that marks the beginning or end of a unit of data
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
    
    //output the message recieved from the user to the consol.
    printf("V1.1-Here is the message from the User: %s\n", messageFromClient);

    //testing to see what action the user is requesting by switching between cases of typeOfRequest
    switch (stoi(code.typeOfRequest)) {
        case 1://check new users entered username against list of usernames to make sure it is unique
            message = code.decipher(messageFromClient); //unpack the message from the user
            testUsername.open("./userdata/" + code.username + "/" + code.username + ".dat"); //opens file to check if it exists
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
            code.userDataDeliminationWrite(1, code.username, code.item3);

            break;
        case 3://check logon info to confirm user identity - user logon
            int ableToLogon;
            ableToLogon = userLogon(code.username, code.item3);
            returnMessage = code.cipher("3", to_string(ableToLogon));
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 4: //change password
            code.userDataDeliminationWrite(2, code.username, code.item3);
            break;
        case 5: //write the user stats to file
            code.userDataDeliminationWrite(3, code.username, code.item3, code.item4, code.item5, code.item6, code.item7, code.item8, code.item9, code.item10);
            returnMessage = code.cipher("4", "wasAbleToSave");
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 6: //Making this read all user info form file  ---------------------------//try to read to user's stats from file - need to get this fully setup.
            code.userDataDeliminationRead(1, code.username); //sets the items3 - 6 to the current stat values
            characters.pullRaceStats(players.getPlayerRace(code.username), code.username);//set the stats of the Player for the race in their file
            // old way to test: characters.Human(code.username); //set the proper stat values for the input of the base stats (This is used in the following long statment)
            returnMessage = code.cipher("5", players.getHealthStat(code.username, characters.baseHealth, stoi(code.item2)), players.getArmorStat(code.username, characters.baseArmor, stoi(code.item3)),
            players.getMagicResistanceStat(code.username, characters.baseMagicResistance, stoi(code.item4)), players.getPhysicalDamageStat(code.username, characters.basePhysicalDamage, stoi(code.item5)), 
            players.getMagicDamageStat(code.username, characters.baseMagicDamage, stoi(code.item6))); // This very long input put into simple terms calculates stats by adding base to bonus then spitting it out as a string for Health, armor, magicResistance, physicalDamage, MagicDamage, Agility
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 7: //read the enemy stats for battle
            int enemyNumPicked, enemyLevel;
            enemyNumPicked = 2; //this is the type of enemy which you will fight
            enemyLevel = 1; //level of boss
            returnMessage = code.cipher("5", enemy.getEnemyName(enemyNumPicked) ,battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "health"), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "armor"), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "magicResistance"), 
            battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "physicalDamage"), battle.getEnemyBattleStats(enemyNumPicked, enemyLevel, "magicDamage")); //get all the values for the enemy to be sent to the client (Change 1 later so that it depends on input from client)
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 8: //user race selection and write to file
            // using code.item3 from the client (which is raceChoice) and code.item4 (which is kitChoice) we will determine the race which the user selected which is the reutrn of getPlayerRace
            code.userDataDeliminationWrite(1, code.username, players.getPlayerRace(code.username, stoi(code.item3)), kit.getPlayerKit(code.username, stoi(code.item4))); //write that race to file
            //instead of kit.kit we need to take code.item4 and determine what kit they chose and input that.
            break;
        case 9: //this takes the input of battle attacks to then reply with the damage amount.
            returnMessage = code.cipher("4", to_string(battle.determineOption(code.username, stoi(code.item4), "Magic", enemy.getEnemyPickedFromName(code.item3)))); //get the damage for the Q ability and cipher return message.
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 0: //check for version compatibility - This is done before using can continue to create account or logon
            int gameVersionClient, gameMajorBuildClient, gameMinorBuildClient, gamePatchClient; //client game versions which we are going to test against the server's version
            gameVersionClient = stoi(code.item3);
            gameMajorBuildClient = stoi(code.item4);
            gameMinorBuildClient = stoi(code.item5);
            gamePatchClient = stoi(code.item6);
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
    Battle battle;
    cout << "Server Successfully Running..." << endl << "Press \"ctrl + c\" to stop the running program\nServer Version: " << to_string(ServerVersion) << "." << to_string(ServerMajorBuild) << "." << to_string(ServerMinorBuild) << "." << to_string(ServerPatch) << endl; //I use this line to make sure the server is running and test the compiles
    cout << "Q: " << battle.doQOption("kota3","Physical", 1) << endl;
    communicate(argc, argv); //Start the servers function
    return 0; /* we never get here */
    //Test coder3 account github submit.
}