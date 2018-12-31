//
// Created by moriya and omer
//
#include <mutex>
#include "Pro.h"
#include <string>
#include "ConnectServerCommand.h"
using namespace std;


/**
 * this function is a constractor
 * @param map  - the symbol table.
 */
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
    this->doConnected = false;
    this->protectedDirectory = "";
    this->updateList = false;
    this->updateCommandIsRunning = false;
}

/**
 * create the collector for all the objects
 */
void Pro::createCollector(){
    Collector* c = new (nothrow) Collector();
    this->collector = c;
}

/**
 * returns the run mode (if we have received any data from the simulator)
 * @return true of false
 */
bool Pro::getRun() {
    return this->updateCommandIsRunning;
}

/**
 * sets the fun mode to the given bool
 * @param b the given bool
 */
void Pro::setRun(bool b) {
    this->updateCommandIsRunning = b;
}

/**
 * reutrn if we have a data to protect
 * @return true or false
 */
bool Pro::getProtectedData() {
    return this->protectData;
}

/**
 * sets the protected data mode
 * @param b
 */
void Pro::setProtectedData(bool b) {
    this->protectData = b;
}

/**
 * set the changed mode
 * @param b the given mode
 */
void Pro::setChanged(bool b) {
    this->changed = b;
}

/**
 * sets the directory of the changed var
 * @param s is the directory
 */
void Pro::setDirectoryOfChanged(string s) {
    this->directoryOfChanged = s;
}

/**
 * returns the indx of a given var name
 * @param s is the var name
 * @return the index
 */
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

/**
 * sets a list of tempruary values
 * @param lis is the list
 */
void Pro::setTempValues(list<double> lis) {
    this->tempValues = lis;
}

/**
 * a distructor for pro
 */
Pro::~Pro() {
    delete this->collector;
    delete this->collectorCommands;
}

/**
 * sets the leftover data from the simulator into the current string
 * @param buffer is the leftovers
 * @param indx starting index
 * @param n end index
 */
void Pro::setLeft(char* buffer, int indx, int n) {
    for (int i = indx; i < n; i++) {
        this->left += buffer[i];
    }
}

/**
 * returns true or false for indicate the program if we saw a \n already
 * @return
 */
bool Pro::getEnd() {
    return this->hasEnd;
}

/**
 * returns the list of the temp values
 * @return
 */
list<double> Pro::getTempValues() {
    return this->tempValues;
}

/**
 * creats a list of doubles according to the tenp values list
 * @return
 */
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

/**
 * this functio updates the symbol table according to the given data
 * from the simulator
 */
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
        if (ifVarBinded(tempString)) {
            list<string> bv = this->bindMap.at(tempString);
            updateBindedVars(bv, *itVal);
        }
    }
}

/**
 * updates the simulator values
 */
void Pro::updateServer() {
    if (this->port != "") {
        for (list<string>::iterator it = lines.begin(); it != lines.end(); it++) {
            double currVal = symbolTable->at(*it);
            setValueInSimulator(*it, currVal);
        }
    }
    return;
}

/**
 * no in use.
 * @return
 */
bool Pro::getUpdateList() {
    return this->updateList;
}


/**
 * this function compares the values (first and second) of two given maps
 * @param m is the first map
 * @param s is the sceond
 * @return true or false
 */
bool Pro::compareMaps(unordered_map<string, double> m, string s) {
    if (symbolTable->at(s) != m.at(s))
        return false;
    return true;
}

/**
 * returns the collector which is responsible of releasing allocated memory
 * @return the collector
 */
Collector* Pro::getCollector() {
    return this->collector;
}
/**
 * retunrs the collector which is responsible of releasing allocated memory
 * in loops
 * @return the collector
 */
Collector* Pro::getCollectorCommands() {
    return this->collectorCommands;
}

/**
 * sets the given data in pro
 * @param buffer if the given daya
 * @param n the data's length
 */
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

/**
 * return true if the given var is in the symbol table, otherwise false
 * @param vn is the given var
 * @return true or false
 */
