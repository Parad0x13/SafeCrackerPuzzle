CC=g++
CFLAGS=-c -Wall -std=c++14
LDFLAGS=
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=SafeCrackerPuzzle

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@