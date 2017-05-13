CC=gcc
CFLAGS=-W -Wall 
LDFLAGS=-lncurses -lSDL -lSDL_image -lSDL_ttf
EXEC=zelsok
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

zelsok: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	+rm *.o

%.o: %.c 
	$(CC) -o $@ -c $<

clean:
	rm *.o

mrproper: clean
	rm $(EXEC)
