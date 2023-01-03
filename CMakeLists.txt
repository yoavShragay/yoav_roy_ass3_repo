cmake_minimum_required(VERSION 3.23)

project(yoav_roy_ass3_repo)
set(CMAKE_CXX_STANDARD 11)


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
        vecComparator.cpp
        vecComparator.h
        vectorsDataStruct.cpp
        vectorsDataStruct.h
        validations.cpp
        validations.h
        server.cpp)
