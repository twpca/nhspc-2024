CC = g++
CCARGS = -O2 -Wall -Wshadow -std=gnu++1z -D CMS -D TESTSYS
CHECKER_LIST = diff \
               cover \
               indset \
               permutation \
               sudoku

all: $(CHECKER_LIST)

clean:
	rm -f $(CHECKER_LIST)

diff: diff.cpp
	$(CC) diff.cpp $(CCARGS) -o diff

cover: cover.cpp
	$(CC) cover.cpp $(CCARGS) -o cover

indset: indset.cpp
	$(CC) indset.cpp $(CCARGS) -o indset

permutation: permutation.cpp
	$(CC) permutation.cpp $(CCARGS) -o permutation

sudoku: sudoku.cpp
	$(CC) sudoku.cpp $(CCARGS) -o sudoku
