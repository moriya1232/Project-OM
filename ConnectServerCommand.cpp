//
// Created by :
// omer shitrit 206333015
// and
// moriya leopold 208116483
//
//

#include "ConnectServerCommand.h"
#include <thread>
#include <mutex>

using namespace std;

/**
 * constractor for connect server
 * @param line
 * @param name
 * @param p
 */
ConnectServerCommand:: ConnectServerCommand(string line, string name, Pro* p) :Command(line,name) {
    this->p = p;
}

/**
 * copy a string to char*
 * @param arr
 * @param s
 */
void ConnectServerCommand::strcpy(char* arr, string s) {
    int i;
    for (i = 0; i < s.length(); i++) {
        arr[i] = s[i];
    }
    arr[i] = '\n';
}

/**
 * clear ip
 * @param arr
 * @param length
 */
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

/**
 * set the buffer
 * @param buffer
 */
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

/**
 * has massage in the buffer?
 * @param buffer
 * @return true ot false
 */
bool ConnectServerCommand::hasMessage(char buffer[]) {
    if (buffer[0] != '\0')
        return true;
    return false;
}

/**
 * this function help to connect the server and send values
 * @param IP
 * @param portNumber
 * @param csc
 * @param num
 */
void ConnectServerCommand:: connectServer(char* IP, string portNumber, ConnectServerCommand* csc, int num) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256] = {'\0'};
    for (int i = 0; i < 256; i++) {
        if (csc->p->getBuffer()[i] == '\n')
            break;
        else
            buffer[i] = csc->p->getBuffer()[i];
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
        csc->setBuffer(buffer);
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
        csc->p->setCurrVal(val);
    }
    close(sockfd);
}

/**
 * check if there is none in the word
 * @param buffer
 * @param n
 * @return
 */
bool ConnectServerCommand::lookForNone(char* buffer, int n) {
    string s = "";
    int i = 0;
    char c = buffer[i];
    while (c != '=' && i < n) {
        c = buffer[++i];
    }
    while (i < n) {
        c = buffer[++i];
        if (c - '0' >= 0 && c - '0' < 10) {
            return false;
        }
    }
    return true;
}

/**
 * this function check if need to update
 * @param buffer
 * @param length
 * @return true or false
 */
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

/**
 * this function parse the string of values
 * @param buffer
 * @param length
 * @return
 */
double ConnectServerCommand::parseResult(char* buffer, int length) {
    if (lookForNone(buffer,length)) {
        return 0;
    }
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
        string s;
        // get the result and return it
        while (c!='\'') {
            s+=c;
            c=buffer[++i];
        }
        try {
            result = stod(s);
        } catch (exception e) {
            try {
                result = stod(s.substr(0,6));
            } catch (exception e1){
                result=0;
            }
        }
        if (negative)
            result *= -1;
        return result;
    } else
        return 0;
}

/**
 * do the command by connect to server
 * @return 0
 */
int ConnectServerCommand:: doCommand(){
    while (!this->p->getDoConnected()) {}
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
    Expression* a = makeExpression(s2, p);
    double d = a->calculate();
    if (this->p->getIP() == "" && this->p->getPort() == ""){
        this->p->setIP(s1);
        this->p->setPort(s2);
    }
    ConnectServerCommand* csc = new (nothrow) ConnectServerCommand("", "", this->p);
    char* cc = new char[arr[n]];
    this->p->getCollectorCommands()->addItem(csc);
    this->p->getCollectorCommands()->addItem(cc);
    strcpy(cc, s1);
    connectServer(cc, to_string(d), csc, n+1);
}