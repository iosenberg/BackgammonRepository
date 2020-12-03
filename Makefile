CC = g++
CFLAGS = -g -pedantic -Wall -Wextra -Werror
LDFLAGS = `wx-config --cxxflags` `wx-config --libs`

main: main.o Backgammon.o Board.o
	$(CC) $(CFLAGS) -o GUItest main.o Backgammon.o Board.o $(LDFLAGS)

main.o: main.cc main.h Backgammon.h
	$(CC) $(CFLAGS) -o main.o main.cc $(LDFLAGS)

Backgammon.o: Backgammon.h Board.h
	$(CC) $(CFLAGS) -o Backgammon.o Backgammon.cc $(LDFLAGS)

Board.o: Board.h
	$(CC) $(CFLAGS) -o Board.o Board.cc $(LDFLAGS)

clean:
	rm -f *~ *.o $(TARGET)
