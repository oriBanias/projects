#--------------------------------------
# Project definitions
#
TARGET=GameTest.out
OBJS= game.o  testgame.o ../player/player.o ../round/round.o ../ui/ui.o ../../../DS/vector/vector.o ../trick/trick.o ../card/card.o ../../../DS/sorts/insertion/insertion.o ../deck/deck.o
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
game.o: game.c ../include/round.h ../include/player.h ../include/ui.h ../include/card.h ../include/trick.h ../include/deck.h ../../../DS/vector/vector.h
testgame.o: testgame.c ../include/player.h ../include/round.h ../include/ui.h  
../player/player.o: ../player/player.c ../include/player.h ../../../DS/sorts/insertion/insertion.h 
../ui/ui.o: ../ui/ui.c ../include/ui.h ../include/card.h ../include/player.h ../include/round.h ../include/trick.h ../include/game.h ../include/deck.h
../round/round.o: ../include/card.h ../include/deck.h ../include/round.h ../include/trick.h
../../../DS/vector/vector.o: ../../../DS/vector/vector.c ../../../DS/vector/vector.h
../trick/trick.o: ../trick/trick.c ../include/trick.h ../include/card.h ../include/ui.h 
../card/card.o: ../card/card.c ../include/card.h
../../../DS/sorts/insertion/insertion.o: ../../../DS/sorts/insertion/insertion.h ../../../DS/vector/vector.h
../deck/deck.o: ../deck/deck.c ../include/deck.h ../include/card.h ../../../DS/vector/vector.h


