//
// Created by omer on 12/7/18.
//

#include "OpenServerCommand.h"
using namespace std;


OpenServerCommand:: OpenServerCommand(string line, string name, Pro* p) : Command(line,name) {
    this->p = p;
}

string OpenServerCommand:: extractWordFromLine(string line) {
    string result = "";
    int i = 0;
    while (line[i] != ' ' && line[i] != '\n' && i < line.length()) {
        result += line[i];
        i++;
    }
    return result;
}

void OpenServerCommand:: error (char* msg) {
    perror(msg);
    exit(1);
}

int OpenServerCommand:: getLengthOfBuffer(char* buffer) {
    return sizeof(buffer)/sizeof(char);
}

void OpenServerCommand:: openServer(string s1, string s2, OpenServerCommand osc) {
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int  n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = stod(s1);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    while (true) {
        /* If connection is established then start communicating */
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        list<double> values = osc.p->getValues(buffer);
        // set values updates all the values, implements the binding idea
        osc.p->setValues(values);
    }
}

static bool checkBuffer(char c1, char c2, char c3) {
    if (c1 == 'e' && c2 == 'n' && c3 == 'd')
        return true;
    return false;
}

int OpenServerCommand:: doCommand() {
    string lin = this->getLine().substr(extractWordFromLine(this->getLine()).length() + 1);
    // port number
    string s1 = extractWordFromLine(lin);
    lin = lin.substr(extractWordFromLine(lin).length() + 1);
    // times per second
    string s2 = extractWordFromLine(lin);
    OpenServerCommand osc = OpenServerCommand("", "", this->p);
    thread listenToServer(openServer,s1,s2, osc);
    listenToServer.detach();
    return 0;
}