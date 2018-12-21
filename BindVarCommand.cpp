//
// Created by omer on 12/15/18.
//

#include "BindVarCommand.h"
#include "ConnectServerCommand.h"
#include "UsefulFunctions.h"

BindVarCommand::BindVarCommand(Pro* p, string line, string name) : Command(line, name){
    this->p =p;
    this->line =line;
    this->name = name;
}


BindVarCommand::BindVarCommand(Pro* p) : Command("", "bind"){
    this->p = p;
}

int BindVarCommand::doCommand() {
    string s = this->line;
    s = s.substr(extractWordFromLine(s).length() + 1);
    string varName = extractWordFromLine(s);
    s = s.substr(varName.length());
    // now look for its directory
    int i = 0;
    char c = s[i];
    string temp = "";
    while (c != '"') {
        temp += c;
        c = s[++i];
    }
    s = s.substr(temp.length());
    double d1 = this->getValueFromSimulator(varName);
    double d2 = this->getValue(varName);
    double d3 = this->p->getSymbolTable().at(varName);
    if (d1 != d3) {
        this->p->setVar(varName, d1);
    } else if (d2 != d3) {
        this->setValueInSimulator(varName, d2);
    }
}

double BindVarCommand::getValue(string varName) {
    //check if the var name exsist in out map
    try {
        double value = this->p->getSymbolTable().at(varName);
        return value;
    } catch (exception e) {
        cout << "Var name does not exsis." << endl;
        // -999 is the default error value
        return -999;
    }
}

void BindVarCommand::setValue(string varName, double d) {
    this->p->setVar(varName, d);
}

/*string BindVarCommand::alreadyBinded(string name) {
    try {
        string s = this->p->getBindMap().at(name);
        return s;
    } catch(exception e){
    }
    return "";
}*/

string BindVarCommand::getLine(string vn) {
    // if the given var is already binded
   /* string s = alreadyBinded(vn);
    if (s != "") {
        return s;
    }
    s = "/controls/flight/";
    if (vn == "aileron" || vn == "elevator" || vn == "rudder" || vn == "flaps") {
        s = s + vn;
        return s;
    } else {
        if (vn == "airspeed") {
            return "/instrumentation/airspeed-indicator/indicated-speed-kt";
        }
        if (vn == "alt" || vn == "altitude") {
            return "/instrumentation/altimeter/indicated-altitude-ft";
        }
        if (vn == "pitch" || vn == "roll") {
            return "/instrumentation/attitude-indicator/indicated-" + vn + "-deg";
        }
        if (vn == "encoder") {
            return "instrumentation/encoder/pressure-alt-ft";
        }
        if (vn == "heading") {
            return "/instrumentation/heading-indicator/indicated-heading-deg";
        }
        if (vn == "magnetic") {
            return "/instrumentation/magnetic-compass/indicated-heading-deg";
        }
        if (vn == "slip") {
            return "/instrumentation/slip-skid-ball/indicated-slip-skid";
        }
        if (vn == "turn") {
            return "/instrumentation/turn-indicator/indicated-turn-rate";
        }
        if (vn == "vertical") {
            return "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
        }
        if (vn == "engine") {
            return "/engines/engine/rpm";
        }
        return "";
    }*/
   return this->p->getNamesAndDirectories().at(vn);
}

void BindVarCommand::setValueInSimulator(string vn, double value) {
    string s = "set " + this->getLine(vn) + " " + to_string(value);
    this->p->setBuffer(s, s.length());
}


double BindVarCommand::getValueFromSimulator(string vn) {
    string s = "get" + this->getLine(vn);
    this->p->setBuffer(s, s.length());
    double val = this->p->getSymbolTable().at(vn);
    return val;
}