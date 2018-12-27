//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//
//

#include "IfCommand.h"

/**
 * this function is a constructor of if command. in this constractor we initialize
 * the condition in string by extract the values from the line, when we will execute the
 * command we will create the condition and will check it.
 * @param line - the line of the command
 * @param name - the name of the command
 * @param commands - the list of the command that the if command has.
 * @param pro - the pro
 */
IfCommand:: IfCommand(string line, string name, list<Command*> commands, Pro* pro) : Command(line, name) {
    this->commands = commands;
    //remove "while " and the "{", "}"
    string conditionStr = line.substr(3);
    conditionStr = conditionStr.substr(0,conditionStr.length()-2);
    this->conditionStr = conditionStr;
    this->pro = pro;
}

/**
 * this fucntion does the command by over all the list of commands that we has in
 * this if command and execute any command.
 * @return 0 if it seccess
 */
int IfCommand::doCommand() {
    //create the condition
    this->condition= new (nothrow) Condition(conditionStr, pro);
    this->pro->getCollector()->addItem(this->condition);
    if(this->condition->checkCondition()) {
        //run all the commands
        for (list<Command *>::iterator it = commands.begin(); it != commands.end(); ++it) {
            Command *c = *it;
            c->doCommand();
        }
    }
    return 0;
}