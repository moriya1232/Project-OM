//
// Created by moriya on 12/12/18.
//

//
// Created by omer on 12/8/18.
//
#include "Var.h"

Var:: Var(): UnaryExpression(0){
    this->name="";
    this->value=0;
}
Var::Var(string name, double v):UnaryExpression(v) {
    this->name = name;
    this->value = v;
}

string Var::extractWordFromLine(string line) {
    string result = "";
    int i = 0;
    while (line[i] != ' ' && line[i] != '\n' && i < line.length()) {
        result += line[i];
        i++;
    }
    return result;
}

double Var::getValue() {
    return this->value;
}
string Var::getName() {
    return this->name;
}


// we need to get the currect value from the server somehow
double Var::operator=(Var& other) {
    this->value = other.getValue();
}

void Var:: setName(string name) {
    this->name = name;
}
void Var:: setValue(double d) {
    this->value = d;
}
double Var::calculate() {
    return this->getValue();
}

int doCommand() {
    /*
    string tempLine = this->getLine();
    // remove "var"
    tempLine = tempLine.substr(extractWordFromLine(tempLine).length() + 1);
    //insert the name
    this->name = extractWordFromLine(tempLine);
    tempLine = tempLine.substr(extractWordFromLine(tempLine).length() + 1);
    //remove the "= "
    tempLine = tempLine.substr(2);
    // remove "bind"
    tempLine = tempLine.substr(5);
    tempLine = removeApostrophes(tempLine);
    int soServer;
    //unsigned  long ser_add;
    //int someNumber;
    //int test = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
     */ return 0;
}