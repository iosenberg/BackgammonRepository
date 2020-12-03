CC = g++
CFLAGS = -g -pedantic -Wall -Wextra -Werror
LDFLAGS = `wx-config --cxxflags` `wx-config --libs`

all: Board.o Backgammon.o GUItest

Board.o: Board.h
	$(CC) $(CFLAGS) -c -o Board.o Board.cc $(LDFLAGS)

Backgammon.o: Backgammon.h Board.o Board.h
	$(CC) $(CFLAGS) -c -o Backgammon.o Backgammon.cc Board.o $(LDFLAGS)

#main.o: main.cc main.h Backgammon.h
#	$(CC) $(CFLAGS) -c -o main.o main.cc main.h Backgammon.o $(LDFLAGS)

GUItest: Board.o Backgammon.o main.h
	$(CC) $(CFLAGS) -o GUItest main.cc Backgammon.o Board.o $(LDFLAGS)

clean:
	rm -f *~ *.o GUItest
