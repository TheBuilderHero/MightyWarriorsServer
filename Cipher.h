#include <iostream>
#include <fstream>
#include <string>

#include "Characters.h"

#pragma once

using namespace std;

class Cipher {
    private:
        const int MAX_NUMBER_OF_QUESTS = 20 + 1; //+1 because we start at 1
        string line;
        string search;
        string delimiter = "~";
        string subDelimiter = "=";
        string typeOfRequest;
<<<<<<< HEAD
        string username;
        string item[22];
        string subItem[22][22];//, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12; // declare the variables that are being used to store the message from the client // in some cases item2 is used.
=======
        string username, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12, item13, item14, item15, item16, item17, item18, item19, item20, item21, item22; // declare the variables that are being used to store the message from the client // in some cases item2 is used.
>>>>>>> 0d5207daccc3386bd1afbc9361a9bf6adc5bd127
        // the above variables may later be replaced with a more wide veriety of variables however, for testing we are using all strings
    public:
    //this function is intended to pull out the users request and the data associated with each request
    string decipher(char messageFromClient[], bool hasSubItems = false); //default does not have sub items
    string subDecipher(string subMessageFromClient, int rootItem);

    //this functions purpose it to add the delimiters to given items 
    string cipher(string responseType, string item2= "", string item3= "", string item4= "", string item5= "", string item6= "", string item7= "", string item8= "", string item9= "", string item10= "", string item11= "", string item12= "", string item13= "", string item14= "", string item15= "", string item16= "", string item17= "", string item18= "", string item19= "", string item20= "", string item21= "", string item22= "");

    //this functions purpose it to add the delimiters to given sub items 
    string subCipher(string item1, string item2= "", string item3= "", string item4= "", string item5= "", string item6= "", string item7= "", string item8= "", string item9= "", string item10= "", string item11= "", string item12= "", string item13= "", string item14= "", string item15= "", string item16= "", string item17= "", string item18= "", string item19= "", string item20= "", string item21= "", string item22= "");

    //This function writes inputs given from a user to file using the sperating delimiter //updateValue: 1 = inital setup race, kit, level, XP 2 = password 3 = user's stats overwrite 4 = level and XP update 5 = user stats update 6 = update weapons 7 = update location 8 = update the player quests progress
    void userDataDeliminationWrite(int updateValue, string username, string data2 = "", string data3 = "", string data4 = "", string data5 = "", string data6 = "", string data7 = "", string data8 = "", string data9 = "", string data10 = "", string data11 = "", string data12 = ""); 
    
    //currently no function but it will read from the user's data file
    void userDataDeliminationRead(int updateValue, string username);

    //Other Data management:
    void copyFile(std::string username, std::string pathOfCopyDestination);
    void copyFileAddingData(std::string username, string pathOfCopyTarget, std::string dataHeader, std::string newData, bool headerIsAtStart = false);
    void deleteFile(std::string fileName);
    void eraseFile(std::string fileName);
    void updateData(string username, string pathOfFileToChangeData, string dataHeaderToUpdate, string newData); //the above functions are used in this function
    
    bool find(std::string username, std::string searchHeader);

    string readData(string username, string pathOfFile, string dataHeader);

    //end of other data management

    //File and folder path return functions:
    std::string getStatPath(std::string username);
    std::string getDatPath(std::string username);
    std::string getActPath(std::string username);
    std::string getWeaponPath(std::string username);
    std::string getTestPath(std::string username);
    std::string getTempPath(std::string username);
    std::string getLocationPath(std::string username);
    std::string getQuestPath(std::string username);

    //getVariable functions:
    std::string getDelimiter() { return delimiter; }
    std::string getTypeOfRequest() { return typeOfRequest; }
    std::string getUsername() { return username; }
    //the purpose of this function is to return data that has been deciphered. //note there is no item1 because that place is being used by response type. //First Item is number 2 because username is 1
    std::string getItem(int itemNumberToReturn, int subItem = 0); //you do not need to enter a subItem if you did not make a request to server that gave you a subItem return.

};