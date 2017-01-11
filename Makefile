# Compiler and Flags to use
CC=g++
CFLAGS= -Wall -Wextra -pedantic

###############################################################################
# Targets to help with testing
###############################################################################
TARGETS =  myTest 

all: test

test: myTest
	myTest

clean:
	del *.o
	del *.exe
	del *.obj


###############################################################################
# CREATING PROGRAMS
###############################################################################

myTest: test.o trie.o
	$(CC) $(CFLAGS) test.o trie.o -o myTest

###############################################################################
# CREATING Object Files
###############################################################################

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp

trie.o: trie.cpp trie.hpp
	$(CC) $(CFLAGS) -c trie.cpp
