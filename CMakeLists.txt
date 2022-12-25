cmake_minimum_required(VERSION 3.23)
project(yoav_roy_ass3_repo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(yoav_roy_ass3_repo
        classifiedVector.cpp
        classifiedVector.h
        distanceAlgo.cpp
        distanceAlgo.h
        distances.cpp
        distances.h
        disVector.cpp
        disVector.h
        main.cpp
        vecComparator.cpp
        vecComparator.h
        vectorsDataStruct.cpp
        vectorsDataStruct.h client.cpp client.h server.cpp)
