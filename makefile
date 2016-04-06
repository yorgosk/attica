CC = g++
CFLAGS = -Wall
OBJECTS = main.o attica.o entrance.o segmentList.o vehicleList.o tollList.o

highway: $(OBJECTS)
	$(CC) $(CFLAGS) -o highway $(OBJECTS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

attica.o: attica.cpp
	$(CC) $(CFLAGS) -c attica.cpp

entrance.o: entrance.cpp
	$(CC) $(CFLAGS) -c entrance.cpp

segmentList.o: segmentList.cpp
	$(CC) $(CFLAGS) -c segmentList.cpp

vehicleList.o: vehicleList.cpp
	$(CC) $(CFLAGS) -c vehicleList.cpp

tollList.o: tollList.cpp
	$(CC) $(CFLAGS) -c tollList.cpp

.PHONY: clean

clean:
	rm -f highway $(OBJECTS)
