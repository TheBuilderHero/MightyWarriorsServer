#include "globalVariables.h"
#include "NPCData/NPC.h"
#include <vector>

std::vector<NPC> npcs;

unsigned int setUIDForNPC(){
    static int currentID = 0;
    return currentID++;
}