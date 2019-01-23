#--------------------------------------
# Project definitions
#
TARGET=PlayerTest.out
OBJS= player.o  testplayer.o ../../../DS/vector/vector.o ../card/card.o ../../../DS/sorts/insertion/insertion.o
LDFLAGS=

#--------------------------------------
# General actions and definitions
#
CC=gcc
CFLAGS=-g -Wconversion -Werror -Wall -ansi -pedantic

$(TARGET): $(OBJS)
	gcc $(OBJS) $(LDFLAGS) -o $(TARGET)

.PHONY: clean run gdb

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

gdb: $(TARGET)
	gdb -q ./$(TARGET)

#--------------------------------------
# Dependencies
#
player.o: player.c ../include/player.h ../../../DS/vector/vector.c 
testplayer.o: testplayer.c ../include/player.h player.c ../../../DS/vector/vector.h ../../../DS/vector/vector.c
../../../DS/vector/vector.o: ../../../DS/vector/vector.c ../../../DS/vector/vector.h
../card/card.o: ../card/card.c ../include/card.h
../../../DS/sorts/insertion/insertion.o: ../../../DS/sorts/insertion/insertion.h ../../../DS/sorts/insertion/insertion.c

