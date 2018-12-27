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
#include "Collector.h"
class Pro {
    Collector* collector;
    Collector* collectorCommands;
    unordered_map <string,double>* symbolTable;
    string current;
    string left;
    bool doConnected;
    string buffer;
    int size;
    unordered_map<string, list<string>> bindMap;
    bool hasEnd;
    list<string> lines;
    unordered_map<string,string> namesAndDirectory;
    void setLines();
    list<double> values;
    string halfNum;
    string directoryToUpdate;
    double needToUpdate;
    list<list<double>> leftovers;
    bool changed;
    string directoryOfChanged;
    string ip;
    string port;
    bool protectData;
    bool hasDirectory(string);
    bool hasBindedVars(string);
    bool updateCommandIsRunning;
    bool compareLists(list<double>, list<double>);
    bool updateList;
    double currVal;
    list<string> listForExp;
    list<double> tempValues;
    string need1;
    double need2;
    unordered_map<string, double> temp;
    int getIndx(string);
    bool compareMaps(unordered_map<string, double>, string);
public:
    mutex g_i_symbolTable;
    list<double> setValueInTempValue(list<double>, string directory, double newValue);
    void setTempValues(list<double>);
    bool comapteLists(list<double> lis);
    void setString(char*, int);
    bool getUpdateList();
    void setUpdateList(bool);
    void updateBindedVars(list<string>, double);
    void setLeft(char*, int, int);
    void setNeed1(string);
    void setNeed2(double);
    string getNeed1();
    double getNeed2();
    string protectedName;
    bool getRun();
    void setRun(bool);
    string protectedDirectory;
    void setChanged(bool);
    bool getProtectedData();
    void setProtectedName(string);
    void setProtectedDirectory(string);
    void setProtectedData(bool);
    void updateServer();
    void setDirectoryOfChanged(string);
    bool getDoConnected();
    void setDoConnected();
    bool getEnd();
    list<double> getLeftovers();
    void setLeftovers(list<double>);
    Pro(unordered_map<string, double>*);
    void addSymbolTable(string, double);
    void updateValues();
    list<double> makeList();
    list<double> getTempValues();
    void setVarInSymbolTable(string, double);
    void setSymbolTable();
    void addLeftToString();
    Collector* getCollector();
    Collector* getCollectorCommands();
    list<double> getValues(char*);
    bool isVarInSymbolTable(string vn);
    int setVar(string var, double newValue);
    void setVarBind(string var1, string var2 );
    unordered_map<string,double>* getSymbolTable();
    string getBuffer();
    int getBufferLength();
    void setBuffer(string, int);
    list<double> setFirstList(char[]);
    list<list<double>> setSecondList(char[]);
    list<double> setLeftovers(char* buffer,int start);
    void setLists(list<list<double>>, list<double>);
    bool isVarBinded(string);
    void addNamesAndDirectory(string, string);
    unordered_map<string, string> getNamesAndDirectories();
    string getNameByDirectory(string);
    bool isExsistInSymbolTable(string);
    double getValueFromSimulator(string);
    void setValueInSimulator(string, double);
    void setIP(string);
    void setPort(string);
    unordered_map<string,list<string>> getBindMap();
    string getIP();
    string getPort();
    void clearListForExp();
    void popFrontExp();
    void setListForExp(list<string> l);
    list<string> getListForExp();
    void setCurrVal(double);
    void createCollector();
    ~Pro();
};

#endif //UNTITLED5_PRO_H