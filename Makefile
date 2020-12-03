CC = g++
CFLAGS = -g -pedantic -Wall -Wextra -Werror
ENDFLAGS = `wx-config --cxxflags` `wx-config --libs`
all = $(TARGET)

main: main.o Backgammon.o Board.o
	$(CC) $(CFLAGS) -o GUItest main.o Backgammon.o Board.o $(ENDFLAGS)

main.o: main.cc main.h Backgammon.h
	$(CC) $(CFLAGS) -c main.cc $(ENDFLAGS)

Backgammon.o: Backgammon.h Board.h

Board.o: Board.h

clean:
	rm -f *~ *.o $(TARGET)
