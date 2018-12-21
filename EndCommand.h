//
// Created by moriya on 15/12/18.
//

#ifndef PROJECT_ENDLOOPCOMMAND_H
#define PROJECT_ENDLOOPCOMMAND_H

//
// Created by omer on 12/13/18.
//

#include "Command.h"

class EndCommand : public Command {

public:
    EndCommand(string line, string name);
    int doCommand();

};


#endif //PROJECT_ENDLOOPCOMMAND_H