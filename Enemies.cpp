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
    radiation = 18;
    level = 1;
    xpDrop = 20;
    //Radiation damage that mutants can inflict?
}

void Enemies::highwayRobber(){
    name = "Highway Robber";
    health = 60;
    attack = 15;
    armor = 10;
    magicAttack = 2;
    magicResistence = 2;
    level = 1;
    xpDrop = 10;
}

void Enemies::orc(){
    name = "Orc";
    health = 70;
    attack = 20;
    armor = 15;
    magicAttack = 10;
    magicResistence = 7;
    level = 1;
    xpDrop = 10;
}

void Enemies::sasquatch(){
    name = "Sasquatch";
    health = 120;
    attack = 35;
    armor = 20;
    magicAttack = 15;
    magicResistence = 3;
    level = 1;
    xpDrop = 80;
}

void Enemies::skunk(){
    name = "Skunk";
    health = 25;
    attack = 10;
    armor = 1;
    magicAttack = 2;
    magicResistence = 2;
    toxicAttack = 17;
    level = 1;
    xpDrop = 7;
    //Skunk has very low armor and magic stats to compensate for toxic damage.
}

void Enemies::mutantSkunk(){
    name = "Mutant Skunk";
    health = 25;
    attack = 10;
    armor = 1;
    magicAttack = 0;
    magicResistence = 0;
    toxicAttack = 17;
    radiation = 10;
    level = 1;
    xpDrop = 12;
}

void Enemies::giantRaccoon(){
    name = "Giant Raccoon";
    health = 350;
    attack = 65;
    armor = 80;
    magicAttack = 25;
    magicResistence = 15;
    level = 1;
    xpDrop = 500;
    //GIANT RACCOON!!! Mini-boss.
}

void Enemies::evilWizard(){
    name = "Evil Wizard";
    health = 80;
    attack = 20;
    armor = 8;
    magicAttack = 20;
    magicResistence = 12;
    level = 1;
    xpDrop = 80;
}

void Enemies::witch(){
    name = "Witch";
    health = 70;
    attack = 13;
    armor = 10;
    magicAttack = 30;
    magicResistence = 15;
    level = 1;
    xpDrop = 80;
}

void Enemies::mutantGhost(){
    name = "Mutant Ghost";
    health = 95;
    attack = 20;
    armor = 1;
    magicAttack = 35;
    magicResistence = 23;
    level = 1;
    xpDrop = 100;
}

void Enemies::wereWolf(){
    name = "Werewolf";
    health = 80;
    attack = 25;
    armor = 5;
    magicAttack = 12;
    magicResistence = 8;
    level = 1;
    xpDrop = 70;
}