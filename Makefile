CC = g++
CFLAGS = -g -pedantic -Wall -Wextra -Werror
LDFLAGS = `wx-config --cxxflags` `wx-config --libs`

all: Backgammon

AIBoard.o: AIBoard.h
	$(CC) $(CFLAGS) -c -o AIBoard.o AIBoard.cc	

rollsList.o: rollsList.h
	$(CC) $(CFLAGS) -c -o rollsList.o rollsList.cc

boardList.o: boardList.h AIBoard.o AIBoard.h
	$(CC) $(CFLAGS) -c -o boardList.o boardList.cc AIBoard.o	

bg.o: bg.h boardList.o boardList.h rollsList.o rollsList.h
	$(CC) $(CFLAGS) -c -o bg.o bg.cc boardList.o rollsList.o

Board.o: Board.h rollsList.o rollsList.h bg.o bg.h
	$(CC) $(CFLAGS) -c -o Board.o Board.cc rollsList.o bg.o $(LDFLAGS)

Backgammon.o: Backgammon.h Board.o Board.h
	$(CC) $(CFLAGS) -c -o Backgammon.o Backgammon.cc Board.o $(LDFLAGS)

Backgammon: Board.o Backgammon.o main.h
	$(CC) $(CFLAGS) -o Backgammon main.cc Backgammon.o Board.o $(LDFLAGS)

clean:
	rm -f *~ *.o Backgammon
