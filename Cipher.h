#include <iostream>
#include <fstream>
#include <string>

#include "Characters.h"

#pragma once

using namespace std;

class Cipher {
    private:
        string line;
        string search;
        string delimiter = "~";
        string typeOfRequest;
        string username, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12; // declare the variables that are being used to store the message from the client // in some cases item2 is used.
        // the above variables may later be replaced with a more wide veriety of variables however, for testing we are using all strings
    public:
    //this function is intended to pull out the users request and the data associated with each request
    string decipher(char messageFromClient[]);

    //this functions purpose it to add the delimiters to given items 
    string cipher(string responseType, string item2= "", string item3= "", string item4= "", string item5= "", string item6= "", string item7= "", string item8= "", string item9= "", string item10= "", string item11= "", string item12= "");

    //This function writes inputs given from a user to file using the sperating delimiter
    void userDataDeliminationWrite(int updateValue, string username, string data2 = "", string data3 = "", string data4 = "", string data5 = "", string data6 = "", string data7 = "", string data8 = "", string data9 = "", string data10 = "");
    
    //currently no function but it will read from the user's data file
    void userDataDeliminationRead(int updateValue, string username);

    //Other Data management:
    void copyFile(std::string username, std::string pathOfCopyDestination);
    void copyFileAddingData(std::string username, string pathOfCopyTarget, std::string dataHeader, std::string newData, bool headerIsAtStart = false);
    void deleteFile(std::string fileName);
    void eraseFile(std::string fileName);
    void updateData(string username, string pathOfFileToChangeData, string dataHeaderToUpdate, string newData); //the above functions are used in this function
    
    bool find(std::string username, std::string searchHeader);

    void readData(string username, string pathOfFile);

    //end of other data management

    //File and folder path return functions:
    std::string getStatPath(std::string username);
    std::string getDatPath(std::string username);
    std::string getActPath(std::string username);
    std::string getWeaponPath(std::string username);
    std::string getTestPath(std::string username);
    std::string getTempPath(std::string username);

    //getVariable functions:
    std::string getDelimiter() { return delimiter; }
    std::string getTypeOfRequest() { return typeOfRequest; }
    std::string getUsername() { return username; }
    std::string getItem(int itemNumberToReturn); //the purpose of this function is to return data that has been deciphered. //note there is no item1 because that place is being used by response type.

};