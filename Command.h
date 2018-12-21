//
// Created by omer on 12/7/18.
//
#ifndef FILE_H
#define FILE_H
using namespace std;


#include <map>
#include <list>
#include <string>
#include "UsefulFunctions.h"
#include "Pro.h"


class Command{
    string line;
    string name;
public:
    Command(string, string);
    virtual int doCommand() = 0;
    string getLine();
    string getName();
};

#endif