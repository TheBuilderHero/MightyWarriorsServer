#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <sys/stat.h>

#include "Cipher.h"

using namespace std;

string Cipher::getItem(int itemNumberToReturn){ //the purpose of this function is to return data that has been deciphered.
    switch (itemNumberToReturn)
    {
    case 2:
        return item2;
        break;
    case 3:
        return item3;
        break;
    case 4:
        return item4;
        break;
    case 5:
        return item5;
        break;
    case 6:
        return item6;
        break;
    case 7:
        return item7;
        break;
    case 8:
        return item8;
        break;
    case 9:
        return item9;
        break;
    case 10:
        return item10;
        break;
    case 11:
        return item11;
        break;
    case 12:
        return item12;
        break;

    default:
        return "Default Output Given";
        break;
    }
}

//char messageFromClient[]
//this function is intended to pull out the users request and the data associated with each request
string Cipher::decipher(char messageFromClient[]){ //requestActions takes all the different typeOfRequest
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
            case 8://the eighth item enclosed in delimiters
            if (output.length() > 0) item8 = output; 
            break;
            case 9://the ninth item enclosed in delimiters
            if (output.length() > 0) item9 = output; 
            break;
            case 10://the tenth item enclosed in delimiters
            if (output.length() > 0) item10 = output; 
            break;
            case 11://the tenth item enclosed in delimiters
            if (output.length() > 0) item11 = output; 
            break;
            case 12://the tenth item enclosed in delimiters
            if (output.length() > 0) item12 = output; 
            break;
        }
        loopPass++;
    }
    return str_file_content;
}

//this functions purpose it to add the delimiters to given items 
string Cipher::cipher(string responseType, string item2, string item3, string item4, string item5, string item6, string item7, string item8, string item9, string item10, string item11, string item12){ // the default values have been set to "" in case no input is given
    int numberOfItems = 12; //max number of items that we can cipher
    string delimiter = "~"; //a character that marks the beginning or end of a unit of data

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
        }
        loopPass++;
    }
    str_file_content += delimiter; // this will add the final delimiter after all the data to mark the end
    return str_file_content;
}

void Cipher::userDataDeliminationWrite(int updateValue, string username, string data2, string data3, string data4, string data5, string data6, string data7, string data8, string data9, string data10){
    ofstream userfile;
    ofstream logonfile;
    switch (updateValue){ //updateValue is for the password, whether it is just getting updated or if this is a new user.
        case 1: //sets the player's username, race, kit, level, and xp on account setup.
            mkdir(("./userdata/" + username).c_str(), 0774);

            //inital starting level and XP stats:
            data4 = "1";
            data5 = "0";
            
            //some user data is stored in "[username].dat"
            userfile.open("./userdata/" + username + "/" + username + ".dat");
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

            logonfile.open("./userdata/" + username + "/" + username + ".act"); // this is the file which will store the users accout logon info
            logonfile << delimiter << username;
            logonfile << delimiter << "0000"; // set defualt password for the account
            logonfile << delimiter;
            logonfile.close();
            break;
        case 2: //password update
            logonfile.open("./userdata/" + username + "/" + username + ".act"); // this is the file which will store the users accout logon info
            logonfile << delimiter << username;
            logonfile << delimiter << data2; //this sets the defualt password to the information input in data2 which was given by the user
            logonfile << delimiter;
            logonfile.close();
            break;
        case 3: //Overwrite the user's stats
            userfile.open("./userdata/" + username + "/" + username + ".stat");
            userfile << delimiter << username; // these are all adding data to the file with delimiter seperation.
            if (data2.length() > 0) {userfile << delimiter << data2;} else {userfile << delimiter;} //health stat
            if (data3.length() > 0) {userfile << delimiter << data3;} else {userfile << delimiter;} //armor stat
            if (data4.length() > 0) {userfile << delimiter << data4;} else {userfile << delimiter;} //magic res stat
            if (data5.length() > 0) {userfile << delimiter << data5;} else {userfile << delimiter;} //physical damage stat
            if (data6.length() > 0) {userfile << delimiter << data6;} else {userfile << delimiter;} //magic damage stat
            if (data7.length() > 0) {userfile << delimiter << data7;} else {userfile << delimiter;} //Agility stat
            if (data8.length() > 0) {userfile << delimiter << data8;} else {userfile << delimiter;} //stealth stat
            if (data9.length() > 0) {userfile << delimiter << data9;} else {userfile << delimiter;} //Stamina stat
            if (data10.length() > 0) {userfile << delimiter << data10;} else {userfile << delimiter;} //Mana stat
            userfile << delimiter;
            userfile.close(); // done writting to file and now it is closed
            break;
        case 4: //update the players's level and XP
            //some user data is stored in "[username].dat"
            userfile.open("./userdata/" + username + "/" + username + ".dat");
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
            break;
    }
}

void Cipher::userDataDeliminationRead(int updateValue, string username){
    ifstream userstats;
    ifstream userdata;
    string s;
    string str_file_content;
    string token, output;
    int loopPass = 0;
    size_t pos = 0; // position variable for removing the delimiters to view the message
    switch (updateValue){ //updateValue is for the password, whether it is just getting updated or if this is a new user.
        case 1: //get user additional stats
            userstats.open("./userdata/" + username + "/" + username + ".stat");
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
                    if (output.length() > 0) item2 = output; // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
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
                    case 8://eighth item after delimiter
                    if (output.length() > 0) item8 = output;
                    break;
                    case 9://ninth item after delimiter
                    if (output.length() > 0) item9 = output;
                    break;
                    case 10://tenth item after delimiter
                    if (output.length() > 0) item10 = output;
                    break;
                    case 11://tenth item after delimiter
                    if (output.length() > 0) item11 = output;
                    break;
                }
                loopPass++;
            }
            userstats.close();
            //return str_file_content; //we are not having this return anything right now, however, we may change this later.
            break;
        case 2: //reads the player's race, kit, level, and XP to items 2, 3, 4, and 5
            userdata.open("./userdata/" + username + "/" + username + ".dat");
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
                    if (output.length() > 0) item2 = output; //this will be where the user's race is stored
                    break;
                    case 3://third item after delimiter
                    if (output.length() > 0) item3 = output; //this will be where the user's kit is stored
                    break;
                    case 4:
                    if (output.length() > 0) item4 = output; //this will be where the user's level is stored
                    break;
                    case 5:
                    if (output.length() > 0) item5 = output; //this will be where the user's XP is stored
                    break;
                }
                loopPass++;
            }
            userdata.close();
            break;
    }
}