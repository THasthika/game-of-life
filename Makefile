CC := gcc
LD := gcc

CCFLAGS :=
LDFLAGS :=

.PHONY: all clean

all: game

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $^

game: main.o
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	rm *.o
	rm game
