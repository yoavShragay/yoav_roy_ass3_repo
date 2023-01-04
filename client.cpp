#include "validations.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;

#define DELIM "."
#define ERROR "invalid input"

/**
 * Check if every part of the ip (separated by a dot) is valid (e.g. 192.68.24.1)
 * @param partIp - a part of the full ip number
 * @return true of its a valid number, and false otherwise.
 */
bool check_valid_part_ip(char *partIp) {
    size_t len = strlen(partIp);
    // if the length is bigger than 3, invalid input.
    // if the length is 2 or 3 but the first char is 0 (e.g. 001 / 00), invalid input.
    if (len > 3 || (len > 1 && partIp[0] == '0')) {
        return false;
    }
    // if the char in ascii is less than 0 or more than 9, invalid input
    for (int i = 0; i < len; i++) {
        if (partIp[i] < '0' || partIp[i] > '9') {
            return false;
        }
    }
    int num = stoi(partIp);
    // if the number is between 0 and 255, it's a valid input
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
    // if the string is empty, invalid input
    if (ip == nullptr) {
        return false;
    }
    int count_dot = 0;
    // parse the ip
    char *ipSplit = strtok(ip, DELIM);
    if (ipSplit == nullptr) {
        return false;
    }
    while (ipSplit) {
        // check if the number is valid
        if (check_valid_part_ip(ipSplit)) {
            // if so, continue to the next part - parse the remaining ip
            ipSplit = strtok(nullptr, DELIM);
            if (ipSplit != nullptr) {
                count_dot++;
            }
        } else {
            return false;
        }
    }
    // if there are more than 3 dots, invalid input
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
    // if the string is empty, invalid input
    if (port == nullptr) {
        return false;
    }
    size_t len = strlen(port);
    // if the port is 0 or starting with a 0, invalid input
    if (port[0] == '0') {
        return false;
    }
    // if the char in ascii is less than 0 or more than 9, invalid input
    for (int i = 0; i < len; ++i) {
        if (port[i] < '0' || port[i] > '9') {
            return false;
        }
    }
    int numPort = stoi(port);

    // if the port not between 0 and 65535, invalid input
    if (numPort < 0 || numPort > 65535) {
        return false;
    }
    return true;
}

/**
 * This function prints "connection problem"
 */
void connectionProblem(){
    cout << "connection problem" << endl;
}

/**
 * This function connects between the server and the client
 * Sends the user input to the server and getting the classification
 * @param ip - the ip string
 * @param port - the port number
 */
void sendVector(string ip, int port) {
    char ipArr[ip.length()];
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
        // send
        // getting the input from the user
        string userInput;
        getline(cin, userInput);
        if (userInput == "-1") {
            flag = true;
        }
        // case - invalid input
        if (!check_valid_user_input(userInput, userInput.length())) {
            cout << "Invalid Input" << endl;
            continue;
        }
        size_t data_len = userInput.length();
        char vectorArr[userInput.length() + 1];
        strcpy(vectorArr, userInput.c_str());
        int sent_bytes = send(sock, vectorArr, data_len, 0);
        if (sent_bytes < 0) {
            connectionProblem();
            break;
        }
        if (flag) {
            break;
        }

        // receive
        char buffer[4096] = "\0";
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            connectionProblem();
            break;
        } else if (read_bytes < 0) {
            connectionProblem();
            break;
        } else {
            if (strcmp(buffer, ERROR) == 0){
                cout << ERROR << endl;
                continue;
            }
            cout << buffer << endl;
        }
    }
    close(sock);
    return;
}

/**
 * This function is the main function in client
 */
int main(int argc, char *argv[]) {
    const string ip = argv[1];
    if (!check_valid_ip(argv[1])) {
        cout << "Invalid Input" << endl;
        exit(1);
    }
    if (!check_valid_port(argv[2])) {
        cout << "Invalid Input" << endl;
        exit(1);
    }

    const int port_no = stoi(argv[2]);

    sendVector(ip, port_no);
    return 0;
}
