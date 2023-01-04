# *__Advanced Programming Assignment__*

## Table of Contents
* [Project Description](#project-description)
* [How To Compile](#how-to-compile)
* [How To Run](#how-to-run)
* [Implementation](#implementation)
* [Authors](#authors)

### Project Description  
In this assignment we will take the program from the previous exercise, and divide it into server side and client side.  
This time, the classifier will run on the server and the client will send an unclassified vector to the server. 
The server in turn will classify the vector and send it to the client the classification.  
Further explanations regarding the server and the client, below.

### How To Compile
In order to compile the code, use the command: `make`

### How To Run
The program should run as follows:  
first, we run the server with the command `./server.out file port`
- file is the name of the file of the classified vectors (can be a relative or full address)
- port is the port number, chosen by the user, and can be a number between 0 and 65535    

After the server is running, it's waiting for a connection from the client.  

Next, we run the client with the command `./client.out ip port`
- ip is the ipv4 address of the server so that a connection can be made with the server  
- port is the same port used by the server

Finally, after the connection has been made, the user enters a vector (as described in previous exercises)  
with the format as follows: `vector distance k`  
- vector is the vector to be classified (format as describes in previous exersices)
- distance is the distance metric: (the representing string value is written next to each one)
  1) Euclidean distance - AUC
  2) Manhattan distance - MAN
  3) Distance Chebyshev - CHB
  4) Distance Canberra - CAN
  5) Minkowski distance - MIN  

- k is the k nearest neighbors (k can't be greater than the number of vectors in the file)  

If the input meets the conditions described above, the output on the screen will be a classification.  
Otherwise, the message `invalid input` will be printed.
  
### Implementation  
The client runs in an infinite loop, and receives from the user an input as described above.  
The client sends the information received from the user to the server.  
The server is classified accordingly, and sends the classification to the client.  
The client prints the received answer to the screen, on a separate line, and receives the next input from the user.  
If the user enters several inputs, the client must send these inputs over the same connection to the server,  
and not on separate connections.  
If the user enters the input -1, the client must close the connection to the server and close the program.  
The server, in this case, continues to the next connection (the server does not close).  
In any case of invalid input, the customer must print invalid input, and continue to receive the next input.  
In any case that the server receives an invalid input from the client, 
the server must return only invalid input to the client and continue receiving
the following information from that customer.

### Authors
- Roy Amit
- Yoav Shragay

