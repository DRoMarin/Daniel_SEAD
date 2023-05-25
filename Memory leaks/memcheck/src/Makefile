CC = gcc
CFLAGS = -O3 -Wall  
SOURCES=memcheck.c
OBJECTS=$(SOURCES:.c=.o)
OUTPUT = memcheck

.PHONY: all

all: ${OUTPUT}

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) -c $^ $(CFLAGS) -o $@

.PHONY: clean

clean:
	-rm -f ${OUTPUT} ${OBJECTS}