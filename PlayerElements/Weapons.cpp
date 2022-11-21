// added these files for the weapon class

#include "Weapons.h"
#include "../Cipher.h"

using namespace std;

Weapons::Weapons(string username, bool initialSetup){
    usernameForWeapons = username; //set the class variable to store the username of the person
    minPhysicalDamage = minMagicDamage = minPsychicDamage = 0;
    if(!initialSetup){
        loadWeaponData(usernameForWeapons);
        setPlayerWeapon(weaponID); //weaponID is pulled from file in loadWeaponData funciton
    } else {
        iron = 0;
        wood = 0;
        gems = 0;
        feet = 0;
        fruit = 0;
        brains = 0;
    }
}

void Weapons::loadWeaponData(string username){    //save the weapon bonus' to file:
    //cout << "Weapon read started\n";
    Cipher cipher;
    //retrive from file:
    cipher.userDataDeliminationRead(6, username);
    cipher.subDecipher("=" + cipher.getItem(2), 0);
    cipher.userDataDeliminationRead(3, username);
    //zero all values:
    iron = 0;
    wood = 0;
    gems = 0;
    feet = 0;
    fruit = 0;
    brains = 0;
    //cout << cipher.getItem(1) + "~" + cipher.getItem(2) + "~" + cipher.getItem(3) + "~" + cipher.getItem(4) + "~" + cipher.getItem(5) + "~" + cipher.getItem(6) + "~" + cipher.getItem(7) + "~" + cipher.getItem(8) + "~\n"; 
    //set all values based on file:
    try{
        weaponID = stoi(cipher.getItem(0, 1));
        iron += stoi(cipher.getItem(3));
        wood += stoi(cipher.getItem(4));
        gems += stoi(cipher.getItem(5));
        feet += stoi(cipher.getItem(6));
        fruit += stoi(cipher.getItem(7));
        brains += stoi(cipher.getItem(8));
    } catch(std::invalid_argument){
        cout << "failed: Weapons::loadWeaponData" << endl;
    }
    
    //cout << "Weapon read successful\n";
}
void Weapons::saveWeaponData(string username){    //save the weapon bonus' to file:
    Cipher cipher;
    cipher.userDataDeliminationWrite(6, username, to_string(weaponID) ,to_string(iron), to_string(wood), to_string(gems), to_string(feet), to_string(fruit), to_string(brains));
}

int Weapons::getPhysicalDamage(){ //this is used for battle to get a value between the min and max values
    srand (time(NULL));
    if(maxPhysicalDamage == 0){ //resolve devide by zero issue
        maxPhysicalDamage++;
    }
    int damageRange = maxPhysicalDamage - minPhysicalDamage;
    return (rand() % damageRange + minPhysicalDamage);  //random number between min and max
}
int Weapons::getPhysicalDamageMax(){
    return maxPhysicalDamage; 
}
int Weapons::getPhysicalDamageMin(){
    return minPhysicalDamage; 
}
int Weapons::getMagicDamage(){ //this is used for battle to get a value between the min and max values
    srand(time(NULL));
    if(maxMagicDamage == 0){//resolve devide by zero issue
        maxMagicDamage++;
    }
    int damageRange = maxMagicDamage - minMagicDamage;
    return (rand() % damageRange + minMagicDamage); //random number between min and max
}
int Weapons::getMagicDamageMin(){
    return minMagicDamage;
}
int Weapons::getMagicDamageMax(){
    return maxMagicDamage; 
}
int Weapons::getPsychicDamage(){ //this is used for battle to get a value between the min and max values
    srand(time(NULL));
    if(maxPsychicDamage == 0){//resolve devide by zero issue
        maxPsychicDamage++;
    }
    int damageRange = maxPsychicDamage - minPsychicDamage;
    return (rand() % damageRange + minPsychicDamage); //random number between min and max
}
int Weapons::getPsychicDamageMin(){
    return minPsychicDamage; 
}
int Weapons::getPsychicDamageMax(){
    return maxPsychicDamage; 
}

void Weapons::setPlayerWeapon(int weaponChoice) 
{
    switch(weaponChoice){
        case 1: 
            weaponType = "Sword";
            weaponID = 1;
            maxPhysicalDamage = 20;
            maxMagicDamage = 0;
            maxPsychicDamage = 0;
            accuracy = 5; //maybe out of 10
            break;
        case 2: 
            weaponType = "Bow";
            weaponID = 2;
            maxPhysicalDamage = 12;
            maxMagicDamage = 0;
            maxPsychicDamage = 0;
            accuracy = 4; 
            break;
        case 3: 
            weaponType = "Dagger";
            weaponID = 3;
            maxPhysicalDamage = 12;
            maxMagicDamage = 0;
            maxPsychicDamage = 0;
            accuracy = 6; 
            break;
         case 4: 
            weaponType = "Fire Rune";
            weaponID = 4;
            maxPhysicalDamage = 3;
            maxMagicDamage = 18;
            maxPsychicDamage = 0;
            accuracy = 8;
            break;
        case 5: 
            weaponType = "Wind Rune";
            weaponID = 5;
            maxPhysicalDamage = 6;
            maxMagicDamage = 14;
            maxPsychicDamage = 0;
            accuracy = 9;
            break;
        case 6: 
            weaponType = "Ice Spike";
            weaponID = 6;
            maxPhysicalDamage = 16;
            maxMagicDamage = 36;
            maxPsychicDamage = 0;
            accuracy = 2;
            break;
        case 7: 
            weaponType = "Black Book";
            weaponID = 7;
            maxPhysicalDamage = 8;
            maxMagicDamage = 8;
            maxPsychicDamage = 5;
            accuracy = 10;
            break;
        default:
        break;
    }
}
int Weapons::getPlayerWeapon(){
    return weaponID;
}
string Weapons::getWeaponName(){
    return weaponType;
}

Weapons::~Weapons() //Weapon class destructor
{
    saveWeaponData(usernameForWeapons);
}