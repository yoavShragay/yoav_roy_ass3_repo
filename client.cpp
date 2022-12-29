#include "client.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;
char* stringToCharArr(string s){
    char arr[s.length()+1];
    strcpy(arr,s.c_str());
    return arr;
}
void sendVector(string ip,int port){
    char ipArr[ip.length()+1];
    strcpy(ipArr,ip.c_str());
    bool flag=false;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ipArr);
    sin.sin_port = htons(port);
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }


    while (true) {
        //send
        string vectorData;
        getline(cin,vectorData);
        if(vectorData=="-1"){
            flag= true;
        }
        int data_len = vectorData.length();
        char vectorArr[vectorData.length()+1];
        strcpy(vectorArr,vectorData.c_str());
        int sent_bytes = send(sock, vectorArr, data_len, 0);
        if (sent_bytes < 0) {
            // error
        }
        if(flag){
            break;
        }

        //recive
        char buffer[4096]="\0";
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            // connection is closed
        } else if (read_bytes < 0) {
            // error
        } else {
            cout << buffer;
        }
    }
    close(sock);
    return ;
}

int main(int argc, char *argv[]) {
    //TODO - check if valid ip and port
    const string ip = "127.0.0.1";
    const int port_no = 12348;
    sendVector(ip,port_no);
    return 0;
}
