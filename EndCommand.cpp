//
// Created by omer on 12/13/18.
//

#include "EndCommand.h"

EndCommand:: EndCommand(string line, string name):Command(line,name){}
int EndCommand:: doCommand(){
    return 0;
}