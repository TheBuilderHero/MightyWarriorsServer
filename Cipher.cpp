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
}string Cipher::getInventoryPath(std::string username){
    string output = "./userdata/" + username + "/" + username + ".inv";
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
    while ((pos = s.find(delimiterLayer1)) != std::string::npos) {
        token = s.substr(0, pos);
        output = token;
        str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
        s.erase(0, pos + delimiterLayer1.length());
        
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
    while ((pos = s.find(delimiterLayer2)) != std::string::npos) {
        token = s.substr(0, pos);
        output = token;
        str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
        s.erase(0, pos + delimiterLayer2.length());
        
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
        str_file_content += delimiterLayer1; // this will add the seperating delimiter before the a given item
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
    str_file_content += delimiterLayer1; // this will add the final delimiterLayer1 after all the data to mark the end
    return str_file_content;
}
//this functions purpose it to add the delimiters to given sub items 
string Cipher::subCipher(string item1, string item2, string item3, string item4, string item5, string item6, string item7, string item8, string item9, string item10, string item11, string item12, string item13, string item14, string item15, string item16, string item17, string item18, string item19, string item20, string item21, string item22){ // the default values have been set to "" in case no input is given
    int numberOfItems = 22; //max number of items that we can cipher
    //string delimiterLayer2 = "="; //a character that marks the beginning or end of a unit of data

    string str_file_content;
    int loopPass = 1; // start at loop instance 1 to not add extra subDelimiters to the front of the message.
    while (loopPass <= numberOfItems) {
        str_file_content += delimiterLayer2; // this will add the seperating delimiterLayer2 before the a given item
        switch (loopPass)
        {
            case 1://first item after delimiterLayer2
            if (item1.length() > 0) str_file_content += item1;
            break;
            case 2://second item after delimiterLayer2
            if (item2.length() > 0) str_file_content += item2;
            break;
            case 3://third item after delimiterLayer2
            if (item3.length() > 0) str_file_content += item3;
            break;
            case 4://forth item after delimiterLayer2
            if (item4.length() > 0) str_file_content += item4;
            break;
            case 5://fith item after delimiterLayer2
            if (item5.length() > 0) str_file_content += item5;
            break;
            case 6://sixth item after delimiterLayer2
            if (item6.length() > 0) str_file_content += item6;
            break;
            case 7://seventh item after delimiterLayer2
            if (item7.length() > 0) str_file_content += item7;
            break;
            case 8://eighth item after delimiterLayer2
            if (item8.length() > 0) str_file_content += item8;
            break;
            case 9://ninth item after delimiterLayer2
            if (item9.length() > 0) str_file_content += item9;
            break;
            case 10://tenth item after delimiterLayer2
            if (item10.length() > 0) str_file_content += item10;
            break;
            case 11://eleventh item after delimiterLayer2
            if (item11.length() > 0) str_file_content += item11;
            break;
            case 12://twelth item after delimiterLayer2
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
    str_file_content += delimiterLayer2; // this will add the final delimiterLayer2 after all the data to mark the end
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
            userfile << delimiterLayer1 << username; // these are all adding data to the file with delimiter seperation.
            if (data2.length() > 0) {userfile << delimiterLayer1 << data2;} else {userfile << delimiterLayer1;} //race
            if (data3.length() > 0) {userfile << delimiterLayer1 << data3;} else {userfile << delimiterLayer1;} //kit
            if (data4.length() > 0) {userfile << delimiterLayer1 << data4;} else {userfile << delimiterLayer1;} //level
            if (data5.length() > 0) {userfile << delimiterLayer1 << data5;} else {userfile << delimiterLayer1;} //xp
            if (data6.length() > 0) {userfile << delimiterLayer1 << data6;} else {userfile << delimiterLayer1;}
            if (data7.length() > 0) {userfile << delimiterLayer1 << data7;} else {userfile << delimiterLayer1;}
            if (data8.length() > 0) {userfile << delimiterLayer1 << data8;} else {userfile << delimiterLayer1;}
            if (data9.length() > 0) {userfile << delimiterLayer1 << data9;} else {userfile << delimiterLayer1;}
            userfile << delimiterLayer1;
            userfile.close(); // done writting to file and now it is closed

            logonfile.open(getActPath(username)); // this is the file which will store the users accout logon info
            logonfile << delimiterLayer1 << username;
            logonfile << delimiterLayer1 << "0000"; // set defualt password for the account
            logonfile << delimiterLayer1;
            logonfile.close();
            break;}
        case 2:{ //password update
            logonfile.open(getActPath(username)); // this is the file which will store the users accout logon info
            logonfile << delimiterLayer1 << username;
            logonfile << delimiterLayer1 << data2; //this sets the defualt password to the information input in data2 which was given by the user
            logonfile << delimiterLayer1;
            logonfile.close();
            break;}
        case 3:{ //Overwrite the user's stats
            userfile.open(getStatPath(username));
            userfile << delimiterLayer1 << username; // these are all adding data to the file with delimiterLayer1 seperation.
            if (data2.length() > 0) {userfile << delimiterLayer1 << data2;} else {userfile << delimiterLayer1;} //health stat
            if (data3.length() > 0) {userfile << delimiterLayer1 << data3;} else {userfile << delimiterLayer1;} //armor stat
            if (data4.length() > 0) {userfile << delimiterLayer1 << data4;} else {userfile << delimiterLayer1;} //magic res stat
            if (data5.length() > 0) {userfile << delimiterLayer1 << data5;} else {userfile << delimiterLayer1;} //physical damage stat
            if (data6.length() > 0) {userfile << delimiterLayer1 << data6;} else {userfile << delimiterLayer1;} //magic damage stat
            if (data7.length() > 0) {userfile << delimiterLayer1 << data7;} else {userfile << delimiterLayer1;} //Agility stat
            if (data8.length() > 0) {userfile << delimiterLayer1 << data8;} else {userfile << delimiterLayer1;} //stealth stat
            if (data9.length() > 0) {userfile << delimiterLayer1 << data9;} else {userfile << delimiterLayer1;} //Stamina stat
            if (data10.length() > 0) {userfile << delimiterLayer1 << data10;} else {userfile << delimiterLayer1;} //NaturalEnergy stat
            if (data11.length() > 0) {userfile << delimiterLayer1 << data11;} else {userfile << delimiterLayer1;} //Mind stat
            if (data12.length() > 0) {userfile << delimiterLayer1 << data12;} else {userfile << delimiterLayer1;} //psychic damage stat
            userfile << delimiterLayer1;
            userfile.close(); // done writting to file and now it is closed
            break;}
        case 4:{ //update the players's level and XP
            //some user data is stored in "[username].dat"
            //pull current stats from file:
            userDataDeliminationRead(2, username);
            string tempRace; //race
            string tempKit; //kit
            int tempLevel; //level
            double tempXP; //XP
            try{
                tempRace = getItem(2); //race
                tempKit = getItem(3); //kit
                tempLevel = stoi(getItem(4)); //level
                tempXP = stod(getItem(5)); //XP
            } catch(std::invalid_argument){
                cout << "failed: userDataDeliminationWrite case 4" << endl;
            }
            
            
            //write back to file:
            userfile.open(getDatPath(username));
            userfile << delimiterLayer1 << username; // these are all adding data to the file with delimiter seperation.
            if (data2.length() > 0) {userfile << delimiterLayer1 << data2;} else {userfile << delimiterLayer1 << tempRace;} //race
            if (data3.length() > 0) {userfile << delimiterLayer1 << data3;} else {userfile << delimiterLayer1 << tempKit;} //kit
            if (data4.length() > 0) {userfile << delimiterLayer1 << data4;} else {userfile << delimiterLayer1 << tempLevel;} //level
            if (data5.length() > 0) {userfile << delimiterLayer1 << data5;} else {userfile << delimiterLayer1 << tempXP;} //XP
            if (data6.length() > 0) {userfile << delimiterLayer1 << data6;} else {userfile << delimiterLayer1;}
            if (data7.length() > 0) {userfile << delimiterLayer1 << data7;} else {userfile << delimiterLayer1;}
            if (data8.length() > 0) {userfile << delimiterLayer1 << data8;} else {userfile << delimiterLayer1;}
            if (data9.length() > 0) {userfile << delimiterLayer1 << data9;} else {userfile << delimiterLayer1;}
            userfile << delimiterLayer1;
            userfile.close(); // done writting to file and now it is closed
            break;}
        case 5:{ //update user stats
            //pull current stats from file:
            userDataDeliminationRead(1, username);
            int tempHealth;//health stat
            int tempArmor;//armor stat
            int tempMagicResistence;//magic res stat
            int tempPhysicalDamage;//physical damage stat
            int tempMagicDamage;//magic damage stat
            int tempAgility;//Agility stat
            int tempStealth;//stealth stat
            int tempStamina;//Stamina stat
            int tempMana;//NaturalEnergy stat
            int tempMind;//Mind stat
            int tempPsychicDamage;//psychic damage stat
            try{
                tempHealth = stoi(getItem(2));//health stat
                tempArmor = stoi(getItem(3));//armor stat
                tempMagicResistence = stoi(getItem(4));//magic res stat
                tempPhysicalDamage = stoi(getItem(5));//physical damage stat
                tempMagicDamage = stoi(getItem(6));//magic damage stat
                tempAgility = stoi(getItem(7));//Agility stat
                tempStealth = stoi(getItem(8));//stealth stat
                tempStamina = stoi(getItem(9));//Stamina stat
                tempMana = stoi(getItem(10));//NaturalEnergy stat
                tempMind = stoi(getItem(11));//Mind stat
                tempPsychicDamage = stoi(getItem(12));//psychic damage stat
            } catch(std::invalid_argument){
                cout << "failed: userDataDeliminationWrite case 5 temp stats part 1" << endl;
            }
            

            //add new stats to current stats:
            try{
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
            } catch(std::invalid_argument){
                cout << "failed: userDataDeliminationWrite case 5 temp stats part 2" << endl;
            }

            //write new stats to file:
            userfile.open(getStatPath(username));
            userfile << delimiterLayer1 << username; // these are all adding data to the file with delimiterLayer1 seperation.
            if (data2.length() > 0) {userfile << delimiterLayer1 << data2;} else {userfile << delimiterLayer1;} //health stat
            if (data3.length() > 0) {userfile << delimiterLayer1 << data3;} else {userfile << delimiterLayer1;} //armor stat
            if (data4.length() > 0) {userfile << delimiterLayer1 << data4;} else {userfile << delimiterLayer1;} //magic res stat
            if (data5.length() > 0) {userfile << delimiterLayer1 << data5;} else {userfile << delimiterLayer1;} //physical damage stat
            if (data6.length() > 0) {userfile << delimiterLayer1 << data6;} else {userfile << delimiterLayer1;} //magic damage stat
            if (data7.length() > 0) {userfile << delimiterLayer1 << data7;} else {userfile << delimiterLayer1;} //Agility stat
            if (data8.length() > 0) {userfile << delimiterLayer1 << data8;} else {userfile << delimiterLayer1;} //stealth stat
            if (data9.length() > 0) {userfile << delimiterLayer1 << data9;} else {userfile << delimiterLayer1;} //Stamina stat
            if (data10.length() > 0) {userfile << delimiterLayer1 << data10;} else {userfile << delimiterLayer1;} //NaturalEnergy stat
            if (data11.length() > 0) {userfile << delimiterLayer1 << data11;} else {userfile << delimiterLayer1;} //Mind stat
            if (data12.length() > 0) {userfile << delimiterLayer1 << data12;} else {userfile << delimiterLayer1;} //psychic damage stat
            userfile << delimiterLayer1;
            userfile.close(); // done writting to file and now it is closed
            break;}
        case 6:{ //update user Weapons
            //copied from case 5
            //pull current stats from file if it exists:
            ifstream weaponFolderTest;
            weaponFolderTest.open(getWeaponPath(username)); //for testing purposes
            if(weaponFolderTest){ //if the file exists
                weaponFolderTest.close();
                userDataDeliminationRead(3, username);
                int tempID;//weapon ID
                int tempIron;//iron
                int tempWood;//wood
                int tempGems;//gems
                int tempFeet;//feet
                int tempFruit;//fruit
                int tempBrains;//brains
                try{
                    tempID = stoi(getItem(2));//weapon ID
                    tempIron = stoi(getItem(3));//iron
                    tempWood = stoi(getItem(4));//wood
                    tempGems = stoi(getItem(5));//gems
                    tempFeet = stoi(getItem(6));//feet
                    tempFruit = stoi(getItem(7));//fruit
                    tempBrains = stoi(getItem(8));//brains
                } catch(std::invalid_argument){
                    cout << "failed: userDataDeliminationWrite case 6 part 1" << endl;
                }

                    //add new amounts to current stats except ID:
                try{
                    data2 = to_string(tempID);
                    data3 = to_string(tempIron + stoi(data3));
                    data4 = to_string(tempWood + stoi(data4));
                    data5 = to_string(tempGems + stoi(data5));
                    data6 = to_string(tempFeet + stoi(data6));
                    data7 = to_string(tempFruit + stoi(data7));
                    data8 = to_string(tempBrains + stoi(data8));
                } catch(std::invalid_argument){
                    cout << "failed: userDataDeliminationWrite case 6 part 2" << endl;
                }
                
            }

            //write new stats to file:
            weaponStats.open(getWeaponPath(username));
            weaponStats << delimiterLayer1 << username; // these are all adding data to the file with delimiterLayer1 seperation.
            if (data2.length() > 0) {weaponStats << delimiterLayer1 << data2;} else {weaponStats << delimiterLayer1;} //Weapon ID
            if (data3.length() > 0) {weaponStats << delimiterLayer1 << data3;} else {weaponStats << delimiterLayer1;} //iron
            if (data4.length() > 0) {weaponStats << delimiterLayer1 << data4;} else {weaponStats << delimiterLayer1;} //wood
            if (data5.length() > 0) {weaponStats << delimiterLayer1 << data5;} else {weaponStats << delimiterLayer1;} //gems
            if (data6.length() > 0) {weaponStats << delimiterLayer1 << data6;} else {weaponStats << delimiterLayer1;} //feet
            if (data7.length() > 0) {weaponStats << delimiterLayer1 << data7;} else {weaponStats << delimiterLayer1;} //fruits
            if (data8.length() > 0) {weaponStats << delimiterLayer1 << data8;} else {weaponStats << delimiterLayer1;} //brains
            weaponStats << delimiterLayer1;
            weaponStats.close(); // done writting to file and now it is closed
            break;
            }
        case 7:{ //update the players location in file
            //write new location to file:
            ofstream locationFile;
            locationFile.open(getLocationPath(username));
            locationFile << delimiterLayer1 << username; // these are all adding data to the file with delimiterLayer1 seperation.
            if (data2.length() > 0) {locationFile << delimiterLayer1 << data2;} else {locationFile << delimiterLayer1;} //Players current location
            locationFile << delimiterLayer1;
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
                    questFile << data3 << endl; // delimiterLayer1 << data3 << delimiterLayer1 << endl; //removed this delimiterLayer1 addition
                } else if (quest[lineNumber].length() > 0) {
                    questFile << quest[lineNumber] << endl; //write back the data
                } else if(lineNumber == 0) {
                    questFile <<delimiterLayer1<< username <<delimiterLayer1<< endl; //kept delimiterLayer1 addition for username only (probably add current mission to the same line)
                } else {
                    questFile << endl;
                }
                lineNumber++;
            }
            questFile.close(); // done writting to file and now it is closed
            break;
        }
        case 9:{ //update inventory
            //write new inventory to file:
            ofstream inventoryFile;
            inventoryFile.open(getInventoryPath(username));
            inventoryFile << delimiterLayer1 << username; // these are all adding data to the file with delimiterLayer1 seperation.
            if (data2.length() > 0) {inventoryFile << delimiterLayer1 << data2;} else {inventoryFile << delimiterLayer1;} //Player's inventory
            inventoryFile << delimiterLayer1;
            inventoryFile.close(); // done writing to file and now it is closed
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
            while ((pos = s.find(delimiterLayer1)) != std::string::npos) {
                token = s.substr(0, pos);
                output = token;
                str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
                s.erase(0, pos + delimiterLayer1.length());
                
                switch (loopPass){
                    case 1: //first item after delimiterLayer1
                    if (output.length() > 0) username = output; // request numbers give different outputs 1 is username usage, 2 is create user account, 3 is logon
                    break;
                    case 2://second item after delimiterLayer1
                    if (output.length() > 0) item[2] = output; // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
                    break;
                    case 3://third item after delimiterLayer1
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
            while ((pos = s.find(delimiterLayer1)) != std::string::npos) {
                token = s.substr(0, pos);
                output = token;
                str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
                s.erase(0, pos + delimiterLayer1.length());
                
                switch (loopPass){
                    case 1: //first item after delimiterLayer1
                    if (output.length() > 0) username = output;
                    break;
                    case 2://second item after delimiterLayer1
                    if (output.length() > 0) item[2] = output; //this will be where the user's race is stored
                    break;
                    case 3://third item after delimiterLayer1
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
            while ((pos = s.find(delimiterLayer1)) != std::string::npos) {
                token = s.substr(0, pos);
                output = token;
                str_file_content += std::string(token);
                s.erase(0, pos + delimiterLayer1.length());
                
                switch (loopPass){
                    case 1: //first item after delimiterLayer1
                    if (output.length() > 0) username = output;
                    break;
                    case 2://second item after delimiterLayer1      //weaponID
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
            while ((pos = s.find(delimiterLayer1)) != std::string::npos) {
                token = s.substr(0, pos);
                output = token;
                str_file_content += std::string(token);
                s.erase(0, pos + delimiterLayer1.length());
                
                switch (loopPass){
                    case 1: //first item after delimiterLayer1
                    if (output.length() > 0) username = output;
                    break;
                    case 2://second item after delimiterLayer1      //Location
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
        case 6:{//get saved inventory data
            ifstream inventoryFile;
            inventoryFile.open(getInventoryPath(username));
            inventoryFile >> s;
            while ((pos = s.find(delimiterLayer1)) != std::string::npos) {
                token = s.substr(0, pos);
                output = token;
                str_file_content += std::string(token);
                s.erase(0, pos + delimiterLayer1.length());
                
                switch (loopPass){
                    case 1: //first item after delimiterLayer1
                    if (output.length() > 0) username = output;
                    break;
                    case 2://second item after delimiterLayer1      //Full Inventory
                    if (output.length() > 0) item[2] = output;
                    break;
                }
                loopPass++;
            }
            inventoryFile.close();
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
                    temp << dataHeader << delimiterLayer1 << newData << endl;
                } else{
                    //write same data for all headers which do not match dataHeader
                    temp << line << endl;
                }
            } else {
                if (found != std::string::npos){ //if dataheader is found to be within the line
                    //add the new data to the file in place of the old:
                    temp << dataHeader << delimiterLayer1 << newData << endl;
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

//Vector send Layer1:
void Cipher::vectorDeliminateLayer1Head(std::string input){ //adds delivery location information to the vector
    MESSAGE.emplace(MESSAGE.begin(),delimiterLayer1+input);
}
void Cipher::vectorDeliminateLayer1OpenNewInput(std::string input){ //adds delimiter to the begining only //can be used to place new information (note ends previous information entry field)
    MESSAGE.emplace_back(delimiterLayer1+input);
}
void Cipher::vectorDeliminateLayer1EndInput(){ //adds delimiter to the end of vector
    MESSAGE.emplace_back(delimiterLayer1);
}

//Layer 2:
void Cipher::vectorDeliminateLayer2OpenNewInput(std::string input){ //breaks the vector up into chunks of information that the client can then distinguish between for different uses
    MESSAGE.emplace_back(delimiterLayer2+input);
}
void Cipher::vectorDeliminateLayer2EndInput(){ //adds delimiter to the end of vector
    MESSAGE.emplace_back(delimiterLayer2);
}
//Layer 3:
void Cipher::vectorDeliminateLayer3OpenNewInput(std::string input){ //breaks the vector up into chunks of information that the client can then distinguish between for different uses
    MESSAGE.emplace_back(delimiterLayer3+input);
}
void Cipher::vectorDeliminateLayer3EndInput(){ //adds delimiter to the end of vector
    MESSAGE.emplace_back(delimiterLayer3);
}
//Layer 4:
void Cipher::vectorDeliminateLayer4OpenNewInput(std::string input){ //breaks the vector up into chunks of information that the client can then distinguish between for different uses
    MESSAGE.emplace_back(delimiterLayer4+input);
}
void Cipher::vectorDeliminateLayer4EndInput(){ //adds delimiter to the end of vector
    MESSAGE.emplace_back(delimiterLayer4);
}