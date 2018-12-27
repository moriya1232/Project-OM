//
// Created by moriya on 13/12/18.
//
#include <mutex>
#include "Pro.h"
#include <string>
#include "ConnectServerCommand.h"
using namespace std;

Pro:: Pro(unordered_map<string,double>* map) {
    this->symbolTable = map;
    setSymbolTable();
    this->buffer = "";
    unordered_map<string,list<string>> bindMap;
    this->bindMap = bindMap;
    list<double> tempList;
    list<list<double>> tempList2;
    this->leftovers = tempList2;
    this->values = tempList;
    setLines();
    this->currVal = 0;
    this->halfNum = "";
    this->current = "";
    this->left = "";
    this->hasEnd = false;
    Collector* c = new (nothrow) Collector();
    this->collector = c;
    Collector* c2 = new (nothrow) Collector();
    this->collectorCommands = c2;
    this->needToUpdate = 0;
    changed = false;
    directoryOfChanged = "";
    this->protectData = false;
    this->protectedName = "";
    this->protectedDirectory = "";
    this->updateList = false;
    need1 = "";
    need2 = 0;
    this->updateCommandIsRunning = false;
}

void Pro::createCollector(){
    Collector* c = new (nothrow) Collector();
    this->collector = c;
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

bool Pro::getRun() {
    return this->updateCommandIsRunning;
}

void Pro::setRun(bool b) {
    this->updateCommandIsRunning = b;
}

void Pro::setNeed1(string s) {
    this->need1 = s;
}

string Pro::getNeed1() {
    return this->need1;
}

void Pro::setNeed2(double d) {
    this->need2 = d;
}

double Pro::getNeed2() {
    return this->need2;
}

bool Pro::getProtectedData() {
    return this->protectData;
}

void Pro::setProtectedData(bool b) {
    this->protectData = b;
}

void Pro::setChanged(bool b) {
    this->changed = b;
}

void Pro::setDirectoryOfChanged(string s) {
    this->directoryOfChanged = s;
}

int Pro::getIndx(string s) {
    int count = 0;
    for (list<string>::iterator it = lines.begin(); it != lines.end(); it++) {
        if (*it == s) {
            return count;
        }
        count ++;
    }
    // meaning there is no match
    return -1;
}

void Pro::setTempValues(list<double> lis) {
    this->tempValues = lis;
}

Pro::~Pro() {
    delete(symbolTable);
    delete this->collector;
    delete this->collectorCommands;
}

void Pro::setLeft(char* buffer, int indx, int n) {
    for (int i = indx; i < n; i++) {
        this->left += buffer[i];
    }
}

bool Pro::getEnd() {
    return this->hasEnd;
}

list<double> Pro::getTempValues() {
    return this->tempValues;
}

list<double> Pro::makeList() {
    list<double> values;
    if(this->ip == "" || this->port == "") {
        return values;
    }
    // first put all the values in a list
    string currNum = "";
    double currVal = 0;
    int i = 0;
    string s = current;
    char c = s[i];
    while (i < s.length()) {
        currNum = "";
        while (c != ',' && i < s.length()) {
            currNum += c;
            c = s[++i];
        }
        currVal = stod(currNum);
        values.push_back(currVal);
        if (i >= s.length()) {
            break;
        }
        if (i < s.length() - 1) {
            c = s[++i];
        }
        else {
            break;
        }
    }
    return values;
}

void Pro::updateValues() {
    unordered_map<string, double> tempMap = *symbolTable;
    bool changeValue = false;
    cout << "this buffer is: " <<this->current << endl;
    if(this->ip == "" || this->port == "") {
        return;
    }
    // first put all the values in a list
    list<double> values;
    string currNum = "";
    double currVal = 0;
    int i = 0;
    string s = current;
    char c = s[i];
    while (i < s.length()) {
        currNum = "";
        while (c != ',' && i < s.length()) {
            currNum += c;
            c = s[++i];
        }
        currVal = stod(currNum);
        values.push_back(currVal);
        if (i >= s.length()) {
            break;
        }
        if (i < s.length() - 1) {
            c = s[++i];
        }
        else {
            break;
        }
    }
    this->tempValues = values;
    // now update the values
    list<string>::iterator it = lines.begin();
    int count = 1;
    double value = 0;
    for (list<double>::iterator itVal = values.begin(); itVal != values.end(); itVal++, it++, count++) {
        string tempString = removeApostrophes(*it);
        value = *itVal;
        if (!isVarInSymbolTable(tempString)) {
            addSymbolTable(tempString, *itVal);
        } else {
            setVarInSymbolTable(tempString, *itVal);
        }
        if (isVarBinded(tempString)) {
            list<string> bv = this->bindMap.at(tempString);
            updateBindedVars(bv, *itVal);
        }
    }
}

void Pro::updateServer() {
    if (this->port != "") {
        for (list<string>::iterator it = lines.begin(); it != lines.end(); it++) {
            double currVal = symbolTable->at(*it);
            setValueInSimulator(*it, currVal);
        }
    }
    return;
}

bool Pro::getUpdateList() {
    return this->updateList;
}



bool Pro::compareMaps(unordered_map<string, double> m, string s) {
    if (symbolTable->at(s) != m.at(s))
        return false;
    return true;
}

Collector* Pro::getCollector() {
    return this->collector;
}
Collector* Pro::getCollectorCommands() {
    return this->collectorCommands;
}

void Pro::setString (char* buffer, int n) {
    int indx = -1;
    // check whether the buffer includes \n
    for (int i = 0; i < n; i++) {
        if (buffer[i] == '\n') {
            this->hasEnd = true;
            indx = i;
        }
    }
    if (!this->hasEnd) {
        for (int i = 0; i < n; i++) {
            this->current += buffer[i];
        }
    } else {
        for (int i = 0; i < indx; i++) {
            this->current += buffer[i];
        }
        setLeft(buffer, indx +1, n);
    }
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
        double tempVal = this->symbolTable->at(vn);
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

// returns true if the lists are equal
bool Pro::compareLists(list<double> l1, list<double> l2) {
    if (l1.empty()) {
        return false;
    }
    list<double>::iterator it1 = l1.begin();
    list<double>::iterator it2 = l2.begin();
    while (it1 != l1.end() && it2 != l2.end()) {
        if (*it1 != *it2) {
            return false;
        }
    }
    return true;
}

void Pro:: setSymbolTable() {
    symbolTable->insert(make_pair("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    symbolTable->insert(make_pair("/instrumentation/altimeter/indicated-altitude-ft", 0));
    symbolTable->insert(make_pair("/instrumentation/altimeter/pressure-alt-ft", 0));
    symbolTable->insert(make_pair("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
    symbolTable->insert(make_pair("/instrumentation/attitude-indicator/indicated-roll-deg", 0));
    symbolTable->insert(make_pair("/instrumentation/attitude-indicator/internal-pitch-deg", 0));
    symbolTable->insert(make_pair("/instrumentation/attitude-indicator/internal-roll-deg", 0));
    symbolTable->insert(make_pair("/instrumentation/encoder/indicated-altitude-ft", 0));
    symbolTable->insert(make_pair("/instrumentation/encoder/pressure-alt-ft", 0));
    symbolTable->insert(make_pair("/instrumentation/gps/indicated-altitude-ft", 0));
    symbolTable->insert(make_pair("/instrumentation/gps/indicated-ground-speed-kt", 0));
    symbolTable->insert(make_pair("/instrumentation/gps/indicated-vertical-speed", 0));
    symbolTable->insert(make_pair("/instrumentation/heading-indicator/offset-deg", 0));
    symbolTable->insert(make_pair("/instrumentation/magnetic-compass/indicated-heading-deg", 0));
    symbolTable->insert(make_pair("/instrumentation/slip-skid-ball/indicated-slip-skid", 0));
    symbolTable->insert(make_pair("/instrumentation/turn-indicator/indicated-turn-rate", 0));
    symbolTable->insert(make_pair("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0));
    symbolTable->insert(make_pair("/controls/flight/aileron", 0));
    symbolTable->insert(make_pair("/controls/flight/elevator", 0));
    symbolTable->insert(make_pair("/controls/flight/rudder", 0));
    symbolTable->insert(make_pair("/controls/flight/flaps", 0));
    symbolTable->insert(make_pair("/controls/engines/current-engine/throttle", 0));
    symbolTable->insert(make_pair("/engines/engine/rpm", 0));
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
    this->lines.push_back("/instrumentation/heading-indicator/offset-deg");
    this->lines.push_back("/instrumentation/magnetic-compass/indicated-heading-deg");
    this->lines.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
    this->lines.push_back("/instrumentation/turn-indicator/indicated-turn-rate");
    this->lines.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    this->lines.push_back("/controls/flight/aileron");
    this->lines.push_back("/controls/flight/elevator");
    this->lines.push_back("/controls/flight/rudder");
    this->lines.push_back("/controls/flight/flaps");
    this->lines.push_back("/controls/engines/current-engine/throttle");
    this->lines.push_back("/engines/engine/rpm");

}

bool Pro::isExsistInSymbolTable(string vn) {
    try {
        this->symbolTable->at(vn);
        return true;
    } catch (exception e) {
        return false;
    }
}

void Pro::setCurrVal(double d) {
    this->currVal = d;
}

void Pro::setProtectedDirectory(string s) {
    this->protectedDirectory = s;
}

void Pro::setProtectedName(string s) {
    this->protectedName = s;
}

void Pro::updateBindedVars(list<string> bv, double val) {
    list<string> bv2;
    double currVal;
    int count = 0;
    for (list<string>::iterator it = bv.begin(); it != bv.end() && count < bv.size(); it++, count++) {
        string currName = *it;
        // if this name is actual a directory
        if (currName[0] == '/') {
            if (isVarInSymbolTable(currName) && symbolTable->at(currName) == val) {
                continue;
            }
            setVarInSymbolTable(currName, val);
            // if the values are equal, continue
            setValueInSimulator(currName, val);
            bv2 = this->bindMap.at(currName);
            //updateBindedVars(bv2, val);
        }
        // if this name is a real name, meaning not a directory
        if (isVarInSymbolTable(currName)) {
            currVal = symbolTable->at(currName);
            // if the value is already updated
            if (currVal == val) {
                continue;
            } else {
                setVarInSymbolTable(currName, val);
                bv2 = this->bindMap.at(currName);
                //updateBindedVars(bv2, val);
            }
        }
        }
    }

bool Pro::hasDirectory(string vn) {
    try {
        this->namesAndDirectory.at(vn);
        return true;
    } catch  (exception e) {
        return false;
    }
}

int Pro::setVar(string vn, double newValue) {
    int prev = symbolTable->at(vn);
    // if this var has a directory, update it
    if (hasDirectory(vn)) {
        string directory = namesAndDirectory.at(vn);
        setVarInSymbolTable(vn, newValue);
        setValueInSimulator(directory, newValue);
        this->needToUpdate = newValue;
        this->directoryToUpdate = directory;
        // if someone is binded to var, update him aswell
        if (isVarBinded(vn)) {
            list<string> bv = this->bindMap.at(vn);
            this->updateCommandIsRunning = false;
            updateBindedVars(bv, newValue);
        }
        // meaning this var has no directory
    } else if (vn[0] == '/') {
        setVarInSymbolTable(vn, newValue);
        this->protectedDirectory = vn;
        setValueInSimulator(vn, newValue);
        // if someone is binded to var, update him aswell
        if (isVarBinded(vn)) {
            list<string> bv = this->bindMap.at(vn);
            this->updateCommandIsRunning = false;
            updateBindedVars(bv, newValue);
        }
    } else {
        setVarInSymbolTable(vn, newValue);
        // if someone is binded to var, update him aswell
        if (isVarBinded(vn)) {
            list<string> bv = this->bindMap.at(vn);
            this->updateCommandIsRunning = false;
            updateBindedVars(bv, newValue);
        }
    }
    this->updateCommandIsRunning = false;
    if (prev != newValue) {
        return 0;
    }
    return -1;
}

bool Pro::hasBindedVars(string vn) {
    try {
        this->bindMap.at(vn);
        return true;
    } catch (exception e) {
        return false;
    }
}

void Pro:: setVarBind(string var1, string var2) {
    if (hasBindedVars(var1)) {
        this->bindMap.at(var1).push_back(var2);
    } else {
        list<string> names;
        names.push_back(var2);
        this->bindMap.insert(make_pair(var1, names));
    }
    if (hasBindedVars(var2)) {
        this->bindMap.at(var2).push_back(var1);
    } else {
        list<string> names;
        names.push_back(var1);
        this->bindMap.insert(make_pair(var2, names));
    }
}

unordered_map<string,double>* Pro::getSymbolTable() {
    return this->symbolTable;
}

double Pro::getValueFromSimulator(string directory) {
    directory = removeApostrophes(directory);
    string s = "get " + directory + '\n';
    this->setBuffer(s, s.length());
    string line = "connect " + this->getIP() + " " + this->getPort();
    ConnectServerCommand csc = ConnectServerCommand(line, "connect", this);
    csc.doCommand();
    return currVal;
}

bool checkSixDigitsAfterDot (string s) {
    int i =0;
    for(char c=s[i];c!='.' && i < s.length();) {
        c= s[++i];
    }
    if (s.length()-i +1 == 6) {
        return true;
    }
    return false;
}

list<list<double>> Pro::setSecondList(char* buffer) {
    list<list<double>> result;
    list<double> temp;
    string s = "";
    bool quitAll = false;
    int i = 0, start = 0;
    char c = buffer[i];
    // find the first \n
    while (c != '\n') {
        c = buffer[++i];
    }
    // now c = \n
    c = buffer[++i];
    while (i < 256) {
        start = i;
        while (c != '\n' && i < 256) {
            while (c != ',' && c != '\n' && i < 256) {
                s += c;
                c = buffer[++i];
            }
            if (!checkSixDigitsAfterDot(s)) {
                temp = setLeftovers(buffer, start);
                quitAll = true;
            }
            if (quitAll) {
                break;
            }
            double d = stod(s);
            temp.push_back(d);
            c = buffer[++i];
            if (c != '\n' && i < 256) {
                c = buffer[++i];
                s = "";
            } else {
                break;
            }
        }
        if (quitAll) {
            break;
        }
        if (c == '\n') {
            result.push_back(temp);
            temp.clear();
            s = "";
        } else if (i == 256) {
            temp = setLeftovers(buffer, start);
            result.push_back(temp);
        }
        if (i < 256) {
            break;
        }
    }
    return result;
}

list<double> Pro::setLeftovers(char* buffer,int start) {
    list<double> result;
    string s = "", lastNum = "";
    bool run = true;
    int i = 0;
    char c = buffer[i];
    while (i < start) {
        c = buffer[++i];
    }
    // after we have reached to the \n
    c = buffer[++i];
    while (i < 256) {
        while (c != ',' && i < 256) {
            s += c;
            c = buffer[++i];
        }
        if (s.length() >= 8) {
            double d = stod(s);
            result.push_back(d);
        }
        c = buffer[++i];
        lastNum = s;
        s = "";
    }
    if (!checkSixDigitsAfterDot(lastNum)){
        for (int j = 0; j < lastNum.length(); j++) {
            if (lastNum[j] - '0' >= 0 && lastNum[j] - '0' < 10 || lastNum[j] == '.' || lastNum[j] == '\n') {
                this->halfNum += lastNum[j];
            }
        }
    } else {
        double d = stod(lastNum);
        result.push_back(d);
        this->halfNum = "";
    }
    return result;
}

list<double> Pro::setFirstList(char* buffer) {
    list<double> result;
    bool quit = false;
    int count = 0;
    string s = "";
    int i = 0;
    cout << this->halfNum << endl;
    char c = buffer[i];
    if (this->halfNum[0] == '.')
        this->halfNum ='0'+ this->halfNum;
    if (this->halfNum != "") {
        while (c != ',' && c != '\n') {
            if (c - '0'>= 0 && c - '0' <10 || c == '.' || c == '\n') {
                this->halfNum += c;
                c = buffer[++i];
            }
        }
        double d = stod(this->halfNum);
        result.push_back(d);
        this->halfNum = "";
        c = buffer[++i];
    }
    while (c != '\n') {
        while (c != ',' && i < 255) {
            s += c;
            c = buffer[++i];
            if (c == '\n') {
                quit = true;
                break;
            }
        }
        double d = stod(s);
        result.push_back((d));
        c = buffer[++i];
        s = "";
        if (quit) {
            break;
        }
    }
    return result;
}

void Pro::addLeftToString() {
    // reset current
    this->current = "";
    // add the leftovers
    for (int i = 0; i < this->left.length(); i++) {
        this->current += this->left[i];
    }
    // set it back to false value
    this->hasEnd = false;
    this->left = "";
}

bool Pro::getDoConnected() {
    return this->doConnected;
}

void Pro::setDoConnected() {
    this->doConnected = true;
}

void Pro::setLists(list<list<double>> l1, list<double> l2) {
    list<string>::iterator itDir = lines.begin();
    list<double> tempList;
    string currDir = "";
    if (!l1.empty()) {
        for (list<list<double>>::iterator it = l1.begin(); it != l1.end(); it++, itDir++) {
            currDir = *itDir;
            tempList = *it;
            for (list<double>::iterator it2 = tempList.begin(); it2 != tempList.end(); it2++) {
                double currVal = *it2;
                if (!isVarInSymbolTable(currDir)) {
                    addSymbolTable(currDir, currVal);
                } else {
                    //string currName = getNameByDirectory(currDir);
                    this->setVar(currDir, currVal);
                }
            }
        }
        l1.clear();
    }
    for (list<double>::iterator it = l2.begin(); it != l2.end(); it++, itDir++) {
        currDir = *itDir;
        double currVal = *it;
        if (!isVarInSymbolTable(currDir)) {
            addSymbolTable(currDir, currVal);
        } else {
            //string currName = getNameByDirectory(currDir);
            this->setVar(currDir, currVal);
        }
    }
}

string Pro::getBuffer() {
    return this->buffer;
}

int Pro::getBufferLength() {
    return this->size;
}

void Pro::setBuffer(string buff, int size) {
    this->size = size;
    char* ch = new (nothrow) char(sizeof(char) * size);
    this->buffer = ch;
    this->collector->addItem(ch);
    this->buffer = "";
    char result[256] = { '\0' };
    for (int i = 0; i < size; i++) {
        this->buffer += buff[i];
    }
}

void Pro::addNamesAndDirectory(string name, string directory) {
    this->namesAndDirectory.insert(make_pair(name, directory));
}

unordered_map<string, string> Pro::getNamesAndDirectories() {
    return this->namesAndDirectory;
}

void Pro::addSymbolTable(string name, double d) {

    this->symbolTable->insert(make_pair(name,d));

}

void Pro:: clearListForExp() {
   this->listForExp.clear();
}

unordered_map<string, list<string>> Pro::getBindMap() {
    return this->bindMap;
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

void Pro::setVarInSymbolTable(string name, double value) {
        if (isVarInSymbolTable(name)) {
            symbolTable->erase(name);
        }
        symbolTable->insert(make_pair(name, value));
        return;
}

void Pro::setValueInSimulator(string directory, double value) {

    directory = removeApostrophes(directory);
    double IntegerValue = value;
    directory = removeApostrophes(directory);
    string s = "set " + directory + " " + to_string(IntegerValue) + '\n';
    setBuffer(s, s.length());
    string line = "connect " + this->getIP() + " " + this->getPort();
    ConnectServerCommand *csc = new(nothrow) ConnectServerCommand(line, "connect", this);
    this->collector->addItem(csc);
    csc->doCommand();

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