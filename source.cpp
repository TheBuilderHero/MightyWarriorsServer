#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>

using namespace std;

void dostuff(int); /* function prototype */

//defining the player and all their caracteristics and items
class Player {
    public:
        string name;
        string race; // is one of the following: Human - Elf - Dino - Dryad - Ghost
        double baseHealth, baseDefense, baseAbility, baseAgility, baseDamage;
        double xp;
        int level;
        
        struct playersWeapon{
            string weaponName;
            int weaponPower;
        };
        
};


//this function is called for an error and used to exit the program
void error(const char* msg)
{
    perror(msg);
    exit(1);
}

//this function is intended to pull out the users request and the data associated with each request
string decipher(char messageFromClient[]){
    string delimiter = "~"; //a character that marks the beginning or end of a unit of data

    string item1, item2, item3, item4, item5, item6, item7; // declare the variables that are being used to store the message from the client
    // the above variables may later be replaced with a more wide veriety of variables however, for testing we are using all strings
    string s = messageFromClient;// change the message into a string
    string str_file_content;
    string token, output;
    int loopPass = 0;
    size_t pos = 0; // position variable for removing the delimiters to view the message
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        output = token;
        str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
        s.erase(0, pos + delimiter.length());
        
        switch (loopPass){
            case 1: //first item after delimiter
            if (output.length() > 0) item1 = output; // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
            break;
            case 2://second item after delimiter
            if (output.length() > 0) item2 = output;
            break;
            case 3://third item after delimiter
            if (output.length() > 0) item3 = output;
            break;
            case 4://forth item after delimiter
            if (output.length() > 0) item4 = output;
            break;
            case 5://fith item after delimiter
            if (output.length() > 0) item5 = output;
            break;
            case 6://sixth item after delimiter
            if (output.length() > 0) item6 = output;
            break;
            case 7://seventh item after delimiter
            if (output.length() > 0) item7 = output;
            break;
        }
        loopPass++;
    }
    return str_file_content;
}

//this functions purpose it to add the delimiters to given items 
string cipher(string item1 = "", string item2= "", string item3= "", string item4= "", string item5= "", string item6= "", string item7= ""){ // the default values have been set to "" in case no input is given
    int numberOfItems = 7; //max number of items that we can cipher
    string delimiter = "~"; //a character that marks the beginning or end of a unit of data

    string str_file_content;
    int loopPass = 1; // start at loop instance 1 to not add extra delimiters to the front of the message.
    while (loopPass != numberOfItems) {
        str_file_content += delimiter; // this will add the seperating delimiter before the a given item

        switch (loopPass)
        {
            case 1://first item after delimiter
            if (item1.length() > 0) str_file_content += item1;
            break;
            case 2://first item after delimiter
            if (item2.length() > 0) str_file_content += item2;
            break;
            case 3://first item after delimiter
            if (item3.length() > 0) str_file_content += item3;
            break;
            case 4://first item after delimiter
            if (item4.length() > 0) str_file_content += item4;
            break;
            case 5://first item after delimiter
            if (item5.length() > 0) str_file_content += item5;
            break;
            case 6://first item after delimiter
            if (item6.length() > 0) str_file_content += item6;
            break;
            case 7://first item after delimiter
            if (item7.length() > 0) str_file_content += item7;
            break;
        }
        str_file_content += delimiter; // this will add the seperating delimiter after the given item
        loopPass++;
    }
    return str_file_content;
}

void requestActions(int socket, char messageFromClient[]) {
    
    //output the message recieved from the user to the consol.
    printf("V1.1-Here is the message from the User: %s\n", messageFromClient);
    

    // The following was for testing purposes and can be removed later to impliment a better version for decicion making
    /**/
    string userMessage = decipher(messageFromClient); // this runs the function dcipher taking off the delimiter value which is currently "~".  This gives us the intended message
    string returnMessage;
    int n;
    //make a decision based off the message from the user
    if (userMessage == "1"){
        
        printf("The user has selected the number 1\n");//print message to consol
        
        returnMessage = "Thisis the message you sent us \"" + userMessage + "\"";//this will be the message sent back to the client
        returnMessage = cipher(returnMessage); // run the function adding the delimiter
        
        n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
        if (n < 0) error("ERROR writing to socket");
    } else if (userMessage == "2") {
        
        printf("The user has input the number 2\n");//print message to consol
        
        returnMessage = "This is the message you sent us \"" + userMessage + "\"";//this will be the message sent back to the client
        returnMessage = cipher(returnMessage); // run the function adding the delimiter
        
        n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
        if (n < 0) error("ERROR writing to socket");
    } else {
        
        printf("The user has selected something other than 1 and 2\n");//print message to consol
        
        returnMessage = "This is the message you sent us \"" + userMessage + "\"";//this will be the message sent back to the client
        returnMessage = cipher(returnMessage); // run the function adding the delimiter
        
        n = write(socket, returnMessage.c_str(), returnMessage.length()+1);//send message back to the client
        if (n < 0) error("ERROR writing to socket");
    }
    /**/
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
    cout << "Server Started..." << endl << "Press \"ctrl + c\" to stop the running program 1.1" << endl;
    communicate(argc, argv);

    return 0; /* we never get here */
}