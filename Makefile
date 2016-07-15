CC = gcc
CFLAGS = -c -Wall -g -O3
LDFLAGS =
SOURCES = 6502.c test.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = test

all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm $(EXECUTABLE) $(OBJECTS)
