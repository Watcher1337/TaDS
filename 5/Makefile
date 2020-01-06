CC=gcc
CFLAGS=-Wall -c 
SOURCES=main.c measures.c queue.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=app.out

all: $(EXECUTABLE) clean 

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ 

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -rf *.o