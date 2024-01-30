CC = g++
CFLAGS = -c
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SOURCES = $(wildcard ./*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = GUITAR-HERALD

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
