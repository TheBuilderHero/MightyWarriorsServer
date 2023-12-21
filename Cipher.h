#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Characters.h"

#pragma once

using namespace std;


class Cipher {
    private:
        const int MAX_NUMBER_OF_QUESTS = 20 + 1; //+1 because we start at 1
        string line;
        string search;
        //For the number of STATS to be send over communication from client to server:
        //update this when you change the number of stats sent from the client.
        const unsigned short int TRANSMITTED_STAT_COUNT = 17;

        //for min and max values:
        std::string delimiterMinMax = " - ";
        string delimiterLayer1 = "~";
        string delimiterLayer2 = "=";
        string delimiterLayer3 = "|";
        string delimiterLayer4 = "+";
        string typeOfRequest;
        string username;
        vector<string> MESSAGE;
        string item[22];
        string subItem[22][22];//, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12; // declare the variables that are being used to store the message from the client // in some cases item2 is used.
        // the above variables may later be replaced with a more wide veriety of variables however, for testing we are using all strings
    public:
        //the strings that are sent for the following are stored in convertSEND_TYPEToString
        enum SEND_TYPE { VECTOR_SEND, VECTOR_RECEIVE };
        //the strings that are sent for the following are stored in convertDATA_TYPEToString
        enum DATA_TYPE { NONE, DIALOGUE_INFO, STAT_INFO, ENEMY_INFO, LOCATION_INFO, RACE_KIT_WEAPON_INFO, QUEST_PROGRESS, INVENTORY_INFO, ABILITY_TYPES_INFO, LEVEL_XP_INFO };
        //
        enum FILE_DATA_TYPE { QUEST_DATA, STAT_DATA, LOCATION_DATA, RACE_KIT_WEAPON_DATA, QUEST_PROGRESS_DATA, INVENTORY_DATA, ABILITY_TYPES_DATA, LEVEL_XP_DATA};
        //this function is intended to pull out the users request and the data associated with each request
        string decipher(char messageFromClient[], bool hasSubItems = false); //default does not have sub items
        string subDecipher(string subMessageFromClient, int rootItem);

        //this functions purpose it to add the delimiters to given items 
        string cipher(string responseType, string item2= "", string item3= "", string item4= "", string item5= "", string item6= "", string item7= "", string item8= "", string item9= "", string item10= "", string item11= "", string item12= "", string item13= "", string item14= "", string item15= "", string item16= "", string item17= "", string item18= "", string item19= "", string item20= "", string item21= "", string item22= "");

        //this functions purpose it to add the delimiters to given sub items 
        string subCipher(string item1, string item2= "", string item3= "", string item4= "", string item5= "", string item6= "", string item7= "", string item8= "", string item9= "", string item10= "", string item11= "", string item12= "", string item13= "", string item14= "", string item15= "", string item16= "", string item17= "", string item18= "", string item19= "", string item20= "", string item21= "", string item22= "");

        //This function writes inputs given from a user to file using the sperating delimiter //updateValue: 1 = inital setup race, kit, level, XP 2 = password 3 = user's stats overwrite 4 = level and XP update 5 = user stats update 6 = update weapons 7 = update location 8 = update the player quests progress
        void userDataDeliminationWrite(int updateValue, string username, string data2 = "", string data3 = "", string data4 = "", string data5 = "", string data6 = "", string data7 = "", string data8 = "", string data9 = "", string data10 = "", string data11 = "", string data12 = ""); 
        //gonna try to move to a more dynamic setup
        void readFromFile(FILE_DATA_TYPE itemUpdateType, string username, vector<pair<int,string>> &saveVector);
        void writeToFile(FILE_DATA_TYPE itemUpdateType, string username, vector<pair<int,string>> &linesToUpdateWithData); //int line to update was replaced with the pair of strings
        
        //currently no function but it will read from the user's data file
        void userDataDeliminationRead(int updateValue, string username); 
        //gonna try to move to a more dynamic setup
        void dataDeliminationRead(FILE_DATA_TYPE returnItemType, string username, vector<string> &data);

        //Other Data management:
        void copyFile(std::string username, std::string pathOfCopyDestination);
        void copyFileAddingData(std::string username, string pathOfCopyTarget, std::string dataHeader, std::string newData, bool headerIsAtStart = false);
        void deleteFile(std::string fileName);
        void eraseFile(std::string fileName);
        void updateData(string username, string pathOfFileToChangeData, string dataHeaderToUpdate, string newData); //the above functions are used in this function
        