bool Pro::isVarInSymbolTable(string vn) {
    try {
        double tempVal = this->symbolTable->at(vn);
        return true;
    } catch (exception e) {
        return false;
    }
}

/**
 * returns the name by a given directory
 * @param direct the directory
 * @return the name
 */
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

/**
 * receives two lists of double and return true if they equal, otherwise false
 * @param l1
 * @param l2
 * @return
 */
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

/**
 * sets the pathes if the xml in the symbol table
 */
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
    symbolTable->insert(make_pair("/instrumentation/heading-indicator/indicated-heading-deg", 0));
    symbolTable->insert(make_pair("/instrumentation/magnetic-compass/offset-deg", 0));
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

/**
 * sets the pathes of the xml in the lines list
 */
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
    this->lines.push_back("/instrumentation/magnetic-compass/offset-deg");
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

/**
 * return true is the given var is in the symbol table
 * @param vn is the given var
 * @return true or false
 */
bool Pro::isExsistInSymbolTable(string vn) {
    try {
        this->symbolTable->at(vn);
        return true;
    } catch (exception e) {
        return false;
    }
}

/**
 * sets the curr val
 * @param d the new curr val
 */
void Pro::setCurrVal(double d) {
    this->currVal = d;
}

/**
 * sets the protected directory
 * @param s the protected directory
 */
void Pro::setProtectedDirectory(string s) {
    this->protectedDirectory = s;
}

/**
 * sets the protected name
 * @param s the protected name
 */
void Pro::setProtectedName(string s) {
    this->protectedName = s;
}

/**
 * updates the list by the given value
 * @param bv the list
 * @param val the given value
 */
void Pro::updateBindedVars(list<string> bv, double val) {
    for (list<string>::iterator it = bv.begin(); it != bv.end(); it++) {
        string currName = *it;
        setVarInSymbolTable(currName, val);
        if(currName[0]=='/') {
            setValueInSimulator(currName, val);
        }
    }
}

/**
 * returns true if the given var has a directory
 * @param vn the given ar
 * @return true of false
 */
bool Pro::hasDirectory(string vn) {
    try {
        this->namesAndDirectory.at(vn);
        return true;
    } catch  (exception e) {
        return false;
    }
}

