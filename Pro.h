//
// Created by moriya on 13/12/18.
//

#ifndef UNTITLED5_PRO_H
#define UNTITLED5_PRO_H
using namespace std;
#include <string>
#include "unordered_map"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <list>
#include <mutex>
class Pro {
    unordered_map <string,double> symbolTable;
    string buffer;
    int size;
    unordered_map<string, list<string>> bindMap;
    list<double> values;
    list<string> lines;
    unordered_map<string,string> namesAndDirectory;
    void setLines();
    string ip;
    string port;
    string currName;
    double currVal;
    list<string> listForExp;
    bool isExsistInSymbolTable(string);
public:
    string getCurrName();
    Pro();
    void addSymbolTable(string name, double d);
    unordered_map<string,double> setSymbolTable();
    bool isVarInSymbolTable(string vn);
    void setVar(string var, double newValue);
    void setVarBind(string var1, string var2 );
    unordered_map<string,double> getSymbolTable();
    string getBuffer();
    int getBufferLength();
    void setBuffer(string, int);
    unordered_map<string,list<string>> getBindMap();
    //void addBind(string, string);
    list<double> getValues(char[]);
    void setValues(list<double>);
    //void updateValues();
    bool isVarBinded(string);
    void addNamesAndDirectory(string, string);
    void setVarNamesAndDirectory(string, string);
    unordered_map<string, string> getNamesAndDirectories();
    string getNameByDirectory(string);
    double getValueFromSimulator(string, string);
    void setValueInSimulator(string, string, double);
    void setIP(string);
    void setPort(string);
    string getIP();
    string getPort();
    void clearListForExp();
    void popFrontExp();
    void setListForExp(list<string> l);
    list<string> getListForExp();
    void setCurrVal(double);
};

#endif //UNTITLED5_PRO_H