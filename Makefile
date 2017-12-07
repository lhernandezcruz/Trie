# Compiler and Flags to use
CC=cl
CFLAGS= /EHsc -W4 

###############################################################################
# Targets to help with testing
###############################################################################
TARGETS=  myTest simpleEx

all: $(TARGETS)

clean:
	del *.exe
	del *.obj


###############################################################################
# CREATING PROGRAMS
###############################################################################

myTest:
	$(CC) $(CFLAGS) test.cpp trie.cpp  /link /out:myTest.exe

autoComplete:
	$(CC) $(CFLAGS) autoCompleteExample.cpp trie.cpp /link /out:autoComplete.exe