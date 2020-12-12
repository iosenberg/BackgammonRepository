CC = g++
CFLAGS = -g -pedantic -Wall -Wextra -Werror
LDFLAGS = `wx-config --cxxflags` `wx-config --libs`

all: Board.o Backgammon.o rollsList.o GUItest 

GUI: BoardNoRolls.o Backgammon.o GUItest

AIBoard.o: AIBoard.h
	$(CC) $(CFLAGS) -c -o AIBoard.o AIBoard.cc	

rollsList.o: rollsList.h
	$(CC) $(CFLAGS) -c -o rollsList.o rollsList.cc

boardList.o: boardList.h AIBoard.o AIBoard.h
	$(CC) $(CFLAGS) -c -o boardList.o boardList.cc AIBoard.o	

bg.o: bg.h boardList.o boardList.h rollsList.o rollsList.h
	$(CC) $(CFLAGS) -c -o bg.o bg.cc boardList.o rollsList.o

Board.o: Board.h rollsList.o rollsList.h
	$(CC) $(CFLAGS) -o Board.o Board.cc rollsList.o $(LDFLAGS)

BoardNoRolls.o: Board.h
	$(CC) $(CFLAGS) -c -o BoardNoRolls.o Board.cc $(LDFLAGS)

Backgammon.o: Backgammon.h Board.o Board.h
	$(CC) $(CFLAGS) -o Backgammon.o Backgammon.cc Board.o $(LDFLAGS)

#main.o: main.cc main.h Backgammon.h
#	$(CC) $(CFLAGS) -c -o main.o main.cc main.h Backgammon.o $(LDFLAGS)

GUItest: BoardNoRolls.o Backgammon.o main.h
	$(CC) $(CFLAGS) -o GUItest main.cc Backgammon.o Board.o $(LDFLAGS)

clean:
	rm -f *~ *.o GUItest bg boardList rollsList
