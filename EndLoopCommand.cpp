//
// Created by omer on 12/13/18.
//

#include "EndLoopCommand.h"

    EndLoopCommand:: EndLoopCommand(string line, string name):Command(line,name){}
    int EndLoopCommand:: doCommand(){
        return 0;
    }