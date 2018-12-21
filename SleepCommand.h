//
// Created by moriya on 20/12/18.
//

#ifndef PROJECT_ANOTHER_COPY_SLEEPCOMMAND_H
#define PROJECT_ANOTHER_COPY_SLEEPCOMMAND_H

#include "Command.h"

class SleepCommand : public Command {
    int time;
public:
    SleepCommand(string, string, string);
    int doCommand();

};
#endif //PROJECT_ANOTHER_COPY_SLEEPCOMMAND_H
