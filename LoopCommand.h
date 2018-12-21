//
// Created by moriya on 15/12/18.
//

#ifndef PROJECT_LOOPCOMMAND_H
#define PROJECT_LOOPCOMMAND_H

#include "Command.h"
#include "Condition.h"
#include "Pro.h"

class LoopCommand :public Command {
    Condition* condition;
    list<Command*> commands;
    string conditionStr;
    Pro* pro;

public:
    LoopCommand(string line, string name, list<Command*> commands, Pro* pro);
    int doCommand();

};
#endif //PROJECT_LOOPCOMMAND_H
