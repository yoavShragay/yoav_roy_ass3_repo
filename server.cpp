#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;
void acceptVector(int port, string file){
    bool flag=false;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }
while(true) {

    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
    }
    while(true) {
        char buffer[4096]="\0";
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);

        if (read_bytes == 0) {
            //TODO - find out waht to do here
            // connection is closed
        } else if (read_bytes < 0) {
            //TODO - find out waht to do here
            // error
        } else {
            if (strcmp(buffer , "-1")==0) {
                break;
            }
            cout << buffer;
        }
        int sent_bytes = send(client_sock, buffer, read_bytes, 0);
        if (sent_bytes < 0) {
            perror("error sending to client");
        }
    }
}
    return ;
}
int main(int argc, char *argv[]) {
    const string file_name = argv[1];
    //TODO - check if leagel number
    const int server_port = stoi(argv[2]);
    acceptVector(server_port,file_name);
    return 0;
}
