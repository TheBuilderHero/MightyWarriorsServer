#include <iostream>
#include <string>

#include "Characters.h"

#pragma once

using namespace std;

class Cipher {
    public:
    string delimiter = "~";
    string typeOfRequest;
    string username, item3, item4, item5, item6, item7; // declare the variables that are being used to store the message from the client
    // the above variables may later be replaced with a more wide veriety of variables however, for testing we are using all strings

    //this function is intended to pull out the users request and the data associated with each request
    string decipher(char messageFromClient[]);

    //this functions purpose it to add the delimiters to given items 
    string cipher(string responseType, string item2= "", string item3= "", string item4= "", string item5= "", string item6= "", string item7= "");

    //This function writes inputs given from a user to file using the sperating delimiter
    void userDataDeliminationWrite(int newOrUpdate, string username, string data2 = "", string data3 = "", string data4 = "", string data5 = "", string data6 = "", string data7 = "");
    
    //currently no function but it will read from the user's data file
    void userDataDeliminationRead(string username);
};