#pragma once
#include <string>
#include <vector>

class NPC{
    private:
        int assignedLandmark;
        std::string name;
        int npcID;
        std::vector<std::vector<std::string>> dialogue;
    public:
        NPC(std::string name, int assignedLandmark);
        std::string getDialoguePath() { return std::string("./NPCData/dialogue.txt"); }
        int getNpcID(){ return npcID; }
        std::string getDialogue(int number, int part){ return dialogue[number][part];}
        int getDialoguePartCount() { int i = dialogue.size(); return i; }
        int getDialogueCount(int number) { int i = dialogue[number].size(); return i; }
        std::string getAllDialogue();
        std::string getName() { return name; }
};