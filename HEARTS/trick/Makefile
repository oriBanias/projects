#--------------------------------------
# Project definitions
#
TARGET=TrickTest.out
OBJS= trick.o  tricktest.o ../../../DS/vector/vector.o ../card/card.o ../player/player.o ../../../DS/sorts/insertion/insertion.o ../deck/deck.o ../ui/ui.o
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
trick.o: trick.c ../include/trick.h  ../include/card.h ../include/ui.h
tricktest.o: tricktest.c ../include/trick.h ../../../DS/vector/vector.h  ../include/card.h ../include/deck.h
../../../DS/vector/vector.o: ../../../DS/vector/vector.c ../../../DS/vector/vector.h
../card/card.o: ../card/card.c ../include/card.h
../player/player.o: ../player/player.c ../include/player.h ../../../DS/sorts/insertion/insertion.h 
../../../DS/sorts/insertion/insertion.o: ../../../DS/sorts/insertion/insertion.h ../../../DS/vector/vector.h
../deck/deck.o: ../deck/deck.c ../include/deck.h ../include/card.h ../../../DS/vector/vector.h
../ui/ui.o: ../ui/ui.c ../include/ui.h ../include/card.h ../include/player.h

