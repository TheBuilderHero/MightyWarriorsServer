#include "NPC.h"
#include "../globalVariables.h"
#include <fstream>
#include <iostream>

using namespace std;

NPC::NPC(std::string name, int assignedLandmark){
    //cout << "Starting init" << endl;
    string line;
    ifstream dialogueFile;
    dialogueFile.open(getDialoguePath());
    int working = 1;
    while(getline(dialogueFile, line)){
        //cout << "loop number " << working++ << endl;
        static bool recordingDialogue = false; 
        static bool getDialogueNumber = false; 
        static int dialogueNumber = -1;
        static int lineNum = 0;
        if(getDialogueNumber) {
            //cout << "Pre test: " << line << endl;
            try {
                dialogueNumber = stoi(line);
            } 
            catch(...){
                //cout << "Failed to initallize NPC while(getline(cin, line)) -> if(getDialogueNumber) -> Stoi(line)" << endl;
                //cout << "Post test: " << line << endl;
            }
        }
        if (line == "~"+name+"~"){
            recordingDialogue = true;
            getDialogueNumber = true;
            dialogue.resize(dialogue.size()+1);
            //cout << "this is other: " << line << endl;
        }
        if (line == "~/"+name+"~"){
            recordingDialogue = false;
            dialogueNumber = -1;
            lineNum = 0;
        }
        if(!getDialogueNumber && recordingDialogue){
            //cout << "Help" << endl;
            //Working to add dialogue into memory
            //cout << to_string(dialogue[dialogueNumber].size()) << endl;
            dialogue[dialogueNumber].resize(dialogue[dialogueNumber].size()+1);
            dialogue[dialogueNumber][lineNum]= line;
            lineNum++;
            cout << lineNum << " : Recorded : Size: " << dialogue[dialogueNumber].size() << endl;
        } 
        if (dialogueNumber >= 0 && recordingDialogue) {
            //cout << "Running false change " << endl;
            getDialogueNumber = false;
        }
    }
    this->assignedLandmark = assignedLandmark;
    this->name = name;
    npcID = setUIDForNPC();
}