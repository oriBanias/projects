TARGET=queueTest.out

# Compiler and linker flags
CC=g++ 
CFLAGS =-g -pedantic -ansi -Wall -Wconversion
CPPFLAGS=-I./include
CXXFLAGS = $(CFLAGS) -std=c++03
LDFLAGS=-g -pthread -ldl

SOSENSOR6 = g++ $(CXXFLAGS) $(CPPFLAGS) runnable.cpp -c -o runnable.o -fPIC
SOSENSOR7 = g++ $(CXXFLAGS) $(CPPFLAGS) thread.cpp -c -o thread.o -fPIC
SOSENSOR8 = g++ $(CXXFLAGS) $(CPPFLAGS) eventstorage.cpp -c -o eventstorage.o -fPIC
SOSENSOR9 = g++ $(CXXFLAGS) $(CPPFLAGS) IEventpoper.cpp -c -o IEventpoper.o -fPIC
SOSENSOR10 = g++ $(CXXFLAGS) $(CPPFLAGS) IEventpusher.cpp -c -o IEventpusher.o -fPIC
SOSENSOR11 = g++ $(CXXFLAGS) $(CPPFLAGS) semaphore.cpp -c -o semaphore.o -fPIC
SOSENSOR12 = g++ $(CXXFLAGS) $(CPPFLAGS) mutex.cpp -c -o mutex.o -fPIC
SOSENSOR5 = g++ $(CXXFLAGS) $(CPPFLAGS) IDevice.cpp -c -o IDevice.o -fPIC
SOSENSOR4 = g++ $(CXXFLAGS) $(CPPFLAGS) deviceMembers.cpp  -c -o deviceMembers.o -fPIC
SOSENSOR = g++ $(CXXFLAGS) $(CPPFLAGS) event.cpp -c -o event.o -fPIC
SOSENSOR0 = g++ $(CXXFLAGS) $(CPPFLAGS) sensorBase.cpp -c -o sensorBase.o -fPIC
SOSENSOR1 = g++ $(CXXFLAGS) $(CPPFLAGS) ./soFiles/noiseSensor.cpp -c -o ./soFiles/noiseSensor.o -fPIC
SOSENSOR2 = g++  runnable.o thread.o eventstorage.o IEventpoper.o IEventpusher.o semaphore.o mutex.o IDevice.o deviceMembers.o event.o sensorBase.o ./soFiles/noiseSensor.o -o noiseSensor -shared
SOSENSOR3 = mv noiseSensor noiseSensor.so

SOCONTROLLER5 = g++ $(CXXFLAGS) $(CPPFLAGS) event.cpp -c -o event.o -fPIC
SOCONTROLLER6 = g++ $(CXXFLAGS) $(CPPFLAGS) IDevice.cpp -c -o IDevice.o -fPIC
SOCONTROLLER7 = g++ $(CXXFLAGS) $(CPPFLAGS) subscriber.cpp -c -o subscriber.o -fPIC
SOCONTROLLER8 = g++ $(CXXFLAGS) $(CPPFLAGS) iregister.cpp -c -o iregister.o -fPIC
SOCONTROLLER9 = g++ $(CXXFLAGS) $(CPPFLAGS) ihandleregistration.cpp -c -o ihandleregistration.o -fPIC
SOCONTROLLER2 = g++ $(CXXFLAGS) $(CPPFLAGS) deviceMembers.cpp  -c -o deviceMembers.o -fPIC
SOCONTROLLER0 = g++ $(CXXFLAGS) $(CPPFLAGS) controllerBase.cpp  -c -o controllerBase.o -fPIC
SOCONTROLLER1 = g++ $(CXXFLAGS) $(CPPFLAGS) ./soFiles/noiseController.cpp  -c -o ./soFiles/noiseController.o -fPIC
SOCONTROLLER3 = g++ event.o IDevice.o subscriber.o iregister.o ihandleregistration.o deviceMembers.o controllerBase.o ./soFiles/noiseController.o -o noiseController -shared
SOCONTROLLER4 = mv noiseController noiseController.so

# Sources & Objects
SOURCES=$(wildcard *.cpp )
OBJECTS=$(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

include depends

depends:
	$(CC) -MM $(CPPFLAGS) $(SOURCES) > depends

clean:
	rm -f *.o *.so $(TARGET) $(OBJECTS) depends

run: $(TARGET)
	./$(TARGET)
	
so:
	$(SOSENSOR6)
	$(SOSENSOR7)
	$(SOSENSOR8)
	$(SOSENSOR9)
	$(SOSENSOR10)
	$(SOSENSOR11)
	$(SOSENSOR12)
	$(SOSENSOR5)
	$(SOSENSOR4) 
	$(SOSENSOR)
	$(SOSENSOR0)
	$(SOSENSOR1) 
	$(SOSENSOR2) 
	$(SOSENSOR3)
	
	$(SOCONTROLLER2)
	$(SOCONTROLLER5)
	$(SOCONTROLLER6)
	$(SOCONTROLLER7)
	$(SOCONTROLLER8)
	$(SOCONTROLLER9)
	$(SOCONTROLLER0)
	$(SOCONTROLLER1)
	$(SOCONTROLLER3)
	$(SOCONTROLLER4)
	
	

