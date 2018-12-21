//
// Created by moriya on 20/12/18.
//

#include "SleepCommand.h"


SleepCommand::SleepCommand(string line, string name, string time):Command(line,name){
this->time = stoi(time);
}

int SleepCommand::doCommand() {
    chrono::milliseconds timespan(this->time); // we need to parse the actual value!
}