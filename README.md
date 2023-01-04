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
    
  if one of the following happens than the program will close itself: 
  the k is bigger the amount of vectors in the file
  the path isnt right
  the port or ip given to the client or tothe server is invalid  
    
  if one of the following happens than the client will send invalid input and will wait for the next input:
  too many or too little vectors in comperison to the number that sould be in the file
  the k is bigger than the intiger max value
  any kind of incorrect string given by the user

### Implementation  



### Authors
- Roy Amit
- Yoav Shragay

