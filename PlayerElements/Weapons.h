// added these files for the weapon class
#include <string>

using namespace std;

class Weapons
{
private:
    string weaponType;
    int physicalDamage, magicDamage, psychicDamage, accuracy;
    int iron, wood, gems, feet, fruit, brains;
public:
    Weapons(int weaponChoice);
    ~Weapons();

    int getPhysicalDamage(){ return physicalDamage + (iron * 2); }
    int getMagicDamage(){ return magicDamage + (gems * 2); }
    int getPsychicDamage(){ return psychicDamage + brains; }
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
};

