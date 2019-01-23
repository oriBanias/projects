#--------------------------------------
# Project definitions
#
TARGET=InsertionTest.out
OBJS= insertion.o  main_insertion.o vector.o 
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
insertion.o: vector.c vector.h
main_insertion.o: insertion.c vector.h vector.c
vector.o: vector.h vector.c
