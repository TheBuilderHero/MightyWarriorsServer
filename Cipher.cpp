#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <sys/stat.h>

#include "Cipher.h"

using namespace std;

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
        }
        loopPass++;
    }
    return str_file_content;
}

//int responseType = 0, string item2= "", string item3= "", string item4= "", string item5= "", string item6= "", string item7= ""
//this functions purpose it to add the delimiters to given items 
string Cipher::cipher(string responseType, string item2, string item3, string item4, string item5, string item6, string item7){ // the default values have been set to "" in case no input is given
    int numberOfItems = 7; //max number of items that we can cipher
    string delimiter = "~"; //a character that marks the beginning or end of a unit of data

    string str_file_content;
    int loopPass = 1; // start at loop instance 1 to not add extra delimiters to the front of the message.
    while (loopPass != numberOfItems) {
        str_file_content += delimiter; // this will add the seperating delimiter before the a given item

        switch (loopPass)
        {
            case 1://first item after delimiter
            if (responseType.length() > 0) str_file_content += responseType;
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
        loopPass++;
    }
    str_file_content += delimiter; // this will add the final delimiter after all the data to mark the end
    return str_file_content;
}

void Cipher::userDataDeliminationWrite(int updateValue, string username, string data2, string data3, string data4, string data5, string data6, string data7){
    ofstream userfile;
    ofstream logonfile;
    switch (updateValue){ //updateValue is for the password, whether it is just getting updated or if this is a new user.
        case 1: //New user account
            mkdir(("./userdata/" + username).c_str(), 0774);
            
            //userfile.open("./userdata/" + username + "/" + username +".dat"); // all user data is stored in the folder called userdata with a naming scheme of "[username].dat"
            userfile.open("./userdata/" + username + "/" + username + ".dat");
            userfile << delimiter << username; // these are all adding data to the file with delimiter seperation.
            if (data2.length() > 0) {userfile << delimiter << data2;} else {userfile << delimiter;}
            if (data3.length() > 0) {userfile << delimiter << data3;} else {userfile << delimiter;}
            if (data4.length() > 0) {userfile << delimiter << data4;} else {userfile << delimiter;}
            if (data5.length() > 0) {userfile << delimiter << data5;} else {userfile << delimiter;}
            if (data6.length() > 0) {userfile << delimiter << data6;} else {userfile << delimiter;}
            if (data7.length() > 0) {userfile << delimiter << data7;} else {userfile << delimiter;}
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
            if (data2.length() > 0) {userfile << delimiter << data2;} else {userfile << delimiter;}
            if (data3.length() > 0) {userfile << delimiter << data3;} else {userfile << delimiter;}
            if (data4.length() > 0) {userfile << delimiter << data4;} else {userfile << delimiter;}
            if (data5.length() > 0) {userfile << delimiter << data5;} else {userfile << delimiter;}
            if (data6.length() > 0) {userfile << delimiter << data6;} else {userfile << delimiter;}
            if (data7.length() > 0) {userfile << delimiter << data7;} else {userfile << delimiter;}
            userfile << delimiter;
            userfile.close(); // done writting to file and now it is closed
            break;
    }
}

void Cipher::userDataDeliminationRead(int updateValue, string username){
    ifstream userstats;
    switch (updateValue){ //updateValue is for the password, whether it is just getting updated or if this is a new user.
        case 1:
            string s;
            userstats.open("./userdata/" + username + "/" + username + ".stat");
            userstats >> s;
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
                }
                loopPass++;
            }
            userstats.close();
            //return str_file_content; //we are not having this return anything right now, however, we may change this later.
            break;
    }
}