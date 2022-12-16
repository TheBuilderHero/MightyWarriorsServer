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
    int runningdialogueNumber = -1; //start at (-1) so after adding 1 the index of 0 will get the first test case
    while(getline(dialogueFile, line)){
        //cout << "loop number " << working++ << endl;
        bool singleExceptionRun = false;
        static bool recordingDialogue = false; 
        static bool getDialogueNumber = false; 
        static int dialogueNumber = -1;
        static int lineNum = 0;
        if(getDialogueNumber) {
            runningdialogueNumber++;
            try {
                dialogueNumber = stoi(line);
                cout << "Compare: " << (dialogueNumber != runningdialogueNumber) << endl;
                if (dialogueNumber != runningdialogueNumber) { //prevent incrimentations to dialogue greater than 1
                    cout << "Statement: True" << endl;
                    throw dialogueNumber;
                }
            } 
            catch(invalid_argument){ //runs if there is no mission number
                dialogueNumber = runningdialogueNumber;
                singleExceptionRun = true;

                //Let user know that something went wrong with dialogue incrementation:
                cout << "Failed to initallize NPC while(getline(cin, line)) -> if(getDialogueNumber) -> Stoi(line) -> incrimentation to dialogue greater than 1" << endl;
            }
            catch(int failed){ //runs since there is a mission number but it is out of order
                dialogueNumber = runningdialogueNumber;
                
                //Let user know that something went wrong with dialogue incrementation:
                cout << "Failed to initallize NPC while(getline(cin, line)) -> if(getDialogueNumber) -> Stoi(line) -> incrimentation to dialogue greater than 1" << endl;
            }
            catch(...){
                //Let user know that something went wrong:
                cout << "Failed to initallize NPC while(getline(cin, line)) -> if(getDialogueNumber) -> Stoi(line)" << endl;
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
        if((!getDialogueNumber && recordingDialogue) || singleExceptionRun){
            //cout << "Help" << endl;
            //Working to add dialogue into memory
            //cout << to_string(dialogue[dialogueNumber].size()) << endl;
            dialogue[dialogueNumber].resize(dialogue[dialogueNumber].size()+1);
            dialogue[dialogueNumber][lineNum]= line;
            lineNum++;
            //cout << lineNum << " : Recorded : Size: " << dialogue[dialogueNumber].size() << endl;
            singleExceptionRun = false;
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

string NPC::getAllDialogue(){
    cout << "Output of NPCs: ";
    for (int i = 0; i < 7; i ++) cout << to_string(npcs.at(i).getNpcID()) << " ";
    cout << endl;
    //Working to add dialogue into memory
    //This outputs all the npc's dialogue:
    for (int i = 0; i < npcs.size(); i++) {
        for(int i2 = 0; i2 < npcs.at(i).getDialoguePartCount(); i2++){
            for(int i3 = 0; i3 < npcs.at(i).getDialogueCount(i2); i3++){
                cout << npcs.at(i).getDialogue(i2, i3) << endl;
            }
        }
    }
    return "stuff";
}