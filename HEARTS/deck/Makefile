#--------------------------------------
# Project definitions
#
TARGET=DeckTest.out
OBJS= deck.o  decktest.o ../../../DS/vector/vector.o
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
deck.o: deck.c ../include/deck.h 
decktest.o: decktest.c ../include/deck.h deck.c 
../../../DS/vector/vector.o: ../../../DS/vector/vector.c ../../../DS/vector/vector.h
