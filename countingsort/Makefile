#--------------------------------------
# Project definitions
#
TARGET=counting.out
OBJS=counting_sort.o unitest.o
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
counting_sort.o:counting_sort.c ../../../DS/vector/vector.h
unitest.o: unitest.c 
