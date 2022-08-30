#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <sys/stat.h>

#include "Cipher.h"

using namespace std;

string Cipher::getStatPath(string username){
    string output = "./userdata/" + username + "/" + username + ".stat";
    return output;
}
string Cipher::getDatPath(std::string username){
    string output = "./userdata/" + username + "/" + username + ".dat";
    return output;
}
string Cipher::getActPath(std::string username){
    string output = "./userdata/" + username + "/" + username + ".act";
    return output;
}
string Cipher::getWeaponPath(std::string username){
    string output = "./userdata/" + username + "/" + username + ".weapons";
    return output;
}
string Cipher::getTestPath(std::string username){
    string output = "./userdata/" + username + "/" + username + ".test";
    return output;
}
string Cipher::getTempPath(std::string username){
    string output = "./userdata/" + username + "/" + username + ".temp";
    return output;
}
string Cipher::getLocationPath(std::string username){
    string output = "./userdata/" + username + "/" + username + ".loc";
    return output;
}
string Cipher::getQuestPath(std::string username){
    string output = "./userdata/" + username + "/" + username + ".quest";
    return output;
}

string Cipher::getItem(int itemNumberToReturn, int subItemNumber){ //the purpose of this function is to return data that has been deciphered.
    if (subItemNumber > 0) return subItem[itemNumberToReturn][subItemNumber];
    return item[itemNumberToReturn];
}

