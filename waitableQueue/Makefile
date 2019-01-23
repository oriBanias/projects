TARGET=queueTest.out

# Compiler and linker flags
CC=g++
CFLAGS =-g -pedantic -ansi -Wall -Wconversion 
CXXFLAGS = $(CFLAGS) -std=c++03
CPPFLAGS=-I../include
LDFLAGS=-g -pthread -ldl


# Sources & Objects
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

include depends

depends:
	$(CC) -MM $(CPPFLAGS) $(SOURCES) > depends

clean:
	rm -f *.o $(TARGET) $(OBJECTS) depends

run: $(TARGET)
	./$(TARGET)