/**
 * this function sets a var, by a given name and value
 * @param vn the name
 * @param newValue the value
 * @return int
 */
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
        if (ifVarBinded(vn)) {
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
        if (ifVarBinded(vn)) {
            list<string> bv = this->bindMap.at(vn);
            this->updateCommandIsRunning = false;
            updateBindedVars(bv, newValue);
        }
    } else {
        setVarInSymbolTable(vn, newValue);
        // if someone is binded to var, update him aswell
        if (ifVarBinded(vn)) {
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

/**
 * this function returns true if the given var is binded, false otherwise
 * @param var the given var
 * @return true or false
 */
bool Pro::ifVarBinded(string var) {
    try {
        list<string> lis = bindMap.at(var);
        return true;
    } catch (exception) {
        return false;
    }
}

/**
 * sets two vars and make them binded to each other
 * @param main the first var
 * @param secondary the second var
 */
void Pro:: setVarBind(string main, string secondary) {
    // if the first var is already binded
        if (ifVarBinded(main)) {
            for (list<string>:: iterator it = bindMap.at(main).begin();it != bindMap.at(secondary).end(); it++ ) {
                string curr = *it;
                try {
                    bindMap.at(curr).remove(secondary);
                } catch (exception e) {

                }
                bindMap.at(curr).push_back(secondary);
            }
            bindMap.at(main).push_back(secondary);
        } else {
            list<string> tempList;
            tempList.push_back(secondary);
            bindMap.insert(make_pair(main, tempList));
        }
        if (ifVarBinded(secondary)) {
            for (list<string>:: iterator it = bindMap.at(secondary).begin();it != bindMap.at(secondary).end(); it++ ) {
                string curr = *it;
                try {
                    bindMap.at(curr).remove(main);
                } catch (exception e) {

                }
                bindMap.at(curr).push_back(main);
            }
            bindMap.at(main).push_back(main);
        } else {
            list<string> tempList;
            tempList.push_back(main);
            bindMap.insert(make_pair(secondary, tempList));
  }
}

unordered_map<string,double>* Pro::getSymbolTable() {
    return this->symbolTable;
}

/**
 * a getter from the simulator
 * @param directory the directory we want to know its value
 * @return the value
 */
double Pro::getValueFromSimulator(string directory) {
    directory = removeApostrophes(directory);
    string s = "get " + directory + '\n';
    this->setBuffer(s, s.length());
    string line = "connect " + this->getIP() + " " + this->getPort();
    ConnectServerCommand csc = ConnectServerCommand(line, "connect", this);
    csc.doCommand();
    return currVal;
}

/**
 * returns true if the given sring includes a double
 * @param s the given string
 * @return true or false
 */
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

/**
 * sets the second lsit
 * @param buffer the data
 * @return the list
 */
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

/**
 * sets to the current string (which includes the data) the leftover data
 * after the update
 * @param buffer the leftover data
 * @param start the starting index
 * @return the list of the values
 */
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

/**
 * sets the first list
 * @param buffer the data
 * @return the list
 */
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

/**
 * add the leftovers the the current string
 */
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

/**
 * return the connected mode (connected or no)
 * @return true or false
 */
bool Pro::getDoConnected() {
    return this->doConnected;
}

/**
 * sets the connected mode
 */
void Pro::setDoConnected() {
    this->doConnected = true;
}

/**
 * sets the lists
 * @param l1 the first list
 * @param l2 the second list
 */
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

/**
 * returns this buffer
 * @return the buffer
 */
string Pro::getBuffer() {
    return this->buffer;
}

/**
 * returns the size of this buffer
 * @return the size
 */
int Pro::getBufferLength() {
    return this->size;
}

/**
 * sets this buffer by a given buffer
 * @param buff the given buffer
 * @param size
 */
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

/**
 * add a name and its directory to our map
 * @param name the name
 * @param directory the directory of the given name
 */
void Pro::addNamesAndDirectory(string name, string directory) {
    this->namesAndDirectory.insert(make_pair(name, directory));
}

/**
 * returns the map of the names and the directories
 * @return the map
 */
unordered_map<string, string> Pro::getNamesAndDirectories() {
    return this->namesAndDirectory;
}

/**
 * add the given var to the symbol table map
 * @param name the name of the var
 * @param d the value of the var
 */
void Pro::addSymbolTable(string name, double d) {

    this->symbolTable->insert(make_pair(name,d));

}

/**
 * clear this list
 */
void Pro:: clearListForExp() {
   this->listForExp.clear();
}

/**
 * returns the bindedMap
 * @return
 */
unordered_map<string, list<string>> Pro::getBindMap() {
    return this->bindMap;
}

/**
 * pop from the expressions values
 */
void Pro:: popFrontExp() {
    this->listForExp.pop_front();
}
/**
 * sets the list of the expression by the given list
 * @param l the given list
 */
void Pro:: setListForExp(list<string> l) {
    listForExp = l;
}

/**
 * returns the list of the expressions
 * @return the list
 */
list<string> Pro:: getListForExp(){
    return listForExp;
}

/**
 * sets a var in the symbol table by the given value
 * @param name the var we need to set
 * @param value the new value
 */
void Pro::setVarInSymbolTable(string name, double value) {
    for ( unordered_map<string,double>::iterator it = this->symbolTable->begin();
    it != this->symbolTable->end() ;it++) {
        if (it->first == name) {
            it->second = value;
        }
    }
}

/**
 * sets a directory value by the given value, in the simulator
 * @param directory the directory we need to update
 * @param value the new value
 */
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

/**
 * sets the ip by the given ip
 * @param s the given ip
 */
void Pro::setIP(string s) {
    this->ip = s;
}

/**
 * sets the port by the given port
 * @param s the given port
 */
void Pro::setPort(string s) {
    this->port = s;
}

/**
 * return the port
 * @return the port
 */
string Pro::getPort() {
    return this->port;
}

/**
 * returns the ip
 * @return the ip
 */
string Pro::getIP() {
    return this->ip;
}