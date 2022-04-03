#include <iostream>
#include "Enemies.h"

using namespace std;

void Enemies::mutantElf() {
    cout << "Mutant Elf V2!" << endl;
    name = "Mutant Elf";
    health = 40;
    attack = 10;
    armor = 2;
    magicAttack = 5;
    magicResistence = 5;
    level = 1;
    xpDrop = 20;
}