//
// Created by moriya on 13/12/18.
//
#include "Pro.h"
#include <string>
#include "ConnectServerCommand.h"
using namespace std;

Pro:: Pro(){
    this->symbolTable = setSymbolTable();
    this->buffer = "";
    unordered_map<string,list<string>> bindMap;
    this->bindMap = bindMap;
    list<double> tempList;
    this->values = tempList;
    setLines();
    this->currVal = 0;
}

bool Pro::isVarBinded(string vn) {
    try {
        list<string> tempList = bindMap.at(vn);
        return true;
    } catch (exception e) {
        return false;
    }
}

bool Pro::isVarInSymbolTable(string vn) {
    try {
        double tempList = this->symbolTable.at(vn);
        return true;
    } catch (exception e) {
        return false;
    }
}

string Pro::getNameByDirectory(string direct) {
    unordered_map<string,string> m = this->namesAndDirectory;
    for (unordered_map<string,string>::iterator it = m.begin(); it != m.end(); it++) {
        string currDir = it->second;
        if (currDir == direct) {
            return it->first;
        }
    }
    return "";
}

void Pro::setValues(list<double> lis) {
    //g_i_values.lock();
    this->values = lis;
    // now update all the relevant vars
    list<double>::iterator itValues = lis.begin();
    for (list<string>::iterator itDir = lines.begin(); itDir != lines.end(); itDir++) {
        string currDir = *itDir;
        string currName = getNameByDirectory(currDir);
        double currVal = *itValues;
        this->setVar(currName, currVal);
        itValues++;
    }
    //g_i_values.unlock();
}

unordered_map<string,double> Pro:: setSymbolTable() {
    unordered_map<string, double> symbolTable;
    symbolTable.insert(make_pair("breaks", 0));
    symbolTable.insert(make_pair("throttle", 0));
    symbolTable.insert(make_pair("heading", 0));
    symbolTable.insert(make_pair("airspeed", 0));
    symbolTable.insert(make_pair("roll", 0));
    symbolTable.insert(make_pair("pitch", 0));
    symbolTable.insert(make_pair("rudder", 0));
    symbolTable.insert(make_pair("aileron", 0));
    symbolTable.insert(make_pair("elevator", 0));
    symbolTable.insert(make_pair("alt", 0));
    symbolTable.insert(make_pair("/instrumentation/airspeed-indicator/indicated-speed-kt",0));
    symbolTable.insert(make_pair("/instrumentation/altimeter/indicated-altitude-ft",0));
    symbolTable.insert(make_pair("/instrumentation/altimeter/pressure-alt-ft",0));
    symbolTable.insert(make_pair("/instrumentation/attitude-indicator/indicated-pitch-deg",0));
    symbolTable.insert(make_pair("/instrumentation/attitude-indicator/indicated-roll-deg",0));
    symbolTable.insert(make_pair("/instrumentation/attitude-indicator/internal-pitch-deg",0));
    symbolTable.insert(make_pair("/instrumentation/attitude-indicator/internal-roll-deg",0));
    symbolTable.insert(make_pair("/instrumentation/encoder/indicated-altitude-ft",0));
    symbolTable.insert(make_pair("/instrumentation/encoder/pressure-alt-ft",0));
    symbolTable.insert(make_pair("/instrumentation/gps/indicated-altitude-ft",0));
    symbolTable.insert(make_pair("/instrumentation/gps/indicated-ground-speed-kt",0));
    symbolTable.insert(make_pair("/instrumentation/gps/indicated-vertical-speed",0));
    symbolTable.insert(make_pair("/instrumentation/heading-indicator/indicated-heading-deg",0));
    symbolTable.insert(make_pair("/instrumentation/magnetic-compass/indicated-heading-deg",0));
    symbolTable.insert(make_pair("/instrumentation/slip-skid-ball/indicated-slip-skid",0));
    symbolTable.insert(make_pair("/instrumentation/turn-indicator/indicated-turn-rate",0));
    symbolTable.insert(make_pair("/instrumentation/vertical-speed-indicator/indicated-speed-fpm",0));
    symbolTable.insert(make_pair("/controls/flight/aileron",0));
    symbolTable.insert(make_pair("/controls/flight/elevator",0));
    symbolTable.insert(make_pair("/controls/flight/rudder",0));
    symbolTable.insert(make_pair("/controls/flight/flaps",0));
    symbolTable.insert(make_pair("/controls/engines/engine/throttle",0));
    symbolTable.insert(make_pair("/engines/engine/rpm",0));
    return symbolTable;
}

