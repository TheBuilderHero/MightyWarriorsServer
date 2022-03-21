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

//********************************************
const int gameVersion     = 1;
const int gameMajorBuild  = 0;
const int gameMinorBuild  = 0;
const int gamePatch       = 0;
//********************************************

using namespace std;
string delimiter = "~"; //a character that marks the beginning or end of a unit of data

void dostuff(int); /* function prototype */

//this function is called for an error and used to exit the program
void error(const char* msg)
{
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

void requestActions(int socket, char messageFromClient[]) {
    Cipher code;
    ifstream testUsername;
    string returnMessage = "0"; //this is hard setting the function to always say that the username does not exist.  This will need to be changed to checking for usernames use.
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
        case 5:
            code.userDataDeliminationWrite(3, "", code.item3, code.item4, code.item5, code.item6);
            returnMessage = code.cipher("4", "wasAbleToSave");
            n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
            if (n < 0) error("ERROR writing to socket");
            break;
        case 0: //check for version compatibility - This is done before using can continue to create account or logon
            int gameVersionT, gameMajorBuildT, gameMinorBuildT, gamePatchT; //client game versions which we are going to test against the server's version
            gameVersionT = stoi(code.item3);
            gameMajorBuildT = stoi(code.item4);
            gameMinorBuildT = stoi(code.item5);
            gamePatchT = stoi(code.item6);
            if (gameVersion == gameVersionT){
                if(gameMajorBuild == gameMajorBuildT){
                    if (gameMinorBuild == gameMinorBuildT){
                        if (gamePatch == gamePatchT){
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
void communicate(int argc, char* argv[])
{ // the job of this function is to indefinitily accept incomming messages and send a message in response to them
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
    cout << "Server Started..." << endl << "Press \"ctrl + c\" to stop the running program 1.4" << endl; //I use this line to make sure the server is running and test the compiles
    
    Enemies test;     
    test.mutantElf();  //testing the multie file classes

    communicate(argc, argv); //Start the servers function
    return 0; /* we never get here */
}