
CC = gcc
CFLAGS = -fPIC -Wall
LDFLAGS = -shared  
SOURCES=libmemcheck.c
OBJECTS=$(SOURCES:.c=.o)
TARGET_LIB = libmemcheck.so

.PHONY: all

all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJECTS)
	$(CC) ${LDFLAGS} -o $@ $^

${SOURCES:.c=.d}:%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SOURCES:.c=.d)

.PHONY: clean

clean:
	-rm -f ${TARGET_LIB} ${OBJECTS} $(SOURCES:.c=.d)