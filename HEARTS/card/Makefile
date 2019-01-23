#--------------------------------------
# Project definitions
#
TARGET=CardTest.out
OBJS= card.o  cardtest.o
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
card.o: card.c ../include/card.h
cardtest.o: card.c ../include/card.h cardtest.c
