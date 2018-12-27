//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//
//

#include "LoopCommand.h"


/**
 * this function is a constructor of loop command. in this constractor we initialize
 * the condition in string by extract the values from the line. when we will execute the
 * command we will create the condition and will check it.
 * @param line - the line of the command
 * @param name - the name of the command
 * @param commands - the list of the command that the loop command has.
 * @param pro - the pro
 */
LoopCommand:: LoopCommand(string line, string name, list<Command*> commands, Pro* pro) : Command(line, name) {
this->commands = commands;
//remove "while " and the "{", "}"
string conditionStr = line.substr(6);
conditionStr = removeOpenSpiPar(conditionStr);
this->conditionStr = conditionStr;
this->pro = pro;
}

/**
 * this fucntion does the command by over all the list of commands that we has in
 * this if command and execute any command. after it, it wil check the condition and will do
 * it again and again by checking the condition
 * @return 0 if it seccess
 */
int LoopCommand::doCommand() {
    this->condition= new (nothrow) Condition(conditionStr, pro);
    //the loop
    while (condition->checkCondition()) {
        //run all the commands
        for (list<Command*>::iterator it = commands.begin(); it != commands.end(); ++it) {
            Command* c = *it;
            c->doCommand();
        }

        delete this->pro->getCollector();
        this->pro->createCollector();
        //update condition
        delete this->condition;
        this->condition = new (nothrow) Condition(conditionStr, this->pro);
    }
    this->pro->getCollector()->addItem(this->condition);
    return 0;
}