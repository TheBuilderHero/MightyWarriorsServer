// added these files for the weapon class
#include <string>

using namespace std;

class Weapons
{
private:
    string weaponType;
    int physicalDamage, magicDamage, psychicDamage, accuracy;
    int iron, wood, gems, feet, fruit, brains; //feet means Rabbit feet
public:
    Weapons(int weaponChoice);
    ~Weapons();

    int getPhysicalDamage();
    int getMagicDamage();
    int getPsychicDamage();
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

<<<<<<< HEAD
    void loadWeaponData(string username);
    void saveWeaponData(string username);
=======
    int getPlayerWeapon(std::string username);
>>>>>>> 92a442f06f40989cdefb55b9431b7e1d2b2b9742
};

