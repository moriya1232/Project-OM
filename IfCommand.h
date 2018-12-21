//
// Created by moriya on 17/12/18.
//

#ifndef PROJECT_IFCOMMAND_H
#define PROJECT_IFCOMMAND_H


#include "Command.h"
#include "Condition.h"
#include "Pro.h"

class IfCommand :public Command {
    Condition* condition;
    list<Command*> commands;
    string conditionStr;
    Pro* pro;

public:
    IfCommand(string line, string name, list<Command*> commands, Pro* pro);
    int doCommand();

};

#endif //PROJECT_IFCOMMAND_H