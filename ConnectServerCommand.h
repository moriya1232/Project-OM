//
// Created by moriya on 15/12/18.
//

#ifndef PROJECT_CONNECTSERVERCOMMND_H
#define PROJECT_CONNECTSERVERCOMMND_H

//
// Created by omer on 12/8/18.
//

#include "Command.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <thread>
#include "BindVarCommand.h"

class ConnectServerCommand : public Command {

    void setBuffer(char[]);
    string getName(char[]);
    static bool hasMessage(char[]);
    static double parseResult(char[], int);
    static bool checkIfBind(char[]);
    static bool haveToUpdate(char[], int);
    void strcpy(char*, string);
    static void clearIP(char*, int);
    static bool ifShouldUpdate(char);
    Pro* p;

public:
    ConnectServerCommand(string line, string name, Pro* p);
    ConnectServerCommand(Pro*);
    string extractWordFromLine(string line);
    static void connectServer(char*, string, ConnectServerCommand, int);
    static char* parseIP(string IP);
    int doCommand();
    void setValue(string, double);
};
#endif //PROJECT_CONNECTSERVERCOMMND_H