//char messageFromClient[]
//this function is intended to pull out the users request and the data associated with each request
string Cipher::decipher(char messageFromClient[], bool hasSubItems){ //requestActions takes all the different typeOfRequest
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
            if (output.length() > 0) typeOfRequest = output; // request numbers give different outputs 1 is username usage, 2 is create user account, 3 is logon
            break;
            case 2://second item after delimiter
            if (output.length() > 0) username = output; // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
            break;
            case 3://third item after delimiter
            if (output.length() > 0) {
                item[3] = output;
                if (hasSubItems) subDecipher(item[3], 3);
                }
            break;
            case 4://forth item after delimiter
            if (output.length() > 0) {
                item[4] = output;
                if (hasSubItems) subDecipher(item[4], 4);
                }
            break;
            case 5://fith item after delimiter
            if (output.length() > 0) {
                item[5] = output;
                if (hasSubItems) subDecipher(item[5], 5);
                }
            break;
            case 6://sixth item after delimiter
            if (output.length() > 0) {
                item[6] = output;
                if (hasSubItems) subDecipher(item[6], 6);
                }
            break;
            case 7://seventh item after delimiter
            if (output.length() > 0) {
                item[7] = output;
                if (hasSubItems) subDecipher(item[7], 7);
                }
            break; 
            case 8://the eighth item enclosed in delimiters
            if (output.length() > 0) {
                item[8] = output;
                if (hasSubItems) subDecipher(item[8], 8);
                } 
            break;
            case 9://the ninth item enclosed in delimiters
            if (output.length() > 0) {
                item[9] = output;
                if (hasSubItems) subDecipher(item[9], 9);
                } 
            break;
            case 10://the tenth item enclosed in delimiters
            if (output.length() > 0) {
                item[10] = output;
                if (hasSubItems) subDecipher(item[10], 10);
                } 
            break;
            case 11://the tenth item enclosed in delimiters
            if (output.length() > 0) {
                item[11] = output;
                if (hasSubItems) subDecipher(item[11], 11);
                } 
            break;
            case 12://the tenth item enclosed in delimiters
            if (output.length() > 0) {
                item[12] = output;
                if (hasSubItems) subDecipher(item[12], 12);
                } 
            break;
            case 13:
            if (output.length() > 0) {
                item[13] = output;
                if (hasSubItems) subDecipher(item[13], 13);
                } 
            break;
            case 14:
            if (output.length() > 0) {
                item[14] = output;
                if (hasSubItems) subDecipher(item[14], 14);
                } 
            break;
            case 15:
            if (output.length() > 0) {
                item[15] = output;
                if (hasSubItems) subDecipher(item[15], 15);
                } 
            break;
            case 16:
            if (output.length() > 0) {
                item[16] = output;
                if (hasSubItems) subDecipher(item[16], 16);
                } 
            break;
            case 17:
            if (output.length() > 0) {
                item[17] = output;
                if (hasSubItems) subDecipher(item[17], 17);
                } 
            break;
            case 18:
            if (output.length() > 0) {
                item[18] = output;
                if (hasSubItems) subDecipher(item[18], 18);
                } 
            break;
            case 19:
            if (output.length() > 0) {
                item[19] = output;
                if (hasSubItems) subDecipher(item[19], 19);
                } 
            break;
            case 20:
            if (output.length() > 0) {
                item[20] = output;
                if (hasSubItems) subDecipher(item[20], 20);
                } 
            break;
            case 21:
            if (output.length() > 0) {
                item[21] = output;
                if (hasSubItems) subDecipher(item[21], 21);
                } 
            break;
            case 22:
            if (output.length() > 0) {
                item[22] = output;
                if (hasSubItems) subDecipher(item[22], 22);
                } 
            break;
        }
        loopPass++;
    }
    return str_file_content;
}
string Cipher::subDecipher(string subMessageFromClient, int rootItem){ //requestActions takes all the different typeOfRequest
    string s = subMessageFromClient;// change the message into a string
    string str_file_content;
    string token, output;
    int loopPass = 0;
    size_t pos = 0; // position variable for removing the delimiters to view the message
    while ((pos = s.find(subDelimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        output = token;
        str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
        s.erase(0, pos + subDelimiter.length());
        
        switch (loopPass){
            case 1: //first item after delimiter
            if (output.length() > 0) subItem[rootItem][1] = output;
            break;
            case 2://second item after delimiter
            if (output.length() > 0) subItem[rootItem][2] = output;
            break;
            case 3://third item after delimiter
            if (output.length() > 0) subItem[rootItem][3] = output;
            break;
            case 4://forth item after delimiter
            if (output.length() > 0) subItem[rootItem][4] = output;
            break;
            case 5://fith item after delimiter
            if (output.length() > 0) subItem[rootItem][5] = output;
            break;
            case 6://sixth item after delimiter
            if (output.length() > 0) subItem[rootItem][6] = output;
            break;
            case 7://seventh item after delimiter
            if (output.length() > 0) subItem[rootItem][7] = output;
            break; 
            case 8://the eighth item enclosed in delimiters
            if (output.length() > 0) subItem[rootItem][8] = output; 
            break;
            case 9://the ninth item enclosed in delimiters
            if (output.length() > 0) subItem[rootItem][9] = output; 
            break;
            case 10://the tenth item enclosed in delimiters
            if (output.length() > 0) subItem[rootItem][10] = output; 
            break;
            case 11://the tenth item enclosed in delimiters
            if (output.length() > 0) subItem[rootItem][11] = output; 
            break;
            case 12://the tenth item enclosed in delimiters
            if (output.length() > 0) subItem[rootItem][12] = output; 
            break;
            case 13:
            if (output.length() > 0) subItem[rootItem][13] = output; 
            break;
            case 14:
            if (output.length() > 0) subItem[rootItem][14] = output; 
            break;
            case 15:
            if (output.length() > 0) subItem[rootItem][15] = output; 
            break;
            case 16:
            if (output.length() > 0) subItem[rootItem][16] = output; 
            break;
            case 17:
            if (output.length() > 0) subItem[rootItem][17] = output; 
            break;
            case 18:
            if (output.length() > 0) subItem[rootItem][18] = output; 
            break;
            case 19:
            if (output.length() > 0) subItem[rootItem][19] = output; 
            break;
            case 20:
            if (output.length() > 0) subItem[rootItem][20] = output; 
            break;
            case 21:
            if (output.length() > 0) subItem[rootItem][21] = output; 
            break;
            case 22:
            if (output.length() > 0) subItem[rootItem][22] = output; 
            break;
        }
        loopPass++;
    }
    return str_file_content;
}

//this functions purpose it to add the delimiters to given items 
string Cipher::cipher(string responseType, string item2, string item3, string item4, string item5, string item6, string item7, string item8, string item9, string item10, string item11, string item12, string item13, string item14, string item15, string item16, string item17, string item18, string item19, string item20, string item21, string item22){ // the default values have been set to "" in case no input is given
    int numberOfItems = 22; //max number of items that we can cipher
    //"~" //a character that marks the beginning or end of a unit of data

    string str_file_content;
    int loopPass = 1; // start at loop instance 1 to not add extra delimiters to the front of the message.
    while (loopPass <= numberOfItems) {
        str_file_content += delimiter; // this will add the seperating delimiter before the a given item
        switch (loopPass)
        {
            case 1://first item after delimiter
            if (responseType.length() > 0) str_file_content += responseType;
            break;
            case 2://second item after delimiter
            if (item2.length() > 0) str_file_content += item2;
            break;
            case 3://third item after delimiter
            if (item3.length() > 0) str_file_content += item3;
            break;
            case 4://forth item after delimiter
            if (item4.length() > 0) str_file_content += item4;
            break;
            case 5://fith item after delimiter
            if (item5.length() > 0) str_file_content += item5;
            break;
            case 6://sixth item after delimiter
            if (item6.length() > 0) str_file_content += item6;
            break;
            case 7://seventh item after delimiter
            if (item7.length() > 0) str_file_content += item7;
            break;
            case 8://eighth item after delimiter
            if (item8.length() > 0) str_file_content += item8;
            break;
            case 9://ninth item after delimiter
            if (item9.length() > 0) str_file_content += item9;
            break;
            case 10://tenth item after delimiter
            if (item10.length() > 0) str_file_content += item10;
            break;
            case 11://eleventh item after delimiter
            if (item11.length() > 0) str_file_content += item11;
            break;
            case 12://twelth item after delimiter
            if (item12.length() > 0) str_file_content += item12;
            break;
            case 13:
            if (item13.length() > 0) str_file_content += item13;
            break;
            case 14:
            if (item14.length() > 0) str_file_content += item14;
            break;
            case 15:
            if (item15.length() > 0) str_file_content += item15;
            break;
            case 16:
            if (item16.length() > 0) str_file_content += item16;
            break;
            case 17:
            if (item17.length() > 0) str_file_content += item17;
            break;
            case 18:
            if (item18.length() > 0) str_file_content += item18;
            break;
            case 19:
            if (item19.length() > 0) str_file_content += item19;
            break;
            case 20:
            if (item20.length() > 0) str_file_content += item20;
            break;
            case 21:
            if (item21.length() > 0) str_file_content += item21;
            break;
            case 22:
            if (item22.length() > 0) str_file_content += item22;
            break;
        }
        loopPass++;
    }
    str_file_content += delimiter; // this will add the final delimiter after all the data to mark the end
    return str_file_content;
}
//this functions purpose it to add the delimiters to given sub items 
string Cipher::subCipher(string item1, string item2, string item3, string item4, string item5, string item6, string item7, string item8, string item9, string item10, string item11, string item12, string item13, string item14, string item15, string item16, string item17, string item18, string item19, string item20, string item21, string item22){ // the default values have been set to "" in case no input is given
    int numberOfItems = 22; //max number of items that we can cipher
    string subDelimiter = "="; //a character that marks the beginning or end of a unit of data

    string str_file_content;
    int loopPass = 1; // start at loop instance 1 to not add extra subDelimiters to the front of the message.
    while (loopPass <= numberOfItems) {
        str_file_content += subDelimiter; // this will add the seperating subDelimiter before the a given item
        switch (loopPass)
        {
            case 1://first item after subDelimiter
            if (item1.length() > 0) str_file_content += item1;
            break;
            case 2://second item after subDelimiter
            if (item2.length() > 0) str_file_content += item2;
            break;
            case 3://third item after subDelimiter
            if (item3.length() > 0) str_file_content += item3;
            break;
            case 4://forth item after subDelimiter
            if (item4.length() > 0) str_file_content += item4;
            break;
            case 5://fith item after subDelimiter
            if (item5.length() > 0) str_file_content += item5;
            break;
            case 6://sixth item after subDelimiter
            if (item6.length() > 0) str_file_content += item6;
            break;
            case 7://seventh item after subDelimiter
            if (item7.length() > 0) str_file_content += item7;
            break;
            case 8://eighth item after subDelimiter
            if (item8.length() > 0) str_file_content += item8;
            break;
            case 9://ninth item after subDelimiter
            if (item9.length() > 0) str_file_content += item9;
            break;
            case 10://tenth item after subDelimiter
            if (item10.length() > 0) str_file_content += item10;
            break;
            case 11://eleventh item after subDelimiter
            if (item11.length() > 0) str_file_content += item11;
            break;
            case 12://twelth item after subDelimiter
            if (item12.length() > 0) str_file_content += item12;
            break;
            case 13:
            if (item13.length() > 0) str_file_content += item13;
            break;
            case 14:
            if (item14.length() > 0) str_file_content += item14;
            break;
            case 15:
            if (item15.length() > 0) str_file_content += item15;
            break;
            case 16:
            if (item16.length() > 0) str_file_content += item16;
            break;
            case 17:
            if (item17.length() > 0) str_file_content += item17;
            break;
            case 18:
            if (item18.length() > 0) str_file_content += item18;
            break;
            case 19:
            if (item19.length() > 0) str_file_content += item19;
            break;
            case 20:
            if (item20.length() > 0) str_file_content += item20;
            break;
            case 21:
            if (item21.length() > 0) str_file_content += item21;
            break;
            case 22:
            if (item22.length() > 0) str_file_content += item22;
            break;
        }
        loopPass++;
    }
    str_file_content += subDelimiter; // this will add the final subDelimiter after all the data to mark the end
    return str_file_content;
}

void Cipher::userDataDeliminationWrite(int updateValue, string username, string data2, string data3, string data4, string data5, string data6, string data7, string data8, string data9, string data10, string data11, string data12){ // updateValue: 1 = inital setup race, kit, level, XP 2 = password 3 = user's stats overwrite 4 = level and XP update 5 = user stats update 6 = update weapons 7 = update location 8 = update the player quests progress
    ofstream userfile;
    ofstream logonfile;
    ofstream weaponStats;
    switch (updateValue){ //updateValue is for the password, whether it is just getting updated or if this is a new user.
        case 1:{ //sets the player's username, race, kit, level, and xp on account setup.
            mkdir(("./userdata/" + username).c_str(), 0774);

            //inital starting level and XP stats:
            data4 = "1";
            data5 = "0";
            
            //some user data is stored in "[username].dat"
            userfile.open(getDatPath(username));
            userfile << delimiter << username; // these are all adding data to the file with delimiter seperation.
            if (data2.length() > 0) {userfile << delimiter << data2;} else {userfile << delimiter;} //race
            if (data3.length() > 0) {userfile << delimiter << data3;} else {userfile << delimiter;} //kit
            if (data4.length() > 0) {userfile << delimiter << data4;} else {userfile << delimiter;} //level
            if (data5.length() > 0) {userfile << delimiter << data5;} else {userfile << delimiter;} //xp
            if (data6.length() > 0) {userfile << delimiter << data6;} else {userfile << delimiter;}
            if (data7.length() > 0) {userfile << delimiter << data7;} else {userfile << delimiter;}
            if (data8.length() > 0) {userfile << delimiter << data8;} else {userfile << delimiter;}
            if (data9.length() > 0) {userfile << delimiter << data9;} else {userfile << delimiter;}
            userfile << delimiter;
            userfile.close(); // done writting to file and now it is closed

            logonfile.open(getActPath(username)); // this is the file which will store the users accout logon info
            logonfile << delimiter << username;
            logonfile << delimiter << "0000"; // set defualt password for the account
            logonfile << delimiter;
            logonfile.close();
            break;}
        case 2:{ //password update
            logonfile.open(getActPath(username)); // this is the file which will store the users accout logon info
            logonfile << delimiter << username;
            logonfile << delimiter << data2; //this sets the defualt password to the information input in data2 which was given by the user
            logonfile << delimiter;
            logonfile.close();
            break;}
        case 3:{ //Overwrite the user's stats
            userfile.open(getStatPath(username));
            userfile << delimiter << username; // these are all adding data to the file with delimiter seperation.
            if (data2.length() > 0) {userfile << delimiter << data2;} else {userfile << delimiter;} //health stat
            if (data3.length() > 0) {userfile << delimiter << data3;} else {userfile << delimiter;} //armor stat
            if (data4.length() > 0) {userfile << delimiter << data4;} else {userfile << delimiter;} //magic res stat
            if (data5.length() > 0) {userfile << delimiter << data5;} else {userfile << delimiter;} //physical damage stat
            if (data6.length() > 0) {userfile << delimiter << data6;} else {userfile << delimiter;} //magic damage stat
            if (data7.length() > 0) {userfile << delimiter << data7;} else {userfile << delimiter;} //Agility stat
            if (data8.length() > 0) {userfile << delimiter << data8;} else {userfile << delimiter;} //stealth stat
            if (data9.length() > 0) {userfile << delimiter << data9;} else {userfile << delimiter;} //Stamina stat
            if (data10.length() > 0) {userfile << delimiter << data10;} else {userfile << delimiter;} //NaturalEnergy stat
            if (data11.length() > 0) {userfile << delimiter << data11;} else {userfile << delimiter;} //Mind stat
            if (data12.length() > 0) {userfile << delimiter << data12;} else {userfile << delimiter;} //psychic damage stat
            userfile << delimiter;
            userfile.close(); // done writting to file and now it is closed
            break;}
        case 4:{ //update the players's level and XP
            //some user data is stored in "[username].dat"
            userfile.open(getDatPath(username));
            userfile << delimiter << username; // these are all adding data to the file with delimiter seperation.
            if (data2.length() > 0) {userfile << delimiter << data2;} else {userfile << delimiter;} //race
            if (data3.length() > 0) {userfile << delimiter << data3;} else {userfile << delimiter;} //kit
            if (data4.length() > 0) {userfile << delimiter << data4;} else {userfile << delimiter;} //level
            if (data5.length() > 0) {userfile << delimiter << data5;} else {userfile << delimiter;} //XP
            if (data6.length() > 0) {userfile << delimiter << data6;} else {userfile << delimiter;}
            if (data7.length() > 0) {userfile << delimiter << data7;} else {userfile << delimiter;}
            if (data8.length() > 0) {userfile << delimiter << data8;} else {userfile << delimiter;}
            if (data9.length() > 0) {userfile << delimiter << data9;} else {userfile << delimiter;}
            userfile << delimiter;
            userfile.close(); // done writting to file and now it is closed
            break;}
        case 5:{ //update user stats
            //pull current stats from file:
            userDataDeliminationRead(1, username);
            int tempHealth = stoi(getItem(2));//health stat
            int tempArmor = stoi(getItem(3));//armor stat
            int tempMagicResistence = stoi(getItem(4));//magic res stat
            int tempPhysicalDamage = stoi(getItem(5));//physical damage stat
            int tempMagicDamage = stoi(getItem(6));//magic damage stat
            int tempAgility = stoi(getItem(7));//Agility stat
            int tempStealth = stoi(getItem(8));//stealth stat
            int tempStamina = stoi(getItem(9));//Stamina stat
            int tempMana = stoi(getItem(10));//NaturalEnergy stat
            int tempMind = stoi(getItem(11));//Mind stat
            int tempPsychicDamage = stoi(getItem(12));//psychic damage stat

            //add new stats to current stats:
            data2 = to_string(tempHealth + stoi(data2));
            data3 = to_string(tempArmor + stoi(data3));
            data4 = to_string(tempMagicResistence + stoi(data4));
            data5 = to_string(tempPhysicalDamage + stoi(data5));
            data6 = to_string(tempMagicDamage + stoi(data6));
            data7 = to_string(tempAgility + stoi(data7));
            data8 = to_string(tempStealth + stoi(data8));
            data9 = to_string(tempStamina + stoi(data9));
            data10 = to_string(tempMana + stoi(data10));
            data11 = to_string(tempMind + stoi(data11));
            data12 = to_string(tempPsychicDamage + stoi(data12));

            //write new stats to file:
            userfile.open(getStatPath(username));
            userfile << delimiter << username; // these are all adding data to the file with delimiter seperation.
            if (data2.length() > 0) {userfile << delimiter << data2;} else {userfile << delimiter;} //health stat
            if (data3.length() > 0) {userfile << delimiter << data3;} else {userfile << delimiter;} //armor stat
            if (data4.length() > 0) {userfile << delimiter << data4;} else {userfile << delimiter;} //magic res stat
            if (data5.length() > 0) {userfile << delimiter << data5;} else {userfile << delimiter;} //physical damage stat
            if (data6.length() > 0) {userfile << delimiter << data6;} else {userfile << delimiter;} //magic damage stat
            if (data7.length() > 0) {userfile << delimiter << data7;} else {userfile << delimiter;} //Agility stat
            if (data8.length() > 0) {userfile << delimiter << data8;} else {userfile << delimiter;} //stealth stat
            if (data9.length() > 0) {userfile << delimiter << data9;} else {userfile << delimiter;} //Stamina stat
            if (data10.length() > 0) {userfile << delimiter << data10;} else {userfile << delimiter;} //NaturalEnergy stat
            if (data11.length() > 0) {userfile << delimiter << data11;} else {userfile << delimiter;} //Mind stat
            if (data12.length() > 0) {userfile << delimiter << data12;} else {userfile << delimiter;} //psychic damage stat
            userfile << delimiter;
            userfile.close(); // done writting to file and now it is closed
            break;}
        case 6:{//update user Weapons
            //copied from case 5
            //pull current stats from file if it exists:
            ifstream weaponFolderTest;
            weaponFolderTest.open(getWeaponPath(username)); //for testing purposes
            if(weaponFolderTest){ //if the file exists
                weaponFolderTest.close();
                userDataDeliminationRead(3, username);
                int tempID = stoi(getItem(2));//weapon ID
                int tempIron = stoi(getItem(3));//iron
                int tempWood = stoi(getItem(4));//wood
                int tempGems = stoi(getItem(5));//gems
                int tempFeet = stoi(getItem(6));//feet
                int tempFruit = stoi(getItem(7));//fruit
                int tempBrains = stoi(getItem(8));//brains

                //add new amounts to current stats except ID:
                data2 = to_string(tempID);
                data3 = to_string(tempIron + stoi(data3));
                data4 = to_string(tempWood + stoi(data4));
                data5 = to_string(tempGems + stoi(data5));
                data6 = to_string(tempFeet + stoi(data6));
                data7 = to_string(tempFruit + stoi(data7));
                data8 = to_string(tempBrains + stoi(data8));
            }

            //write new stats to file:
            weaponStats.open(getWeaponPath(username));
            weaponStats << delimiter << username; // these are all adding data to the file with delimiter seperation.
            if (data2.length() > 0) {weaponStats << delimiter << data2;} else {weaponStats << delimiter;} //Weapon ID
            if (data3.length() > 0) {weaponStats << delimiter << data3;} else {weaponStats << delimiter;} //iron
            if (data4.length() > 0) {weaponStats << delimiter << data4;} else {weaponStats << delimiter;} //wood
            if (data5.length() > 0) {weaponStats << delimiter << data5;} else {weaponStats << delimiter;} //gems
            if (data6.length() > 0) {weaponStats << delimiter << data6;} else {weaponStats << delimiter;} //feet
            if (data7.length() > 0) {weaponStats << delimiter << data7;} else {weaponStats << delimiter;} //fruits
            if (data8.length() > 0) {weaponStats << delimiter << data8;} else {weaponStats << delimiter;} //brains
            weaponStats << delimiter;
            weaponStats.close(); // done writting to file and now it is closed
            break;
            }
        case 7:{ //update the players location in file
            //write new location to file:
            ofstream locationFile;
            locationFile.open(getLocationPath(username));
            locationFile << delimiter << username; // these are all adding data to the file with delimiter seperation.
            if (data2.length() > 0) {locationFile << delimiter << data2;} else {locationFile << delimiter;} //Players current location
            locationFile << delimiter;
            locationFile.close(); // done writting to file and now it is closed
            break;
        }
        case 8:{ //update the players quest info in file
            //pull current quest info from file if it exists:
            string quest[MAX_NUMBER_OF_QUESTS]; //we start at 1
            ifstream questFileTest;
            questFileTest.open(getQuestPath(username)); //for testing purposes
            if(questFileTest){ //if the file exists then we need to load the info into temp variables to be written back into the file
                questFileTest.close();
                userDataDeliminationRead(5, username);
                if(getItem(2).length() > 0) quest[1] = getItem(2);//quest 1
                if(getItem(3).length() > 0) quest[2] = getItem(3);//quest 2
                if(getItem(4).length() > 0) quest[3] = getItem(4);//quest 3
                if(getItem(5).length() > 0) quest[4] = getItem(5);//quest 4
                if(getItem(6).length() > 0) quest[5] = getItem(6);//quest 5
                if(getItem(7).length() > 0) quest[6] = getItem(7);//quest 6
                if(getItem(8).length() > 0) quest[7] = getItem(8);//quest 7
                if(getItem(9).length() > 0) quest[8] = getItem(9);//quest 8
                if(getItem(10).length() > 0) quest[9] = getItem(10);//quest 9
            }

            //write new stats to file:
            ofstream questFile;
            string line;
            int lineNumber = 0;
            questFile.open(getQuestPath(username));
            while(lineNumber != MAX_NUMBER_OF_QUESTS){ //write all the quests back into the file
                if (lineNumber == stoi(data2)){ //update the line with info about the quest
                    questFile << data3 << endl; // delimiter << data3 << delimiter << endl; //removed this delimiter addition
                } else if (quest[lineNumber].length() > 0) {
                    questFile << quest[lineNumber] << endl; //write back the data
                } else if(lineNumber == 0) {
                    questFile <<delimiter<< username <<delimiter<< endl; //kept delimiter addition for username only (probably add current mission to the same line)
                } else {
                    questFile << endl;
                }
                lineNumber++;
            }
            questFile.close(); // done writting to file and now it is closed
            break;
        }
    }
}

void Cipher::userDataDeliminationRead(int updateValue, string username){
    ifstream userstats;
    ifstream userdata;
    ifstream weaponStats;
    string s;
    string str_file_content;
    string token, output;
    int loopPass = 0;
    size_t pos = 0; // position variable for removing the delimiters to view the message
    switch (updateValue){ //updateValue is for the password, whether it is just getting updated or if this is a new user.
        case 1:{ //get user additional stats
            userstats.open(getStatPath(username));
            userstats >> s;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                output = token;
                str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
                s.erase(0, pos + delimiter.length());
                
                switch (loopPass){
                    case 1: //first item after delimiter
                    if (output.length() > 0) username = output; // request numbers give different outputs 1 is username usage, 2 is create user account, 3 is logon
                    break;
                    case 2://second item after delimiter
                    if (output.length() > 0) item[2] = output; // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
                    break;
                    case 3://third item after delimiter
                    if (output.length() > 0) item[3] = output;
                    break;
                    case 4://forth item after delimiter
                    if (output.length() > 0) item[4] = output;
                    break;
                    case 5://fith item after delimiter
                    if (output.length() > 0) item[5] = output;
                    break;
                    case 6://sixth item after delimiter
                    if (output.length() > 0) item[6] = output;
                    break;
                    case 7://seventh item after delimiter
                    if (output.length() > 0) item[7] = output;
                    break;
                    case 8://eighth item after delimiter
                    if (output.length() > 0) item[8] = output;
                    break;
                    case 9://ninth item after delimiter
                    if (output.length() > 0) item[9] = output;
                    break;
                    case 10://tenth item after delimiter
                    if (output.length() > 0) item[10] = output;
                    break;
                    case 11://tenth item after delimiter
                    if (output.length() > 0) item[11] = output;
                    break;
                    case 12://tenth item after delimiter
                    if (output.length() > 0) item[12] = output;
                    break;
                    case 13://tenth item after delimiter
                    if (output.length() > 0) item[13] = output;
                    break;
                    case 14://tenth item after delimiter
                    if (output.length() > 0) item[14] = output;
                    break;
                    case 15://tenth item after delimiter
                    if (output.length() > 0) item[15] = output;
                    break;
                    case 16://tenth item after delimiter
                    if (output.length() > 0) item[16] = output;
                    break;
                    case 17://tenth item after delimiter
                    if (output.length() > 0) item[17] = output;
                    break;
                    case 18://tenth item after delimiter
                    if (output.length() > 0) item[18] = output;
                    break;
                    case 19://tenth item after delimiter
                    if (output.length() > 0) item[19] = output;
                    break;
                    case 20://tenth item after delimiter
                    if (output.length() > 0) item[20] = output;
                    break;
                    case 21://tenth item after delimiter
                    if (output.length() > 0) item[21] = output;
                    break;
                    case 22://tenth item after delimiter
                    if (output.length() > 0) item[22] = output;
                    break;
                }
                loopPass++;
            }
            userstats.close();
            //return str_file_content; //we are not having this return anything right now, however, we may change this later.
            break;
            }
        case 2:{ //reads the player's race, kit, level, and XP to items 2, 3, 4, and 5
            userdata.open(getDatPath(username));
            userdata >> s;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                output = token;
                str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
                s.erase(0, pos + delimiter.length());
                
                switch (loopPass){
                    case 1: //first item after delimiter
                    if (output.length() > 0) username = output;
                    break;
                    case 2://second item after delimiter
                    if (output.length() > 0) item[2] = output; //this will be where the user's race is stored
                    break;
                    case 3://third item after delimiter
                    if (output.length() > 0) item[3] = output; //this will be where the user's kit is stored
                    break;
                    case 4:
                    if (output.length() > 0) item[4] = output; //this will be where the user's level is stored
                    break;
                    case 5:
                    if (output.length() > 0) item[5] = output; //this will be where the user's XP is stored
                    break;
                }
                loopPass++;
            }
            userdata.close();
            break;
            }
        case 3:{//get the weapon stat amounts
            weaponStats.open(getWeaponPath(username));
            weaponStats >> s;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                output = token;
                str_file_content += std::string(token);
                s.erase(0, pos + delimiter.length());
                
                switch (loopPass){
                    case 1: //first item after delimiter
                    if (output.length() > 0) username = output;
                    break;
                    case 2://second item after delimiter      //weaponID
                    if (output.length() > 0) item[2] = output; // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
                    break;
                    case 3://third item after delimiter       //iron
                    if (output.length() > 0) item[3] = output;
                    break;
                    case 4://forth item after delimiter       //wood
                    if (output.length() > 0) item[4] = output;
                    break;
                    case 5://fith item after delimiter        //gems
                    if (output.length() > 0) item[5] = output;
                    break;
                    case 6://sixth item after delimiter       //feet
                    if (output.length() > 0) item[6] = output;
                    break;
                    case 7://seventh item after delimiter     //fruit
                    if (output.length() > 0) item[7] = output;
                    break;
                    case 8://seventh item after delimiter     //brains
                    if (output.length() > 0) item[8] = output;
                    break;
                }
                loopPass++;
            }
            weaponStats.close();
            break;
            }
        case 4:{//get the location saved to file
            ifstream locationFile;
            locationFile.open(getLocationPath(username));
            locationFile >> s;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                output = token;
                str_file_content += std::string(token);
                s.erase(0, pos + delimiter.length());
                
                switch (loopPass){
                    case 1: //first item after delimiter
                    if (output.length() > 0) username = output;
                    break;
                    case 2://second item after delimiter      //Location
                    if (output.length() > 0) item[2] = output;
                    break;
                }
                loopPass++;
            }
            locationFile.close();
            break;
            }
        case 5:{ //quest info
            ifstream questFile;
            string currentLine;
            questFile.open(getQuestPath(username));
            while(getline(questFile, currentLine)){
                switch (loopPass){
                    case 0: //zero item line
                    if (currentLine.length() > 0) username = currentLine;
                    break;
                    case 1: //first item line      //quest 1
                    if (currentLine.length() > 0) item[2] = currentLine;
                    break;
                    case 2://second item line      //quest 2
                    if (currentLine.length() > 0) item[3] = currentLine;
                    break;
                    case 3://third item line       //quest 3
                    if (currentLine.length() > 0) item[4] = currentLine;
                    break;
                    case 4://forth item line       //quest 4
                    if (currentLine.length() > 0) item[5] = currentLine;
                    break;
                    case 5://fith item line        //quest 5
                    if (currentLine.length() > 0) item[6] = currentLine;
                    break;
                    case 6://sixth item line       //quest 6
                    if (currentLine.length() > 0) item[7] = currentLine;
                    break;
                    case 7://seventh item line     //quest 7
                    if (currentLine.length() > 0) item[8] = currentLine;
                    break;
                    case 8://eighth item line     //quest 8
                    if (currentLine.length() > 0) item[9] = currentLine;
                    break;
                    case 9://ninth item line     //quest 9
                    if (currentLine.length() > 0) item[10] = currentLine;
                    break;
                }
                loopPass++;
            }
            questFile.close();
            break;
        }
    }
}

