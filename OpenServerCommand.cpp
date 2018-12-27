//
// Created by omer on 12/7/18.
//

#include "OpenServerCommand.h"
using namespace std;

OpenServerCommand:: OpenServerCommand(string line, string name, Pro* p) : Command(line,name) {
    this->p = p;
}

void OpenServerCommand:: openServer(string s1, string s2, OpenServerCommand* osc) {
    int sockfd, newsockfd, portno, clilen;
    char buffer[100];
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
        bzero(buffer, 100);
        if (osc->p->getRun()) {
            continue;
        }
        n = read(newsockfd, buffer, 99);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        if (osc->p->getEnd() && osc->p->getDoConnected()) {
            osc->p->addLeftToString();
        }
        osc->p->setString(buffer, n);
        if (dataReceived(buffer, 100)) {
            osc->p->setDoConnected();
        }
        if (osc->p->getEnd() && osc->p->getDoConnected()) {
            osc->p->updateValues();
        }
    }
}

bool OpenServerCommand::dataReceived(char* buffer, int n) {
    string s = "";
    int i = 0;
    char c = buffer[i];
    while (i < n) {
        if (c - '0' == 0 || c == '.' || c == '\n' && i < n || '\0' || '\000' ) {
            c = buffer[++i];
        } else {
            return true;
        }
    }
    return false;
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
    Expression* a1 = makeExpression(s1, p);
    double d1 = a1->calculate();
    lin = lin.substr(extractWordFromLine(lin).length() + 1);
    // times per second
    string s2 = extractWordFromLine(lin);
    Expression* a2 = makeExpression(s2, p);
    double d2 = a2->calculate();
    OpenServerCommand* osc = new (nothrow) OpenServerCommand("", "", this->p);
    osc->p->getCollector()->addItem(osc);
    thread listenToServer(openServer,to_string(d1),to_string(d2), osc);
    listenToServer.detach();
    return 0;
}