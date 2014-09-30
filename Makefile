# This script will recompile all sources if only one was changed.
# But I don't mind.

CC=gcc
CFLAGS=-c -Werror=all
LDFLAGS=-lmtp
SOURCES=filelist.c rawdevs.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=$(SOURCES:.c=)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $@.o -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

.PHONY: clean