//Other data input output:
void Cipher::copyFile(string username, string pathOfCopyDestination){ //simply copies the temp file back to the destination file
    ofstream in;
    ifstream temp;
    temp.open(getTempPath(username));
    in.open(pathOfCopyDestination, ios::app); //append mode
    if(temp.is_open()){
        //write all the same data to the temp file up until we reach the end
        while(getline(temp,line)){
            in << line << endl;
        }
    }
    in.close();
    temp.close();

}
void Cipher::copyFileAddingData(string username, string pathOfCopyTarget, string dataHeader, string newData, bool headerIsAtStart){ // this recreates a temp file with the added data which we can then use to write back to the original (note, headerIsAtStart is ment to make it so that it only searches for headers at the start of a line)
    ifstream in;
    ofstream temp;
    temp.open(getTempPath(username), ios::app);
    in.open(pathOfCopyTarget);
    if(in.is_open()){
        //write all the same data to the temp file up until the dataHeader we are searching
        while(getline(in,line)){
            int found = line.find(dataHeader);
            if (headerIsAtStart){
                if (found != std::string::npos && found == 0){ //if dataheader is found to be within the line
                    //add the new data to the file in place of the old:
                    temp << dataHeader << delimiter << newData << endl;
                } else{
                    //write same data for all headers which do not match dataHeader
                    temp << line << endl;
                }
            } else {
                if (found != std::string::npos){ //if dataheader is found to be within the line
                    //add the new data to the file in place of the old:
                    temp << dataHeader << delimiter << newData << endl;
                } else{
                    //write same data for all headers which do not match dataHeader
                    temp << line << endl;
                }
            }
        }
    }
    in.close();
    temp.close();
}
void Cipher::updateData(string username, string pathOfFileToChangeData, string dataHeaderToUpdate, string newData){ //given a file path, this function will update the data at the header listed
    //verify we are working with a fresh temp file by erasing it:
    deleteFile(getTempPath(username));

    //update the data:
    copyFileAddingData(username, pathOfFileToChangeData, dataHeaderToUpdate, newData, true);
    eraseFile(pathOfFileToChangeData); //delete the old file and replace it with the new file
    copyFile(username, pathOfFileToChangeData);

    deleteFile(getTempPath(username)); //erase the temp file once the update is complete
}

