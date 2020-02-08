CC=gcc
CFLAGS=-Wall -c 
SOURCES=measures.c queue.c prints.c processor.c main.c includes.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=app.out

all: $(EXECUTABLE) clean 

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ 

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -rf *.o