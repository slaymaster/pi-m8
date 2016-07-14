CC=gcc
CFLAGS=-Wall -g -pedantic -std=gnu99 `pkg-config --cflags glib-2.0`
LDFLAGS=$(shell pkg-config --libs glib-2.0)
SOURCES=frameworks/memwork/memwork.c frameworks/threadwork/threadwork.c pi-m8.c
OBJECTS=$(SOURCES:.c=.o)
DEPS=frameworks/memwork/memwork.h frameworks/threadwork/threadwork.h pi-m8.h
EXECUTABLE=pi-m8

all: $(SOURCES) $(EXECUTABLE) clean
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lpthread

.c.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf *.o