void Pro:: setLines(){
    this->lines.push_back("/instrumentation/airspeed-indicator/indicated-speed-kt");
    this->lines.push_back("/instrumentation/altimeter/indicated-altitude-ft");
    this->lines.push_back("/instrumentation/altimeter/pressure-alt-ft");
    this->lines.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg");
    this->lines.push_back("/instrumentation/attitude-indicator/indicated-roll-deg");
    this->lines.push_back("/instrumentation/attitude-indicator/internal-pitch-deg");
    this->lines.push_back("/instrumentation/attitude-indicator/internal-roll-deg");
    this->lines.push_back("/instrumentation/encoder/indicated-altitude-ft");
    this->lines.push_back("/instrumentation/encoder/pressure-alt-ft");
    this->lines.push_back("/instrumentation/gps/indicated-altitude-ft");
    this->lines.push_back("/instrumentation/gps/indicated-ground-speed-kt");
    this->lines.push_back("/instrumentation/gps/indicated-vertical-speed");
    this->lines.push_back("/instrumentation/heading-indicator/indicated-heading-deg");
    this->lines.push_back("/instrumentation/magnetic-compass/indicated-heading-deg");
    this->lines.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
    this->lines.push_back("/instrumentation/turn-indicator/indicated-turn-rate");
    this->lines.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    this->lines.push_back("/controls/flight/aileron");
    this->lines.push_back("/controls/flight/elevator");
    this->lines.push_back("/controls/flight/rudder");
    this->lines.push_back("/controls/flight/flaps");
    this->lines.push_back("/controls/engines/engine/throttle");
    this->lines.push_back("/engines/engine/rpm");

}

bool Pro::isExsistInSymbolTable(string vn) {
    try {
        this->symbolTable.at(vn);
        return true;
    } catch (exception e) {
        return false;
    }
}

void Pro::setCurrVal(double d) {
    this->currVal = d;
}

void Pro::setVar(string vn, double newValue) {
    if (isExsistInSymbolTable(vn)) {
        // update in the symbol table
        this->symbolTable.erase(vn);
    }
    this->symbolTable.insert(make_pair(vn, newValue));
    // if someone is binded to var, update him aswell
    if (isVarBinded(vn)) {
        list<string> bv = this->bindMap.at(vn);
        for (list<string>::iterator it = bv.begin(); it != bv.end(); it++) {
            string currName = *it;
            if (currName[0] == '"') {
                string name = getNameByDirectory(currName);
                setValueInSimulator(name, currName, newValue);
            } else {
                double currValue = this->symbolTable.at(currName);
                if (currValue != newValue) {
                    this->setVar(currName, newValue);
                }
            }
        }
    }
}

void Pro:: setVarBind(string var1, string var2) {
    try {
        this->bindMap.at(var1).push_back(var2);
    } catch (exception e) {
        list<string> names;
        names.push_back(var2);
        this->bindMap.insert(make_pair(var1, names));
    }
    try {
        this->bindMap.at(var2).push_back(var1);
    } catch (exception e){
        list<string> names;
        names.push_back(var1);
        this->bindMap.insert(make_pair(var2, names));
    }
}

unordered_map<string,double> Pro::getSymbolTable() {
    return this->symbolTable;
}

double Pro::getValueFromSimulator(string name, string directory) {
    string s = "get" + directory + '\n';
    this->setBuffer(s, s.length());
    string line = "connect " + this->getIP() + " " + this->getPort();
    ConnectServerCommand csc = ConnectServerCommand(line, "connect", this);
    this->currName = name;
    csc.doCommand();
    return currVal;
}

list<double> Pro::getValues(char* buffer) {
    list<double> result;
    bool run = true;
    string s = "";
    int i = 0;
    char c = buffer[i];
    while (run) {
        if (c == '\n') {
            run = false;
        }
        while (c != ',' && run) {
            s += c;
            c = buffer[++i];
            if (c == '\n') {
                run = false;
            }
        }
        double d = stod(s);
        result.push_back((d));
        c = buffer[++i];
        s = "";
    }
    return result;
}

string Pro::getBuffer() {
    return this->buffer;
}

int Pro::getBufferLength() {
    return this->size;
}

void Pro::setBuffer(string buff, int size) {
    this->size = size;
    this->buffer = new (nothrow) char(sizeof(char) * size);
    this->buffer = "";
    char result[256] = { '\0' };
    for (int i = 0; i < size; i++) {
        this->buffer += buff[i];
    }
}

unordered_map<string,list<string>> Pro::getBindMap() {
    return this->bindMap;
}

void Pro::addNamesAndDirectory(string name, string directory) {
    this->namesAndDirectory.insert(make_pair(name, directory));
}

void Pro:: setVarNamesAndDirectory(string name, string dir) {
    this->namesAndDirectory.erase(name);
    this->namesAndDirectory.insert(make_pair(name, dir));
}

unordered_map<string, string> Pro::getNamesAndDirectories() {
    return this->namesAndDirectory;
}

void Pro::addSymbolTable(string name, double d) {
    this->symbolTable.insert(make_pair(name,d));
}

void Pro:: clearListForExp() {
   this->listForExp.clear();
}

void Pro:: popFrontExp() {
    this->listForExp.pop_front();
}
void Pro:: setListForExp(list<string> l) {
    listForExp = l;
}

list<string> Pro:: getListForExp(){
    return listForExp;
}

void Pro::setValueInSimulator(string vn, string directory, double value) {
    int IntegerValue = (int) value;
    directory = removeApostrophes(directory);
    string s = "set " + directory + " " + to_string(IntegerValue) + '\n';
    setBuffer(s, s.length());
    string line = "connect " + this->getIP() + " " + this->getPort();
    ConnectServerCommand csc = ConnectServerCommand(line, "connect", this);
    this->currName = vn;
    csc.doCommand();
    setVar(vn, currVal);
    }

void Pro::setIP(string s) {
    this->ip = s;
}

void Pro::setPort(string s) {
    this->port = s;
}

string Pro::getPort() {
    return this->port;
}

string Pro::getIP() {
    return this->ip;
}

string Pro::getCurrName() {
    return this->currName;
}