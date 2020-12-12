CC = g++
CFLAGS = -g -pedantic -Wall -Wextra -Werror
LDFLAGS = `wx-config --cxxflags` `wx-config --libs`

Backgammon: Board.o Backgammon.o main.h
	$(CC) $(CFLAGS) -o Backgammon main.cc Backgammon.o Board.o $(LDFLAGS)

AIBoard.o: AIBoard.h
	$(CC) $(CFLAGS) -c -o AIBoard.o AIBoard.cc	

rollsList.o: rollsList.h
	$(CC) $(CFLAGS) -c -o rollsList.o rollsList.cc

boardList.o: boardList.h AIBoard.o AIBoard.h
	$(CC) $(CFLAGS) -c -o boardList.o boardList.cc

bg.o: bg.h boardList.o boardList.h rollsList.o rollsList.h
	$(CC) $(CFLAGS) -c -o bg.o bg.cc

Board.o: Board.h rollsList.o rollsList.h bg.o bg.h
	$(CC) $(CFLAGS) -c -o Board.o Board.cc $(LDFLAGS)

Backgammon.o: Backgammon.h Board.o Board.h
	$(CC) $(CFLAGS) -c -o Backgammon.o Backgammon.cc $(LDFLAGS)

clean:
	rm -f *~ *.o Backgammon
