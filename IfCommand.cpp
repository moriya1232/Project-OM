//
// Created by moriya on 17/12/18.
//



#include "IfCommand.h"

IfCommand:: IfCommand(string line, string name, list<Command*> commands, Pro* pro) : Command(line, name) {
    this->commands = commands;
//remove "while " and the "{", "}"
    string conditionStr = line.substr(3);
    conditionStr = conditionStr.substr(0,conditionStr.length()-2);
    this->condition= new (nothrow) Condition(conditionStr, pro);
    this->conditionStr = conditionStr;
    this->pro = pro;
}

int IfCommand::doCommand() {
    if(this->condition->checkCondition()) {
        //run all the commands
        for (list<Command *>::iterator it = commands.begin(); it != commands.end(); ++it) {
            Command *c = *it;
            c->doCommand();
        }
    }
    //update condition
    //this->condition = new (nothrow) Condition(conditionStr, this->pro);
    return 0;
}