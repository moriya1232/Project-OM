//
// Created by moriya on 15/12/18.
//

#ifndef PROJECT_PRINTCOMMAND_H
#define PROJECT_PRINTCOMMAND_H

//
// Created by omer on 12/13/18.
//

#include "Command.h"
#include <iostream>


using namespace std;

class PrintCommand : public Command {
    Pro* p;

public:
    PrintCommand(string line, string name, Pro* p);
    int doCommand();
};

#endif //PROJECT_PRINTCOMMAND_H