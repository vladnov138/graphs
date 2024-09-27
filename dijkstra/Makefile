CC = g++
CFLAGS = -std=c++20 -Wall -pedantic
SOURCE = main.cpp ./exceptions/FileNotOpenException.h ./exceptions/GraphException.h ./exceptions/NodeException.h ./models/Node/Node.h ./models/MarkedNode.cpp ./models/Way.cpp ./models/PriorityQueue/PriorityQueue.h ./models/PriorityQueue/PriorityQueue.cpp 

ifeq ($(OS), Windows_NT)
	RM = del
	TARGET = main.exe
else
	RM = rm
	TARGET = main
endif

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	$(RM) $(TARGET)

run: all
	$(TARGET)