all: server.out client.out

server.out: server.o vectorData.o validations.o vectorsDataStruct.o distanceAlgo.o classifiedVector.o disVector.o vecComparator.o distances.o
	g++ -std=c++11 server.o vectorData.o validations.o vectorsDataStruct.o distanceAlgo.o classifiedVector.o disVector.o vecComparator.o distances.o -o server.out

client.out: client.o vectorData.o validations.o vectorsDataStruct.o distanceAlgo.o classifiedVector.o disVector.o vecComparator.o distances.o
	g++ -std=c++11 client.o vectorData.o validations.o vectorsDataStruct.o distanceAlgo.o classifiedVector.o disVector.o vecComparator.o distances.o -o client.out

client.o: client.cpp validations.h
	g++ -c -std=c++11 client.cpp

server.o: server.cpp validations.h
	g++ -c -std=c++11 server.cpp

vectorData.o: vectorData.cpp vectorData.h
	g++ -c -std=c++11 vectorData.cpp

validations.o: validations.cpp validations.h
	g++ -c -std=c++11 validations.cpp

vectorsDataStruct.o: vectorsDataStruct.cpp vectorsDataStruct.h classifiedVector.h disVector.h
	g++ -c -std=c++11 vectorsDataStruct.cpp

distanceAlgo.o: distanceAlgo.cpp distanceAlgo.h distances.h
	g++ -c -std=c++11 distanceAlgo.cpp

classifiedVector.o: classifiedVector.cpp classifiedVector.h
	g++ -c -std=c++11 classifiedVector.cpp

disVector.o: disVector.cpp disVector.h
	g++ -c -std=c++11 disVector.cpp

vecComparator.o: vecComparator.cpp vecComparator.h
	g++ -c -std=c++11 vecComparator.cpp

distances.o: distances.cpp distances.h
	g++ -c -std=c++11 distances.cpp

clean:
	rm *.o a.out