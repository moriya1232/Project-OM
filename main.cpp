#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "OpenServerCommand.h"
#include "ConnectServerCommand.h"
#include "UpdateCommand.h"
#include "SetVarCommand.h"
#include <unordered_map>
#include <unordered_map>
#include "PrintCommand.h"
#include "Command.h"
#include "Var.h"
#include "EndCommand.h"
#include "Condition.h"
#include "LoopCommand.h"
#include "IfCommand.h"
#include "SleepCommand.h"
#include <regex>
#include "Enterc.h"
#include "ExitCommand.h"



using namespace std;
list<Command*> getCommands(list<string>, Pro* pro);

unordered_map<string, double>* symbolTable = new unordered_map<string,double>();

bool checkIfProper(string name, string line) {
    if(name=="open") {
        regex openS("[[:space:]]*(openDataServer)[[:space:]]+[[:digit:]]+[[:space:]]+[[:digit:]]+[[:space:]]*");
        return regex_match(line, openS);
    } else if(name=="connect") {
        regex connentS("[[:space:]]*(connect)[[:space:]]+[[:digit:]]+(.)[[:digit:]]+(.)"
         "[[:digit:]]+(.)[[:digit:]][[:space:]]+[[:digit:]]+[[:space:]]*");
        return regex_match(line,connentS);
    } else if (name=="var") {
        regex varS("[[:space:]]*(var)[[:space:]]+[a-z]+[[:digit:]]*[[:space:]]*(=)[[:space:]]*.*");
        return regex_match(line,varS);
    }
}

Command* parseCommand(string line,list<string> lines, int& counter, Pro* p) {

    if (extractWordFromLine(line) == "Enterc" || extractWordFromLine(line) == "enterc") {
        Enterc* c2 = new (nothrow) Enterc(line,"Enterc");
        p->getCollectorCommands()->addItem(c2);
        return c2;
    }
    // remove the number
    //line = removeNumBeginLine(line);
    line = removeSpaces(line);
    string temp = line;
    string commandFromLine = extractWordFromLine(line);
    if (commandFromLine == "}") {
        EndCommand* end = new (nothrow) EndCommand(line, "End");
        p->getCollectorCommands()->addItem((end));
        //cp = &end;
        return end;

    }

    Command* cp;
    if (commandFromLine[0] == '{') {
        commandFromLine = commandFromLine.substr(1);
        commandFromLine = removeSpaces(commandFromLine);
        if (commandFromLine == "") {
            return NULL;
        }
    }
    string lineExceptCommand = line.substr(commandFromLine.length() + 1);
    if (commandFromLine == "openDataServer") {
        if (!checkIfProper("open", line)){
            throw "the line of openDataServer don't properly!";
        }
        OpenServerCommand* c1 = new (nothrow) OpenServerCommand(line, "OpenServer",p);
        p->getCollectorCommands()->addItem(c1);
        return c1;
    } else if (commandFromLine == "connect") {
        if (!checkIfProper("connect", line)) {
            throw "the line of connect don't properly!";
        }
        ConnectServerCommand* c2 = new (nothrow) ConnectServerCommand(line,"ConnectServer", p);
        p->getCollectorCommands()->addItem(c2);
        return c2;
    } else if (commandFromLine == "var") {
        if (!checkIfProper("var", line)) {
            throw "the line of var don't properly!";
        }
        SetVarCommand* c3 = new (nothrow) SetVarCommand(line, "Var", p);
        p->getCollectorCommands()->addItem(c3);
        return c3;

    } else if (commandFromLine == "while" || commandFromLine == "for") {
        list<string> linesInLoop;
        int temp=0;
        for(list<string>::iterator it = lines.begin(); it !=lines.end();++it, temp++) {
            if (temp>counter) {
                string tempStr = *it;
                tempStr = removeSpaces(tempStr);
                counter++;
                if (tempStr == "}") {
                    break;
                } else if (tempStr[tempStr.length()-1] == '}') {
                    tempStr = tempStr.substr(0, tempStr.length()-2);
                    linesInLoop.push_back(tempStr);
                    break;
                }

                linesInLoop.push_back(tempStr);
            }
        }
        list<Command*> commands = getCommands(linesInLoop, p);
        LoopCommand* loop = new (nothrow) LoopCommand(line,"Loop", commands ,p);
        p->getCollectorCommands()->addItem(loop);
        return loop;
    } else if (commandFromLine == "if") {
        list<string> linesInIf;
        int temp=0;
        for(list<string>::iterator it = lines.begin(); it !=lines.end();++it, temp++) {
            if (temp>counter) {
                string tempStr = *it;
                tempStr = removeSpaces(tempStr);
                counter++;
                if (tempStr == "}") {
                    break;
                } else if (tempStr[tempStr.length()-1] == '}') {
                    tempStr = tempStr.substr(0, tempStr.length()-2);
                    linesInIf.push_back(tempStr);
                    break;
                }
                linesInIf.push_back(tempStr);
            }
        }
        list<Command*> commands = getCommands(linesInIf, p);
        IfCommand* ifCommand = new (nothrow) IfCommand(line,"If", commands ,p);
        p->getCollectorCommands()->addItem(ifCommand);
        return ifCommand;
    } else if (commandFromLine == "print") {
        PrintCommand* print = new (nothrow) PrintCommand(line,"Print",p);
        p->getCollectorCommands()->addItem(print);
        return print;
    } else if (commandFromLine == "sleep") {
        line = line.substr(extractWordFromLine(line).length() + 1);
        string time = extractWordFromLine(line);
        SleepCommand* sc = new (nothrow) SleepCommand(line, "sleep", time);
        p->getCollectorCommands()->addItem(sc);
        return sc;
    } else if (commandFromLine == "exit") {
        ExitCommand* ex = new (nothrow) ExitCommand(line, "exit", p);
        p->getCollectorCommands()->addItem(ex);
        return ex;
    }
    else {
        UpdateCommand* c4 = new (nothrow) UpdateCommand(line,"update", p);
        p->getCollectorCommands()->addItem(c4);
        return c4;
    }
}

list<Command*> getCommands(list<string> lines, Pro* p) {
    list<Command*> result;
    int counter=0;
    bool inLoop = false;
    for (list<string>::iterator it = lines.begin(); it != lines.end(); it++) {
        string line = *it;
        Command* c = parseCommand(line,lines,counter, p);
        if(c!=NULL) {
            if (!inLoop) {
                result.push_back(c);
                counter++;
            }
            if (c->getName() == "Loop" || c->getName() == "If") {
                inLoop = true;
            } else if (c->getName() == "End") {
                inLoop = false;
            }
        }
    }
    return result;
}

list<string> lexer(string fileName) {
    ifstream inFile(fileName);
    string line = "";
    list<string> result;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            if (removeSpaces(line)==""){
                continue;
            }
            result.push_back(line);
        }
    }
    return result;
}

int main() {
    Pro* p = new (nothrow) Pro(symbolTable);
    list<string> namesOfCommands = lexer("Test.txt");
    list<Command*> commands = getCommands(namesOfCommands, p);
    // a creation for an iterator of the strings
    Command* c;
    for (list<Command*>::iterator it = commands.begin(); it != commands.end(); it++){
        c = *it;
        if (c != NULL)
            c->doCommand();
    }
    return 0;
}