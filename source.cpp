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
void error(const char* msg)
{
    perror(msg);
    exit(1);
}

void communicate(int argc, char* argv[])
{
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
    string delimiter = "~~~";
    bzero(buffer, 256);
    n = read(sock, buffer, 255);
    if (n < 0) error("ERROR reading from socket");
    string str_file_content;
    string s = buffer;
    printf("Here is the message from the User: %s\n", buffer);
    size_t saveOpenCheck = s.find(delimiter);
    size_t pos = 0;
    string token;

    //Outputting the value of str_file_content to look a little nicer and remove the delimiter character
    string message = string(" Thanks for conneceting to the Server! Your Message was: \"") + str_file_content + s + string("\"");  //had been outputting buffer instead to troubleshoot and get full picture of what I was getting
        n = write(sock, message.c_str(), sizeof(message) + sizeof(buffer));
        if (n < 0) error("ERROR writing to socket");

    string prg_saved = string(" Progress Saved!");
    n += write(sock, prg_saved.c_str(), sizeof(prg_saved) + sizeof(buffer));
    if (n < 0) error("ERROR writing to socket");
}
int main(int argc, char* argv[]){
    cout << "Server Started..." << endl << "Press \"ctrl + c\" to stop the running program 1.1" << endl;
    communicate(argc, argv);

    return 0; /* we never get here */
}