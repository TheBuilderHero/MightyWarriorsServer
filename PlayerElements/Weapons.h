// added these files for the weapon class
#include <string>

using namespace std;

class Weapons
{
private:
    string weaponType;
    int weaponID;
    string usernameForWeapons;
    int accuracy;
    int minPhysicalDamage = 0, minMagicDamage = 0, minPsychicDamage = 0;
    int maxPhysicalDamage, maxMagicDamage, maxPsychicDamage;
    int iron, wood, gems, feet, fruit, brains; //feet means Rabbit feet
public:
    Weapons(std::string username, bool initialSetup = false);
    ~Weapons();

    int getPhysicalDamage();
    int getPhysicalDamageMin();
    int getPhysicalDamageMax();
    int getMagicDamage();
    int getMagicDamageMin();
    int getMagicDamageMax();
    int getPsychicDamage();
    int getPsychicDamageMin();
    int getPsychicDamageMax();
    int getAccuracy(){ return accuracy; }

    int getIron(){ return iron; }
    int getWood(){ return wood; }
    int getGems(){ return gems; }
    int getFeet(){ return feet; }
    int getFruit(){ return fruit; }
    int getBrains(){ return brains; }

    void addIron(int numberAdded){ iron += numberAdded; }
    void addWood(int numberAdded){ wood += numberAdded; }
    void addFeet(int numberAdded){ feet += numberAdded; }
    void addGems(int numberAdded){ gems += numberAdded; }
    void addFruit(int numberAdded){ fruit += numberAdded; }
    void addBrains(int numberAdded){ brains += numberAdded; }

    void loadWeaponData(string username);
    void saveWeaponData(string username);
    void setPlayerWeapon(int weaponChoice);
    int getPlayerWeapon(); //reutrns weapon ID
    std::string getWeaponName(); //returns name of weapon
};