        bool find(std::string username, std::string searchHeader);

        string readData(string username, string pathOfFile, string dataHeader);

        //end of other data management

        //setter:
        void setUsername(std::string username) { this->username = username; };

        //File and folder path return functions:
        std::string getStatPath(std::string username);
        std::string getDatPath(std::string username);
        std::string getActPath(std::string username);
        std::string getWeaponPath(std::string username);
        std::string getTestPath(std::string username);
        std::string getTempPath(std::string username);
        std::string getLocationPath(std::string username);
        std::string getQuestPath(std::string username);
        std::string getInventoryPath(std::string username);

        //getVariable functions:
        std::string getDelimiterMinMax() { return delimiterMinMax; }
        std::string getDelimiterLayer1() { return delimiterLayer1; }
        std::string getDelimiterLayer2() { return delimiterLayer2; }
        std::string getDelimiterLayer3() { return delimiterLayer3; }
        std::string getDelimiterLayer4() { return delimiterLayer4; }
        std::string getTypeOfRequest() { return typeOfRequest; }
        std::string getUsername() { return username; }
        int getMESSAGESize() { return MESSAGE.size(); }
        std::string getMESSAGE(int pos) { return MESSAGE.at(pos); }
        //the purpose of this function is to return data that has been deciphered. //note there is no item1 because that place is being used by response type. //First Item is number 2 because username is 1
        std::string getItem(int itemNumberToReturn, int subItem = 0); //you do not need to enter a subItem if you did not make a request to server that gave you a subItem return.
        //layer 1:
        void vectorDeliminateLayer1Head(const enum SEND_TYPE &input = VECTOR_SEND);
        void vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(const enum DATA_TYPE &input);
        void vectorDeliminateLayer1OpenNewInputOrSwitchDownLayer(std::string input = "");
        void vectorDeliminateLayer1EndInput();
        //layer 2:
        void vectorDeliminateLayer2OpenNewInputOrSwitchDownLayer(std::string input = "");
        void vectorDeliminateLayer2EndInput();
        //layer 3:
        void vectorDeliminateLayer3OpenNewInputOrSwitchDownLayer(std::string input = "");
        void vectorDeliminateLayer3EndInput();
        //layer 4:
        void vectorDeliminateLayer4OpenNewInputOrSwitchDownLayer(std::string input);
        void vectorDeliminateLayer4EndInput();

        //enumeration convertion:
        std::string convertSEND_TYPEToString(const enum SEND_TYPE &input){
            //if these are changed we need to then update them on the client side:
            switch(input){
                case 0: return "7";
                default: return "7"; 
            }
        }
        std::string convertDATA_TYPEToString(const enum DATA_TYPE &input){
            //if these are changed we need to then update them on the client side:
            switch(input){
                case 0: return "none"; 
                case 1: return "dialogue"; 
                case 2: return "stats"; 
                case 3: return "enemyinfo";
                case 4: return "locationinfo";
                case 5: return "racekitweaponinfo";
                case 6: return "questinfo";
                case 7: return "inventoryinfo";
                case 8: return "abilitytypeinfo";
                case 9: return "levelxpinfo";
                default: return "failed"; 
            }
        }
        
    //enumeration convertion:
    enum SEND_TYPE convertToSEND_TYPE(std::string &input){
        //if these are changed we need to then update them on the server side:
        if(input == "7"){
            return VECTOR_RECEIVE;
        }
    }
    enum DATA_TYPE convertToDATA_TYPE(std::string &input){
        //if these are changed we need to then update them on the server side:
        if (input == "dialogue") return DIALOGUE_INFO;
        if (input == "stats") return STAT_INFO;
        if (input == "enemyinfo") return ENEMY_INFO;
        if (input == "locationinfo") return LOCATION_INFO;
        if (input == "racekitweaponinfo") return RACE_KIT_WEAPON_INFO;
        if (input == "questinfo") return QUEST_PROGRESS;
        if (input == "inventoryinfo") return INVENTORY_INFO;
        if (input == "abilitytypeinfo") return ABILITY_TYPES_INFO;
        if (input == "levelxpinfo") return LEVEL_XP_INFO;
        return NONE;
    }
};