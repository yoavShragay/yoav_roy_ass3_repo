#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#include "validations.h"
#include "vectorData.h"

#define BUFFERSIZE 4096
#define ERROR "invalid input"

using namespace std;

/**
 * converts character array to string and returns it
 * @param a the char array
 * @param size size of the array
 * @return the string
 */
string convertToString(char *a, int size) {
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

/**
 * This function creates a new vectorData that holds the user input parameters
 * @param userInput - string of the following format: vector, distance, k
 * @return a new vectorData object
 */
vectorData createVecData(string userInput, int read_bytes) {
    bool flag = true;
    int last_index = userInput.find_last_of(' ');
    int first_index;
    string distance;
    // splitting the k parameter from user input
    string k = userInput.substr(last_index + 1, read_bytes - last_index);
    for (int i = last_index - 1; i >= 0; --i) {
        // splitting the distance parameter from user input
        if (userInput[i] == ' ' && flag) {
            first_index = i;
            // splitting the vector parameter from the user input
            distance = userInput.substr(i + 1, last_index - (first_index + 1));
            // check if the distance parameter is valid
            flag = false;
        }
    }
    // splitting the vector parameter from the user input
    string vec = userInput.substr(0, first_index);
    // check if the vector is valid
    vectorData v = vectorData(vec, distance, stoi(k));
    return v;
}

/**
 * classifying the vector according to the arguments the user gave us
 * @param buffer pointer to the start of array with the the information from the user
 * @param file_name path to the file of the vectors
 * @return
 */
string classify(char *buffer, string file_name, int read_bytes) {
    string userInput = convertToString(buffer, read_bytes);
    if (!check_valid_user_input(userInput, read_bytes)) {
        return ERROR;
    }
    // getting the vectors from the file
    vector<classifiedVector> allClassVec = fileToVec(file_name);
    // separating the user's input to the different values
    vectorData vecData = createVecData(userInput, read_bytes);
    // case - k is bigger than the amount of vectors in the file
    if (allClassVec.size() < vecData.getK()) {
        return ERROR;
    }
    // getting the classification
    string classification = getClassification(allClassVec, vecData.getDistance(),
                                              vecData.getK(), vecData.getVec());
    return classification;
}

/**
 * connecting to client
 * @param sock the socket that the client going to be connected to
 * @return the client socket
 */
int connectClient(int sock) {
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        cout << "error accepting client";
        exit(1);
    }
    return client_sock;
}

/**
 * accepting the vector from the client and returning the classification
 * @param port the port
 * @param file the file is going to be used for the classification
 */
void acceptVector(int port, string file) {
    bool flag = false;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cout << "error creating socket";
        exit(1);
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);
    //bind
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout << "error binding socket";
        exit(1);
    }
    if (listen(sock, 5) < 0) {
        cout << "error listening to a socket";
        exit(1);
    }
    while (true) {
        int client_sock = connectClient(sock);
        while (true) {
            char buffer[BUFFERSIZE] = "\0";
            int expected_data_len = sizeof(buffer);
            int read_bytes = recv(client_sock, buffer, expected_data_len, 0);

            if (read_bytes == 0) {
                cout << "connection is closed";
                break;
            } else if (read_bytes < 0) {
                cout << "problem with connection";
                break;
            } else {
                if (strcmp(buffer, "-1") == 0) {
                    break;
                }
            }
            // classify
            string tmpClassification = classify(buffer, file, read_bytes);
            // converting to buffer
            strcpy(buffer, tmpClassification.c_str());
            // sending the classification to the client
            int sent_bytes = send(client_sock, buffer, tmpClassification.length() + 1, 0);
            if (sent_bytes < 0) {
                cout << "error sending to client";
                break;
            }
        }
    }
}

/**
 * This is the main function of server
 */
int main(int argc, char *argv[]) {
    const string file_name = argv[1];
    //TODO - check if leagel number
    const int server_port = stoi(argv[2]);
    acceptVector(server_port, file_name);
    return 0;
}
