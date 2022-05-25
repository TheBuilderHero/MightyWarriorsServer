#include <iostream>
#include <string>

#include "Map.h"
using namespace std;
//The map and movement are laid out thus:
// 1 - 2 -_3_
// 4 | 5 - 6
string getMapDescription(int location){
    switch(location){
        case 1:
            return "You are in the Glacius Desert. Frozen cacti are scattered everywhere.";
            break;
        case 2:
            return "You are at Lake Argentus. The water shimmers brightly.";
            break;
        case 3:
            return "You are in the city of Sanctus Ludovicus. Many eyes watch you from the shadows.";
            break;
        case 4:
            return "You are in the Ventosus Mountains. Strong winds nearly push you over.";
            break;
        case 5:
            return "You are in Arva Umbra. A few farmers tend crops and livestock.";
            break;
        case 6:
            return "You are in Silva Ignis. Orange and red trees surround you.";
            break;
        default:
            return "You are nowhere.";
            break;
    }

}
//direction is figured thus: 
//     1        N
//   4   2    W   E
//     3        S
bool canTravel(int location, int direction){
    switch(location){
        case 1:
            if(direction == 2 || direction == 3)
                return true;
            else
                return false;
            break;
        case 2:
            if(direction == 1)
                return false;
            else
                return true;
            break;
        case 3:
            if(direction == 4)
                return true;
            else
                return false;
            break;
        case 4:
            if(direction == 1)
                return true;
            else
                return false;
            break;
        case 5:
            if(direction == 1 || direction == 2)
                return true;
            else
                return false;
            break;
        case 6:
            if(direction == 4)
                return true;
            else
                return false;
            break;
        default:
            return false;
            break;
    }

}

string getTravelMessage(int location, int direction){
    switch(location){
        case 1:
            if(direction == 1)
                return "There is only vast ocean to the North.";
            else if(direction == 2)
                return "You leave the bitter cold and advance on a huge lake.";
            else if(direction == 3)
                return "The sands disappear behind as you enter an awesome mountain range.";
            else
                return "There is only vast ocean to the West.";
            break;
        case 2:
           if(direction == 1)
                return "There is only vast ocean to the North.";
            else if(direction == 2)
                return "The lake shrinks in the distance and you come upon a grand city.";
            else if(direction == 3)
                return "You depart the lake and find yourself in a wide stretch of plains.";
            else
                return "You leave the lake behind and advance into a great tundra.";
            break;
        case 3:
            if(direction == 1)
                return "There is only vast ocean to the North.";
            else if(direction == 2)
                return "There is only vast ocean to the East.";
            else if(direction == 3)
                return "The trees are so thick that you cannot find any route South.";
            else
                return "The city shrinks in the distance and you come upon a glittering lake.";
            break;
        case 4:
            if(direction == 1)
                return "The mountains disappear behind as you enter a frozen desert.";
            else if(direction == 2)
                return "The mountains are so tall that you cannot find any path East.";
            else if(direction == 3)
                return "There is only vast ocean to the South.";
            else
                return "There is only vast ocean to the West.";
            break;
        case 5:
            if(direction == 1)
                return "You depart the plains and find yourself at a shining lake.";
            else if(direction == 2)
                return "The plains fade behind and before you appears an orange forest.";
            else if(direction == 3)
                return "There is only vast ocean to the South.";
            else
                return "Mountains which seem to touch the sky deter your passage West.";
            break;
        case 6:
            if(direction == 1)
                return "The trees are so thick that you cannot find any route North.";
            else if(direction == 2)
                return "There is only vast ocean to the East.";
            else if(direction == 3)
                return "There is only vast ocean to the South.";
            else
                return "The forest fades behind and before you appear grassy plains.";
            break;
        default:
            return "You were nowhere, did you find your way out?";
            break;
    }
}