bool Cipher::find(string username, string searchHeader){ //this was a test for finding string within a file
    ifstream in;
    ofstream out, temp;
    string header;
    search = searchHeader;
    in.open(getTestPath(username));
    temp.open(getTempPath(username));

    while(in>>header){
        if(search.compare(header) == 0){ //finds the item which it was searching for
            in.close();
            temp.close();
            return true;
        }
    }
    in.close();
    temp.close();
    return false;
}

void Cipher::eraseFile(string fullFilePath){ //erase contents of a file without deleting it.
    //this will erase the data from the temp file before deleting it to garentee that commands that take place right after are not using the bad data:
    ofstream temp;
    temp.open(fullFilePath);
    if(temp.is_open()){
        temp << "";
    }
    temp.close();
}
void Cipher::deleteFile(string fullFilePath){ //this deletes a input file (Note, it is not a good way to delete a file since it takes time but it kinda works)
    //this will erase the data from the temp file before deleting it to garentee that commands that take place right after are not using the bad data:
    ofstream temp;
    temp.open(fullFilePath);
    if(temp.is_open()){
        temp << "";
    }
    temp.close();
    // assigning value to string s
    string s("rm -f " + fullFilePath);
    // declaring character array : p
    char charFilename[s.length()];
    int i;
    for (i = 0; i < sizeof(charFilename); i++) {
        charFilename[i] = s[i];
        cout << charFilename[i];
    }
    system(charFilename);
}

string Cipher::readData(string username, string pathOfFile, string dataHeader){ //return the read data's informaiton
    string data;
    ifstream in;
    ofstream temp;
    temp.open(getTempPath(username), ios::app);
    in.open(pathOfFile);
    if(in.is_open()){
        //write all the same data to the temp file up until the dataHeader we are searching
        while(getline(in,line)){
            int found = line.find(dataHeader);
            if (found == 0){ //if dataheader is found to be at the beginning of the line
                //return that data:
                return line;
            }
        }
    }
    return "failed";
}