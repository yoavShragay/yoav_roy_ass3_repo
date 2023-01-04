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
The program should run as follows: `./a.out k file distance`
- k is the number of neighbors (any positive int value)
- file is the name of the file of the classified vectors (can be a relative or full address)
- distance is the distance metric: (the representing string value is written next to each one)

  1) Euclidean distance - AUC
  2) Manhattan distance - MAN
  3) Distance Chebyshev - CHB
  4) Distance Canberra - CAN
  5) Minkowski distance - MIN

### Implementation  



### Authors
- Roy Amit
- Yoav Shragay

