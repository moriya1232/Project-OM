

#include "LoopCommand.h"

LoopCommand:: LoopCommand(string line, string name, list<Command*> commands, Pro* pro) : Command(line, name) {
this->commands = commands;
//remove "while " and the "{", "}"
string conditionStr = line.substr(6);
conditionStr = removeOpenSpiPar(conditionStr);
this->condition= new (nothrow) Condition(conditionStr, pro);
this->conditionStr = conditionStr;
this->pro = pro;
}

int LoopCommand::doCommand() {
    while (condition->checkCondition()) {
        //run all the commands
        for (list<Command*>::iterator it = commands.begin(); it != commands.end(); ++it) {
            Command* c = *it;
            c->doCommand();
        }
        //update condition
        this->condition = new (nothrow) Condition(conditionStr, this->pro);
    }
    return 0;
}