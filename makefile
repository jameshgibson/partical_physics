CC=g++
CFLAGS=-c -Wall -O2
LDFLAGS=
SOURCES=main.cpp helpers.cpp particle_analyser.cpp spatial_analyser.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
DEL=rm -f
EXE=sa

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS) 
$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
$(CC) $(CFLAGS) $< -o $@

clean:
$(DEL) $(EXE) *.o
