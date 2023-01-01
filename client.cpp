#include "client.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

#define DELIM "."

/**
 * Check if every part of the ip (separated by a dot) is valid (e.g. 192.68.24.1)
 * @param partIp - a part of the full ip number
 * @return true of its a valid number, and false otherwise.
 */
bool check_valid_part_ip(char *partIp) {
    size_t len = strlen(partIp);
    // if the length is bigger than 3,
    if (len > 3 || (len > 1 && partIp[0] == '0')) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (partIp[i] < '0' || partIp[i] > '9') {
            return false;
        }
    }
    int num = stoi(partIp);
    if (num >= 0 && num <= 255) {
        return true;
    }
    return false;
}

/**
 * Check if the given ip number is valid
 * @param ip - ip number
 * @return true of its a valid ip number, and false otherwise.
 */
bool check_valid_ip(char *ip) {
    if (ip == nullptr) {
        return false;
    }
    int count_dot = 0;
    char *ipSplit = strtok(ip, DELIM);
    if (ipSplit == nullptr) {
        return false;
    }
    while (ipSplit) {
        if (check_valid_part_ip(ipSplit)) {
            ipSplit = strtok(nullptr, DELIM);
            if (ipSplit != nullptr) {
                count_dot++;
            }
        } else {
            return false;
        }
    }
    if (count_dot != 3) {
        return false;
    }
    return true;
}

/**
 * Check if the port is a valid number
 * @param port - port number
 * @return true if this is a valid port number, false otherwise.
 */
bool check_valid_port(char *port) {
    if (port == nullptr) {
        return false;
    }
    size_t len = strlen(port);
    if (port[0] == '0') {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if (port[i] < '0' || port[i] > '9') {
            return false;
        }
    }
    int numPort = stoi(port);
    if (numPort < 1024 || numPort > 65536) {
        return false;
    }
    return true;
}


char *stringToCharArr(string s) {
    char arr[s.length() + 1];
    strcpy(arr, s.c_str());
    return arr;
}

void sendVector(string ip, int port) {
    char ipArr[ip.length() + 1];
    strcpy(ipArr, ip.c_str());
    bool flag = false;
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
        getline(cin, vectorData);
        if (vectorData == "-1") {
            flag = true;
        }
        int data_len = vectorData.length();
        char vectorArr[vectorData.length() + 1];
        strcpy(vectorArr, vectorData.c_str());
        int sent_bytes = send(sock, vectorArr, data_len, 0);
        if (sent_bytes < 0) {
            // error
        }
        if (flag) {
            break;
        }

        //receive
        char buffer[4096] = "\0";
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
    return;
}

int main(int argc, char *argv[]) {
    //TODO - check if valid ip and port
    if (!check_valid_ip(argv[1])) {
        cout << "Invalid Input";
    }
    if (!check_valid_port(argv[2])) {
        cout << "Invalid Input";
    }
    const string ip = argv[1];
    const int server_port = stoi(argv[2]);
    const int port_no = 12348;
    sendVector(ip, port_no);
    return 0;
}
