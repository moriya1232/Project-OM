//
// Created by omer on 12/8/18.
//

#include "ConnectServerCommand.h"
#include <thread>

using namespace std;


ConnectServerCommand:: ConnectServerCommand(string line, string name, Pro* p) :Command(line,name) {
    this->p = p;
}

void ConnectServerCommand::strcpy(char* arr, string s) {
    int i;
    for (i = 0; i < s.length(); i++) {
        arr[i] = s[i];
    }
    arr[i] = '\n';
}

void ConnectServerCommand::clearIP(char* arr, int length) {
    int i = 0;
    char c = arr[i];
    while (c != '\n') {
        c = arr[++i];
    }
    while (i < length) {
        arr[i] = '\0';
        i++;
    }
}

string ConnectServerCommand:: extractWordFromLine(string line) {
    string result = "";
    int i = 0;
    while (line[i] != ' ' && line[i] != '\n' && i < line.length()) {
        result += line[i];
        i++;
    }
    return result;
}

string ConnectServerCommand::getName(char buffer[]) {
    string currWord = "";
    unordered_map<string, double> map = this->p->getSymbolTable();
    bool run = true;
    int i = 0;
    while (run) {
        currWord = "";
        char c = buffer[i];
        while (c != '/' && i < this->p->getBufferLength() && c != ' ') {
            currWord += c;
            c = buffer[++i];
        }
        i++;
        for(std::unordered_map<string, double>::iterator iter = map.begin(); iter != map.end(); ++iter)
        {
            string k =  iter->first;
            if (currWord == k)
                return k;
        }
    }
    return  "";
}

void ConnectServerCommand::setBuffer(char* buffer) {
    int i = 0;
    string origin = this->p->getBuffer();
    for (; i < 256; i++) {
        if (origin[i] != '\0')
            buffer[i] = origin[i];
        else
            break;
    }
}

bool ConnectServerCommand::hasMessage(char buffer[]) {
    if (buffer[0] != '\0')
        return true;
    return false;
}

void ConnectServerCommand:: connectServer(char* IP, string portNumber, ConnectServerCommand csc, int num) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256] = {'\0'};
    for (int i = 0; i < 256; i++) {
        if (csc.p->getBuffer()[i] == '\n')
            break;
        else
            buffer[i] = csc.p->getBuffer()[i];
    }
    portno = stoi(portNumber);

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    clearIP(IP, num);
    server = gethostbyname(IP);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
    if (hasMessage(buffer)) {
        // now set the buffer
        csc.setBuffer(buffer);
        int len = 0;
        while (true) {
            if (buffer[len] == '\0')
                break;
            len++;
        }
        // add \r\n to the message
        int i = 0;
        bool run = true;
        while (run) {
            if (buffer[i] == '\0') {
                buffer[i] = '\r';
                buffer[i + 1] = '\n';
                run = false;
            }
            i++;
        }
        /* Send message to the server */
        n = write(sockfd, buffer, strlen(buffer));
        int numofbits = send(sockfd, buffer, len, 0);
        if (numofbits == -1)
            perror("something went wrong while creating the message.\n");
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
        /* Now read server response */
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        // now buffer has the answer from the sever
        double val = parseResult(buffer, n);
        csc.p->setCurrVal(val);
    }
}

bool ConnectServerCommand::ifShouldUpdate(char c) {
    if (c == 'g') {
        return true;
    }
    return false;
}

void ConnectServerCommand::setValue(string vn, double value) {
    this->p->setVar(vn, value);
}

bool ConnectServerCommand::haveToUpdate(char* buffer, int length) {
    int i = 0;
    char c = buffer[i];
    while (i < length) {
        if (c == '=') {
            return true;
        }
        c = buffer[++i];
    }
    return false;
}

double ConnectServerCommand::parseResult(char* buffer, int length) {
    // check we have to update some Var
    if (haveToUpdate(buffer, length)) {
        double result = 0;
        bool run = true, negative = false;
        int i = 0;
        char c = buffer[i];
        while (run) {
            c = buffer[++i];
            if (i < length && c == '=') {
                // reach to the beginning of the result
                i += 3;
                c = buffer[i];
                // stop the loop
                run = false;
            }
        }
        run = true;
        if (c == '-') {
            negative = true;
            c = buffer[++i];
        }
        // get the result and return it
        while (run) {
            result *= 10;
            result += c - '0';
            c = buffer[++i];
            if (i < length && c == '\'') {
                run = false;
            }
        }
        if (negative)
            result *= -1;
        return result;
    } else
        return 0;
}

char* ConnectServerCommand:: parseIP(string IP) {
    char* result = new (nothrow) char(IP.length());
    int count = 0;
    int len = IP.length();
    while (count < IP.length()) {
        result[count] = IP[count];
        count++;
    }
    return result;
}

int ConnectServerCommand:: doCommand(){
    string tempLine = this->getLine();
    tempLine = tempLine.substr(extractWordFromLine(tempLine).length() + 1);
    // ip address
    string s1 = extractWordFromLine(tempLine);
    int n = s1.length();
    char arr[n+1];
    strcpy(arr,s1);
    tempLine = tempLine.substr(extractWordFromLine(tempLine).length() + 1);
    // port number
    string s2 = extractWordFromLine(tempLine);
    if (this->p->getIP() == "" && this->p->getPort() == ""){
        this->p->setIP(s1);
        this->p->setPort(s2);
    }
    ConnectServerCommand csc = ConnectServerCommand("", "", this->p);
    char* cc = new char(arr[n]);
    strcpy(cc, s1);
    connectServer(cc, s2, csc, n+1);
}