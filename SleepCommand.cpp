//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//

#include "SleepCommand.h"
#include "unistd.h"


/**
 * this function is a constractor for sleep command
 * @param line - the line of the command
 * @param name - the name of this command
 * @param time - how much tine we need to sleep
 */
SleepCommand::SleepCommand(string line, string name, string time):Command(line,name){
    this->time = stoi(time);
}

/**
 * this function execute the sleeping.
 * @return 0 -it success
 */
int SleepCommand::doCommand() {
    sleep(this->time/1000); // we need to parse the actual value!
    return 0;
}