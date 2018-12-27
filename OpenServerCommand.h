//
// Created by moriya on 15/12/18.
//

#ifndef PROJECT_OPENSERVERCOMMAND_H
#define PROJECT_OPENSERVERCOMMAND_H


//
// Created by omer on 12/7/18.
//

#include "Command.h"
#include <unistd.h>
#include <stdio.h>
#include <thread>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <ctype.h>
#include "SleepCommand.h"

using namespace std;

class OpenServerCommand : public Command {

    Pro* p;
    static bool dataReceived(char*, int);

public:
    OpenServerCommand(string line, string name, Pro* p);

    static void openServer(string s1, string s2, OpenServerCommand*);

    int doCommand();
};
#endif //PROJECT_OPENSERVERCOMMAND_H