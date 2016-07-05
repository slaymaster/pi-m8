CC=gcc
CFLAGS=-Wall -g -pedantic -std=gnu99 `pkg-config --cflags glib-2.0`
LDFLAGS=$(shell pkg-config --libs glib-2.0)
SOURCES=threadwork.c threadworker.c ../memwork/memwork.c
OBJECTS=$(SOURCES:.c=.o)
DEPS=threadwork.h ../memwork/memwork.h
EXECUTABLE=threadwork

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lpthread

.c.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf *.o
